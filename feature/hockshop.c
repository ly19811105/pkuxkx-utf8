#pragma save_binary
// hockshop.c
// modified by Pal 2003-5-28
// Jason 2009/06 重新设计，去除大量重复代码，向上为玩家自己的当铺提供适当抽象

#include <ansi.h>

inherit ROOM;
#define MAX_PAWN 20
inherit F_SAVE;
inherit F_UNIOBJ;

//唯一的ID号，每一个实现者都必须分配一个不同的ID
//这是区分存档文件的唯一标志。
nosave int unique_id = 0;

nosave string *sell_msg = ({
  "破破烂烂，一文不值",
  "质地低劣，难看之极",
  "又脏又破，臭气熏天",
});


nosave string *do_value_msg = ({
  "质地尚可，可惜品相欠佳",
  "外表不俗，奈何已有破损",
  "貌似名品，然则真伪难辨",
  "金玉其外败絮其中",
  "无印无鉴无款，实属三无产品"
});

//单样货物的上限
int getsinglelimit();


nosave object shop_box;

int query_max_items() {return 50;}
string get_name(string str);
int filter_goods(object ob,string goodtype);

int get_price(object ob,string pricetype);
int check_balance_enough(int value);
int pay_shop(object pl,int value);

int clean_goods();

object findbox();
int check_can_sell_or_not(object ob);

string query_save_file()
{
  return "/data/business/hockshop_"+unique_id;
}

string use_help()
{
  return "公平交易
  卖东西：sell id(或name) [number]
  买东西：buy id(或name)
  当东西：pawn(dang) id
  赎东西：retrieve(shu) piao
  取消典当物品的赎回权利：discard <物品标号>
  看可卖物品：list
  估价：value id
";
}

//临时解决颜色码导致不能对齐的问题
int color_len(string str)
{
        int i;
        int extra;

        extra = 0;
        for (i = 0; i < strwidth(str); i++)
        {
                if (str[i] == ESC[0])
                {
                        while ((extra++, str[i] < 'A' ||
                                        str[i] > 'z' ||
                                        str[i] > 'Z' && str[i] < 'a') && i < strwidth(str))
                                i++;
                }
        }
        return extra;
}

int save_shop()
{
  //东西存放在聚宝盒里。
  mapping goods = findbox()->query_temp("goods");
  string* names;
  string basename;
  string longstr,shortstr,realmap;

  int i = 0;

  delete("goods");
  if(mapp(goods) && sizeof(goods) > 0)
  {
    names = keys(goods);
    i = sizeof(goods);
    //保存货物
    while(i--) {
      if(i%10 == 0) reset_eval_cost();

      if(!goods[names[i]]) 
      {
        findbox()->delete_temp("numbers/"+names[i]);
        findbox()->delete_temp("goods/"+names[i]);
        continue;
      }
      basename = base_name(goods[names[i]]);
      basename = replace_string(basename,"/","_-_");
      set("goods/"+basename,findbox()->query_temp("numbers/"+names[i]));
    }
  }

  //其他信息都在dbase里
  save();
  return 1;
}

int load_shop()
{
  //装载货物
  mapping goods;
  string* names;
  int i = 0;
  string index;
  object ob;
  object* invs;
  string basename;

  restore();

  goods = query("goods");
  findbox()->delete_temp("goods");
  invs = all_inventory(findbox());
  for(i=0;i<sizeof(invs);i++)
  {
    destruct(invs[i]);
  }

  if(mapp(goods) && sizeof(goods) > 0)
  {
    names = keys(goods);
    i = sizeof(goods);

    while(i--) 
    {
      if(i%10 == 0) reset_eval_cost();
      
      basename = names[i];
      basename = replace_string(basename,"_-_","/");
      catch(ob = new(basename));
      if(objectp(ob))
      {
        index=ob->query("name")+"("+ob->query("id")+")";
        findbox()->set_temp("goods/"+index,ob);
        findbox()->set_temp("numbers/"+index,goods[names[i]]);
        ob->move(findbox());
      }
    }
  }  
  remove_call_out("clean_goods");
  call_out("clean_goods",120);
  return 1;
}

void setup_shop()
{
  load_shop();
}

void init()
{
    add_action("do_value", "value");
    add_action("do_pawn", "pawn");
    add_action("do_pawn","dang");
    add_action("do_retrieve","shu");

    add_action("do_sell", "sell");
    add_action("do_retrieve", "retrieve");
    add_action("do_retrieve", "redeem");
    add_action("do_discard", "discard");    

    add_action("do_buy", "buy");
    add_action("do_list", "list");
    //add_action("do_quit", "quit");

    set("no_clean_up", 1);
}

// find the shopbox object for this shop to hold sold items.
object findbox()
{
    if(shop_box && environment(shop_box)==this_object()) 
  return shop_box;

    shop_box = present("treasure box",this_object());
    if(objectp(shop_box) && base_name(shop_box) == __DIR__"shopbox")
      return shop_box;

    shop_box=new(__DIR__"shopbox");
    shop_box->move(this_object());
    return shop_box;
}

string value_string(int value)
{
    if( value < 1 ) value = 1;
    else if( value < 100 )
  return chinese_number(value) + "文钱";
    else if( value < 10000)
  return chinese_number(value/100) + "两白银"
  + (value%100? "又" + chinese_number(value%100) + "文钱": "");
    else
  return chinese_number(value/10000) + "两黄金" + (value%10000?chinese_number((value%10000)/100) + "两白银":"")
  + (value%100? "又" + chinese_number(value%100) + "文钱": "");
}

void pay_player(object who, int amount)
{
    object ob;

    if( amount < 1 ) amount = 1;
    if( amount/100000 ) {
      ob = new("/clone/money/thousand-cash");
      ob->set_amount(amount/100000);
    
    if(!ob->move(who))
      ob->move(environment(who));
      amount %= 100000;
    }
    
    if( amount/10000) {
      ob = new(GOLD_OB);
      ob->set_amount(amount/10000);
      if(!ob->move(who))
        ob->move(environment(who));
        amount %= 10000;
    }
    
    if( amount/100 ) {
      ob = new(SILVER_OB);
      ob->set_amount(amount/100);
      if(!ob->move(who))
        ob->move(environment(who));
        amount %= 100;
    }
    
    if( amount ) {
      ob = new(COIN_OB);
      ob->set_amount(amount);
      if(!ob->move(who))
        ob->move(environment(who));
    }
}

//当铺给物品估价
int do_value(string arg)
{
    object ob;
    int value, sale;

    if( !arg || !(ob = present(arg, this_player())) )
      return notify_fail("你要拿什么物品给当铺估价？\n");

    if( ob->query("money_id") )
      return notify_fail("这是「钱」，你没见过吗？\n");

    value = get_price(ob,"sell");

    if( !value) printf("%s一文不值。\n", ob->query("name"));
    else 
      printf("这位客官，%s%s,本店以%s收购。\n",
        ob->query("name"), do_value_msg[random(sizeof(do_value_msg))],value_string(value));

    return 1;
}

//玩家将物品典当给系统当铺
int do_pawn(string arg)
{
    object ob, stamp_ob,me;
    int value, sale_price,pawn_count,attribute;
    string obj_file,file_name,data;
    int i,pawn_num,clone_number,totalnum;
    mapping pawn,npawn,vpawn;
    string term, *terms;
    totalnum=0;

    me = this_player();

    pawn = me->query("pawn");
    npawn = me->query("npawn");
    vpawn = me->query("vpawn");     

    if( me->is_busy() )
      return notify_fail("你现在正忙着呢。\n");

    pawn_num=to_int(me->query("combat_exp")/5000000+me->query("mud_age")/(3600*24*10))+1;
    if (pawn_num < 0)
      pawn_num=0;
    if (pawn_num > MAX_PAWN)
      pawn_num = MAX_PAWN;
    if ( mapp(pawn) && sizeof(pawn) )
    {
      terms = keys(pawn);
      for (i=0 ;i<sizeof(terms) ;i++ )
      {
        totalnum += npawn[terms[i]];
      }
    }
//  printf("pawn_num=%d,totalnum=%d,i=%d\n",pawn_num,totalnum,i);
    if( !arg || !(ob = present(arg, me))) 
//      return notify_fail("指令格式：pawn|dang [<物品ID>]\n");
    {
      if( !mapp(pawn) || !sizeof(pawn) )
      {
        write("你并没有典当任何物品。\n");
        printf("\t你一共可以典当%d样%d件物品。\n",pawn_num,2*pawn_num);
      }
      else
      {
        write("你目前典当的物品有：\n");
        terms = keys(pawn);
        for (i=0 ;i<sizeof(terms) ;i++ )
        {
          printf("%-3s：  %-15s  共有%-5d件    赎银：%s\n", terms[i], pawn[terms[i]],npawn[terms[i]],  value_string(vpawn[terms[i]]* 4/5));
        }
        printf("\t你还可以典当%d样%d件物品。\n",pawn_num-i,2*pawn_num-totalnum);
      }
      return 1;
    }
//  printf("pawn_num=%d,totalnum=%d,i=%d\n",pawn_num,totalnum,i);
    if (ob->query("shaolin"))
      return notify_fail("少林的宝物小的可不敢要呀！\n");
    if (ob->query("mingjiao"))
      return notify_fail("魔教的财产小的可不敢要呀！\n");
    if (ob->query("zijin"))
      return notify_fail("大内的宝物小的可不敢要呀！\n");
    if (ob->query("dalunsi"))
      return notify_fail("大轮寺的宝物小的可不敢要呀！\n");
    if (ob->query("money_id"))  
      return notify_fail("你要当「钱」？\n");
      
    if ( (int)ob->query("skill_type")!=0 && 
         (int)ob->query("rigidity")<50 ) 
      return notify_fail("掌柜的说：我们不收破烂的兵器。\n");
    if( ob->query("unique") )
      return notify_fail("掌柜的说：这种宝物我们可不敢要!\n");
    if( ob->query("material") == "ice" )
      return notify_fail("掌柜的说：冰的东西我们这里没法存放。\n");
//cuz ice melts, will cause problem, so disabled...weiqi, 970930.

    value = ob->query("value");
    sale_price=ob->query_temp("sale_price");
    if (sale_price>0)
      sale_price= sale_price>value?value:sale_price;
    else
      sale_price=value;

    if( !(sale_price*6/10) ) 
      return notify_fail("这样东西并不值很多钱。\n");
    if( !value || value < 10) 
      return notify_fail("这样东西不值钱。\n");
    if(ob->query("no_pawn") || ob->query("no_store"))
      return notify_fail("这样东西不能买卖。\n");

    if(ob->query("no_drop"))
      return notify_fail("这样东西不能离开你。\n");
    if (totalnum >= pawn_num*2)
      return notify_fail("你典当物品数量太多，小店没有地方存了。\n");

    if( mapp(pawn) && sizeof(pawn))
    {
      terms = keys(pawn);
      for(i=0; i<50; i++)  
      {
        sscanf(file_name(ob),"%s#%d",file_name,clone_number);
        if (file_name+".c"==me->query("fpawn/"+sprintf("%d",i)))
        {
          if (totalnum >= pawn_num*2)
            return notify_fail("你典当物品数量太多，小店没有地方存了。\n");
          me->set("npawn/"+ sprintf("%d",i),me->query("npawn/"+sprintf("%d",i))+1);
          me->set("vpawn/" + sprintf("%d",i),ob->query("value"));
          me->save();
          if (ob->query("equipped")) ob->unequip();
          if ( ob->query_amount()>0 )
            write("掌柜的唱道："+ sell_msg[random(sizeof(sell_msg))] +
              ob->query("name") + "一" + ob->query("base_unit") + "，押"+
              value_string(sale_price*60/100)+ "。\n");
          else
            write("掌柜的唱道："+ sell_msg[random(sizeof(sell_msg))] +
              ob->query("name") + "一" + ob->query("unit") + "，押"+
              value_string(sale_price*60/100)+ "。\n");
          message_vision("$N把身上的" + ob->query("name") + "拿出来典当了"
            + value_string(sale_price * 60 / 100) + "。\n", me);
          me->start_busy(1);
          pay_player(me, sale_price * 60 / 100);
          if ( ob->query_amount()>0 )
            ob->add_amount(-1);
          else
            destruct(ob);
          return 1;
        }
      }
      for(i=0; i<sizeof(terms); i++)  
      {
        pawn_count = i;
        if(!((int) me->query("vpawn/" + sprintf("%d", i))))
          break;
        else pawn_count = i+1;
      }
      if (sizeof(terms) >= pawn_num)
        return notify_fail("你已典当太多物品了。\n");
//    printf("pawn_count=%d\n",pawn_count);
    }
    else
      pawn_count=0;
//  printf("pawn_count=%d\n",pawn_count);
    if (ob->query("equipped")) ob->unequip();
    if ( ob->query_amount()>0 )
      write("掌柜的唱道："+ sell_msg[random(sizeof(sell_msg))] +
        ob->query("name") + "一" + ob->query("base_unit") + "，押"+
        value_string(sale_price*60/100)+ "。\n");
    else
      write("掌柜的唱道："+ sell_msg[random(sizeof(sell_msg))] +
        ob->query("name") + "一" + ob->query("unit") + "，押"+
        value_string(sale_price*60/100)+ "。\n");
    message_vision("$N把身上的" + ob->query("name") + "拿出来典当了"
      + value_string(sale_price * 60 / 100) + "。\n", me);
    me->start_busy(1);
    term = ob->query("name");
    attribute = ob->query("attribute");
    data = base_name(ob)+ ".c";
    me->set("pawn/"+ sprintf("%d",pawn_count),  term);
    me->set("vpawn/"+sprintf("%d",pawn_count), ob->query("value"));
    me->set("fpawn/"+sprintf("%d",pawn_count), data);
    me->set("npawn/"+sprintf("%d",pawn_count), 1);
    me->set("apawn/"+sprintf("%d",pawn_count), attribute);
    me->save();
    pay_player(me, sale_price * 60 / 100);
    if ( ob->query_amount()>0 )
      ob->add_amount(-1);
    else
      destruct(ob);

    return 1;
}
// strip away ansi color code.
// mon 5/7/98
string get_name(string str)
{
    string str1, str2;

    while(sscanf(str,"%s%*sm%s",str1,str2)==3)
  str=str1+str2;
    return str;
}

//物品销售的核心函数
//增加对combined类物品的支持 by seagate@pkuxkx
varargs mixed do_every_sell(object ob, int num)
{
    int value, sale;
    string obj_file;
    object oldob, cob;
    int i, oldnum, realnum=0;
    string index;

  
  //player_hockshop have more complex judgement here.
  //not simple "no_sell" -- Jason
    if(check_can_sell_or_not(ob) == 0)
    {
      write("这样东西不能买卖。\n");
      return 0;
    }

    value = get_price(ob,"sell");

    if(!value ) 
    {
      write("这样东西不值钱。\n");
      return 0;
    }

    if(check_balance_enough(this_player()->query_temp("sell_allvalue") + value) == 0)
    {
      write("对不起，本店资金有限，无力收购您的货物。\n");
      return 0;
    }

    index=ob->query("name")+"("+ob->query("id")+")"; 
      
    if(!(oldob = findbox()->query_temp("goods/"+index)) )
    {
      if ( (realnum=ob->query_amount())>0 )
      {
        if ( num>0 && realnum>num )
          realnum=num;
        else if ( num<=0 )
          realnum=1;

        findbox()->set_temp("numbers/"+index, realnum);
        if ( realnum==ob->query_amount() )
        {
          ob->set_amount(1);
          ob->move(findbox());
          findbox()->set_temp("goods/"+index, ob);
        }
        else
        {
          cob=new(base_name(ob));
          cob->set_amount(1);
          ob->add_amount(-realnum);
          cob->move(findbox());
          findbox()->set_temp("goods/"+index, cob);
        }
        value=value*realnum;
      }
      else 
      {
        findbox()->set_temp("goods/"+index, ob);
        findbox()->set_temp("numbers/"+index, 1);
        ob->move(findbox());
      }
    }
    else 
    {
      oldnum = findbox()->query_temp("numbers/"+index);
      if(oldnum >= getsinglelimit() && getsinglelimit() > 0)
      {
        write("这样东西我们已经收购的足够多了，暂时不需要了。\n");
        return 0;
      }
      if ( (realnum=ob->query_amount())>0 )
      {
        if ( num>0 && realnum>num )
          realnum=num;
        else if ( num<=0 )
          realnum=1;
        
        findbox()->set_temp("numbers/"+index, oldnum+realnum);
        value=value*realnum;        
      }
      else
        findbox()->set_temp("numbers/"+index, oldnum+1);
      if (ob->query("value") > oldob->query("value"))
        oldob->set("value",ob->query("value"));
    }

    if ( realnum<=0 )
      this_player()->set_temp("sell_unit/"+index,ob->query("unit"));
    else
      this_player()->set_temp("sell_unit/"+index,ob->query("base_unit"));
      
    this_player()->add_temp("sell_value/"+index,value);
    if ( realnum<=0 )
      this_player()->add_temp("sell_count/"+index,1);
    else
      this_player()->add_temp("sell_count/"+index,realnum);
    
    if(oldnum && realnum<=0 )
      destruct(ob);
    else if ( oldnum && realnum>0 )
      ob->add_amount(-realnum);
    
    if ( realnum<=0 )
      return value;
    else
      return ({value, realnum});
}

//物品出售给当铺的动作函数
//增加对combined物品的支持 by seagate@pkuxkx
int do_sell(string arg)
{
    object ob;
    int value, sale, pay_value, *sells;
    string obj_file,obj,msg,msg2;
    int i, oldnum,num,num_sold;
    mapping objvalue,objcount,objunit;
    string index;
    object *ob_list;
    if (!arg)
      return notify_fail("指令格式：sell 物品名称或ID <个数>\n");
    
    if( this_player()->is_busy() )
      return notify_fail("你现在正忙着呢。\n");

    if (sscanf(arg, "%s %d",obj, num) != 2)
    {
      obj = arg;
      num = 1;
    }
    
    arg = obj;
    if (num < 1)
      return notify_fail("你想卖多少？\n");

    if( !arg)
      return notify_fail("你要卖断什么物品？\n");
    
    ob_list = all_inventory(this_player());
    oldnum = 0;
    for (i=0;i<sizeof(ob_list);i++)
    {
      if( (member_array(arg, 
        ob_list[i]->parse_command_id_list()) != -1 ) ||
        (arg == get_name(ob_list[i]->name())) )
      {
        if ( ob_list[i]->query_amount() )
        {
          if ( ob_list[i]->query("base_unit") )
            index=ob_list[i]->query("base_unit");
          else
            index=ob_list[i]->query("unit");
          
          oldnum+=ob_list[i]->query_amount();
        }
        else
        {
          index = ob_list[i]->query("unit");
          oldnum++;
        }
      }
    }
    
    if (oldnum == 0)
      return notify_fail("你身上没有" + arg + "\n");
      
    if (oldnum < num)
      return notify_fail("你只有" + CHINESE_D->chinese_number(oldnum) + index
        + arg + "，没那么多可卖。\n");
        
    this_player()->delete_temp("sell_value");
    this_player()->delete_temp("sell_count");
    this_player()->delete_temp("sell_unit");
    ob_list = all_inventory(this_player());
    num_sold = 0;
   
    for (i=sizeof(ob_list)-1;i>=0;i--)
    {
      if (ob_list[i])
        if( (member_array(arg, ob_list[i]->parse_command_id_list()) != -1 ) 
            || (arg == get_name(ob_list[i]->name())) )
        {
          if (  ob_list[i]->query_amount()<=0 )
          {
            if ( (value=do_every_sell(ob_list[i])) > 0 )
            {
              this_player()->add_temp("sell_allvalue",value);
              num_sold++;
            }
          }
          else
          {
            sells=do_every_sell(ob_list[i], num-num_sold);
            if ( sells && arrayp(sells) )
            {
              this_player()->add_temp("sell_allvalue",sells[0]);
              num_sold+=sells[1];
            }
          }
        }
          
      if (num_sold == num)
        break;
    }
    
    value = 0;
    this_player()->start_busy(1);
    if (sizeof(this_player()->query_temp("sell_count")) != 0)
    {
      objvalue = this_player()->query_temp("sell_value");
      objcount = this_player()->query_temp("sell_count");
      objunit = this_player()->query_temp("sell_unit");
      msg = "掌柜的唱道："+ sell_msg[random(sizeof(sell_msg))];
      msg2 = "$N把身上的";
      for (i=0;i<sizeof(objvalue);i++)
      {
        msg = msg + keys(objvalue)[i] + CHINESE_D->chinese_number(values(objcount)[i]) + 
              values(objunit)[i] + "，当" + value_string(values(objvalue)[i])+ "；";
        if (sscanf(keys(objvalue)[i],"%s(%s)",obj,obj_file)!=2)
          obj = keys(objvalue)[i];
        msg2 = msg2 + CHINESE_D->chinese_number(values(objcount)[i]) + 
               values(objunit)[i] + obj + ",";
        value = value + values(objvalue)[i];
      }

      if (sizeof(objvalue) == 1)
        msg = msg[0..sizeof(msg)-2] + "。\n";
      else
        msg = msg + "共：" + value_string(value) + "。\n";
      
      write(msg);
      msg2 = msg2[0..sizeof(msg2)-2] + "卖掉。\n";
      message_vision(msg2,this_player());
      pay_player(this_player(),value);
    }
    this_player()->delete_temp("sell_value");
    this_player()->delete_temp("sell_count");
    this_player()->delete_temp("sell_unit");
    this_player()->delete_temp("sell_allvalue");
    
    return 1;
}

int affordable(object me, int amount)
{
        int total;
        object cash, tencash, gold, silver, coin;
    
    tencash = present("tenthousand-cash_money", me);
        cash = present("thousand-cash_money", me);
        gold = present("gold_money",me);
        silver = present("silver_money",me);
        coin = present("coin_money",me);

        total = 0;
        if( tencash) total += tencash->value();
        if( cash) total += cash->value();
        if( gold ) total += gold->value();
        if( silver ) total += silver->value();
        if( coin ) total += coin->value();

        if( total < amount ) return 0;

        return total;
}

//赎回自己典当的物品
int do_retrieve(string arg)
{
        int num;
        int amount, attribute;
        string ob_file;
        object ob;
        object me;
        int afford;
        if( !arg || sscanf(arg, "%d", num)!=1 )
          return notify_fail("指令格式：retrieve|shu|redeem <物品标号>\n");
        me = this_player();
        amount = (int) me->query("vpawn/" + sprintf("%d", num));
        if( !amount )
          return notify_fail("有这个物品标号吗？\n");
        amount = amount * 4 /5;
        if( !(afford = this_player()->can_afford(amount)) )  {
          return notify_fail("你没有足够的钱来赎回。\n");
        }
        else if( afford == 2 )
          return notify_fail("你没有足够的零钱，而银票又没人找得开。\n");
        //复制同属性装备的bug
        if (me->query("npawn/"+sprintf("%d",num))>1 && me->query("apawn/"+sprintf("%d",num))>69)
          return notify_fail("对不起，暂时无法取出该装备。怀疑你利用bug复制物品，请找becool接受调查。\n");
        if( afford = affordable(me, amount) ) {
          me->start_busy(1);
          me->pay_money(amount);
          ob_file = me->query("fpawn/"+sprintf("%d",num));
          ob = new(ob_file);
		  if (!ob||!objectp(ob))
			{
				me->delete("fpawn/"+sprintf("%d",num));
				return notify_fail("这样东西已经不存在于北侠世界了。\n");
			}
          if ( ob->query_amount()>0 )
            ob->set_amount(1);
//现存龙套装改为no pawn
          if (ob->query("taozhuang"))
            ob->set("no_pawn",1);
          ob->move(me);
          attribute = me->query("apawn/"+sprintf("%d",num));
          reset_attribute(me, ob, attribute);
          me->add("npawn/"+sprintf("%d",num),-1);
          if (me->query("npawn/"+sprintf("%d",num))<1)
          {
            me->delete("npawn/"+sprintf("%d",num));
            me->delete("pawn/"+sprintf("%d",num));
            me->delete("vpawn/"+sprintf("%d",num));
            me->delete("fpawn/"+sprintf("%d",num));
            me->delete("apawn/"+sprintf("%d",num));
          }          
          me->save();
          message_vision("$N赎回了$n。\n", me, ob);
          return 1;
        } else
          return notify_fail("你的钱不够。\n");
}

//注销典当的物品
int do_discard(string arg)//物品已经不存在时，可以用来清除记录，腾出空间。
{
        int num;
        int amount;
        string ob_file;
        object ob;
        object me;
        if( !arg || sscanf(arg, "%d", num)!=1 )
          return notify_fail("指令格式：discard <物品标号>\n");
        me = this_player();
        amount = (int) me->query("vpawn/" + sprintf("%d", num));
        if( !amount )
          return notify_fail("有这个物品标号吗？\n");

        ob_file = me->query("fpawn/"+sprintf("%d",num));
        ob = new(ob_file);
        me->add("npawn/"+sprintf("%d",num),-1);
        if (me->query("npawn/"+sprintf("%d",num))<1)
        {
          me->delete("npawn/"+sprintf("%d",num));
          me->delete("pawn/"+sprintf("%d",num));
          me->delete("vpawn/"+sprintf("%d",num));
          me->delete("fpawn/"+sprintf("%d",num));
          me->delete("apawn/"+sprintf("%d",num));
        }          
        me->save();
        message_vision("$N放弃了在当铺的$n。\n", me, ob);
        destruct(ob);
        return 1;
}

//列出已出售给当铺的物品列表
int do_list(string arg)
{
    mapping goods;
    string list, *name;
    int i;
    string tlist;
    string indent;
    object me=this_player();
    int colorlen = 0;

    if( !mapp(goods = findbox()->query_temp("goods")) )
      return notify_fail("当铺目前没有任何货物可卖。\n");
    name = keys(goods);
    if(!sizeof(goods)) 
      return notify_fail("当铺目前没有任何货物可卖。\n");

    list = "你可以购买下列这些东西：\n";
  //write(list);
    list = "";
    i=sizeof(goods);
    while(i--) 
    {
      if(!goods[name[i]]) 
      {
        findbox()->delete_temp("numbers/"+name[i]);
        findbox()->delete_temp("goods/"+name[i]);
        continue;
      }
      //mon 2/4/98 because some items may destruct themselves
      //after being sold.
      if(filter_goods(goods[name[i]],arg))
      {
      //tlist = get_name(name[i]);
        tlist = name[i]+NOR;
        colorlen = color_len(tlist);
        indent = sprintf("%%-%ds",colorlen+30);
        if ( goods[name[i]]->query_amount()>0 )
          list += sprintf(indent+"：%-20s：还剩%s%s\n", tlist,
            value_string(get_price(goods[name[i]],"buy")),
            chinese_number(findbox()->query_temp("numbers/"+name[i])),
            goods[name[i]]->query("base_unit") );
        else
          list += sprintf(indent+"：%-20s：还剩%s%s\n", tlist,
            value_string(get_price(goods[name[i]],"buy")),
            chinese_number(findbox()->query_temp("numbers/"+name[i])),
            goods[name[i]]->query("unit") );
      }
    }
    me->start_more(list);

    return 1;
}

//购买已出售给当铺的物品
int do_buy(string arg)
{
    mapping goods;
    string *name;
    string fname;
    object obj_file, ob;
    int value, oldnum, afford, order;
    int i, j;
    object* inv;
    string arg1, arg2;

    if( this_player()->is_busy() )
      return notify_fail("你现在正忙着呢。\n");

    if( !arg )  {
      write("指令格式：buy 物品名称或ID \n");
      return 1;
    }

    // players are used to the "buy sth from sb" format.
    if( sscanf(arg, "%s from %s", arg1, arg2) == 2 )   {
      arg = arg1;
    }

    if( sscanf(arg, "%s %d", fname, order) != 2 )   {
      fname = arg;
      order = 1;
    }

    if( !mapp(goods = findbox()->query_temp("goods")) )
      return notify_fail("当铺目前没有任何货物可卖。\n");
    
    name = keys(goods);
    if(!sizeof(goods)) 
      return notify_fail("当铺目前没有任何货物可卖。\n");

    j = 0;
    i=sizeof(name);
    while(i--) {
      if(!goods[name[i]]) continue;
        
      if( (member_array(fname, 
        goods[name[i]]->parse_command_id_list()) != -1 ) ||
        (fname == get_name(goods[name[i]]->name())) )
      {
        j++;   
      }
      
      if( j == order )   {
        obj_file = goods[name[i]];

        value = get_price(obj_file,"buy");
        if (this_object()->my_discount(this_player())>1)//an existed discount rate has been set in player pawn shop, but it should not be set in System pawnshop anyway. Zine 2013/2/6
          value=value*(100-this_object()->my_discount(this_player()))/100;
      
        if( !(afford=this_player()->can_afford(value)) )  {
          write("你没有足够的钱。\n");
          return 1; 
        }
        else if( afford == 2 )  {
          write("你没有足够的零钱，而银票又没人找得开。\n");
          return 1;
        }

        ob = new( base_name( obj_file ) );
        if ( ob->query_amount()>0 )
          ob->set_amount(1); 
        ob->set_name(obj_file->query("name"),
        obj_file->parse_command_id_list());
        if (ob->query("no_buy_from_hockshop"))
        {
          write("这样东西是镇店之宝，不出售。\n");
          return 1;
        }
    //comment this to fix the bug in player_hockshop:
    //set the buy price very high. sell it and buy out again
    //the object will be expensive, then sell to normal shop
    //if the player is the owner of player_shop.

//    ob->set("value",value);
    
        pay_shop(this_player(),value);
      
        if ( ob->query_amount()>0 )
          message_vision("$N向当铺买下一" +
            ob->query("base_unit") + ob->query("name") + "。\n", this_player() );
        else
          message_vision("$N向当铺买下一" +
            ob->query("unit") + ob->query("name") + "。\n", this_player() );

        this_player()->start_busy(1);
        this_player()->save();

      //so that the bought item would be the
      //same as the one on sale.

        if(!ob->move(this_player()))
        {
    //pay back player the money he payed
          pay_player(this_player(),value);
          return 0;
        }

        arg = obj_file->query("name")+
          "("+obj_file->query("id")+")";
        oldnum = findbox()->query_temp("numbers/"+arg);
        if(oldnum == 1)  {    
          findbox()->delete_temp("numbers/"+arg);
          findbox()->delete_temp("goods/"+arg);
          if(!living(obj_file)&&!obj_file->is_character()) catch(destruct(obj_file));
        }
        else    {
          findbox()->set_temp("numbers/"+arg, oldnum-1); 
        }
        return 1;
      }
    }

    write("当铺里没有这种货品。\n");

    return 1;
}

int do_quit()
{
  //玩家反映当铺quit丢东西无法捡回，改为quit转移至center
    if(this_player()->is_busy())
    {
        write("你正忙着呢，无法退出。\n");
        return 1;
    }
    if(this_player()->is_fighting())
    {
        write("你正在战斗，无法退出。\n");
        return 1;
    }     
    this_player()->move("/d/city/guangchang");;
  call_other(find_object("/cmds/usr/quit"),"main",this_player(),"");       
    return 1;
}

// no clean up at hockshop to prevent items lose.
int clean_up()  
{
    return 0;
}

//function:Get object's price
//price_type, possible values are:buy,sell
int get_price(object ob,string pricetype)
{
  int value,sale;
  int stored_num=0;
  string index;

  if(!objectp(ob)) return 0;
  if(pricetype == "buy")
  {
    return ob->query("value");
  }
  else if(pricetype == "sell")
  {
    value = ob->query("value");
    sale=ob->query_temp("sale_price");
    if(sale>0 && sale<value) value=sale;
    value = to_int(value*1.0/100.0*80); 

    //decrease the value if there is too many obs already
    index = ob->query("name")+"("+ob->query("id")+")"; 
    stored_num = findbox()->query_temp("numbers/"+index);
    if(stored_num > 1000)
    {
      value = value * (1000.0/stored_num);
      if(value <= 0) value = 1;
    }
    return value;
  }
  return 0;  
}

//function:filter_goods
//ob: good object
//goodtype:the filter. like:book,drug,etc.
int filter_goods(object ob,string goodtype)
{
  if(!goodtype || goodtype == "") return 1;

  if( goodtype == "book" )  
  {
      return mapp(ob->query("skill"));
  }
    else if( goodtype == "drug" )  
  {
    return mapp(ob->query("drug_type"));
  }
    else if( goodtype == "axe" || goodtype == "blade" || goodtype == "dagger" || 
      goodtype == "fork" || goodtype == "hammer" || goodtype == "spear" || goodtype == "mace" || goodtype == "rake" ||
      goodtype == "staff" || goodtype == "stick" || goodtype == "sword" || goodtype == "whip" ||
      goodtype == "throwing" )  
  {
      return ob->query("skill_type") == goodtype;
  }
    else if( goodtype == "archery" )  
  {
      return ob->query("apply/skill_type") == goodtype;
  }
    else if( goodtype == "armor" || goodtype == "boots" || goodtype == "cloth" ||
      goodtype == "finger" || goodtype == "hands" || goodtype == "head" || goodtype == "neck" ||
      goodtype == "shield" || goodtype == "surcoat" || goodtype == "waist" ||
      goodtype == "wrists" )   
  {

     return ob->query("armor_type") == goodtype;
  }
    else   
  {
     return member_array(goodtype,ob->parse_command_id_list()) != -1 ;
  }
  return 0;
}

//always return 1. Because it's system shop
//for player shop, here should check more
//return 0 if money is not enough
int check_balance_enough(int value)
{
  return 1;
}

int pay_shop(object pl,int value)
{
  pl->pay_money(value);
}


int getsinglelimit()
{
  //unlimited, otherwise, too many objects remain in mud.
  //hockshop is in fact a rubbish collector.
  return -1;
}


//定期消耗当铺中的商品 10%，只有系统当铺才会这样。
int clean_goods()
{
  object box = findbox();
  mapping numbers;
  string* indexs;
  int start,end;

  //六分钟一次
  if(time() - query("last_clear_time") > 360)
  {
    numbers = box->query_temp("numbers");  
    if(mapp(numbers))
    {
      indexs = keys(numbers);
      //每次只更新1/10的物品，以免系统负担太重。
      start = random(sizeof(indexs));
      end = start + sizeof(indexs)/10 + 1;
      if(end > sizeof(indexs)) end = sizeof(indexs);

      for(int i=start;i<end;i++)
      {
        if(i%10 == 0)
        {
          reset_eval_cost();
        }
        if(numbers[indexs[i]] > 300)
        {
          numbers[indexs[i]] = numbers[indexs[i]]*9/10;
        }
      }
    }
    set("last_clear_time",time());
  }
  remove_call_out("clean_goods");
  call_out("clean_goods",120);
}

//被摧毁前由/adm/simul_efun/object.c通知
int pre_destruct()
{
  save_shop();
}

//可售物品检查
int check_can_sell_or_not(object ob)
{
    if(ob->query("no_sell")) return 0;

    if (ob->query("shaolin"))
    {
      write("少林的宝物小的可不敢要呀！\n");
      return 0;
    }
    if (ob->query("chaoting"))
    {
        write("大内的宝物小的可不敢要呀！\n");
        return 0;
    }
    if (ob->query("zijin"))
    {
        write("大内的宝物小的可不敢要呀！\n");
        return 0;
    }

    if (ob->query("dalunsi")) 
    {
        write("大轮寺的宝物小的可不敢要呀！\n");
        return 0;
    }
    if (ob->query("mingjiao"))
    {   
      write("魔教的财产小的可不敢要呀！\n");
      return 0;
    }
    if( ob->query("money_id") )  
    {
      write("你要卖「钱」？\n");
      return 0;
    }
    if(ob->query("no_drop"))
    {
      write("这样东西不能离开你。\n");
      return 0;
    }

    if( (int)ob->query("skill_type") && (int)ob->query("rigidity")<50) 
    {
        write("掌柜的说：我们不收破烂的兵器。\n");
        return 0;
    }
    if(ob->query("unique"))
    {
        write("掌柜的说：这种宝物我们可不敢要!\n");
        return 0;
    }

    if( ob->query("material") == "ice" )
    {
      write("掌柜的说：冰的东西我们这里没法存放。\n");
      return 0;
    }

    if(sizeof(all_inventory(ob)) > 0)
    {
      write("掌柜的说：客官您这"+ob->name()+"里面还有东西呢。\n");
      return 0;
    }

    return 1;
}
