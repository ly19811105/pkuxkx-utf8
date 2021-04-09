#pragma save_binary
// player_hockshop.c. 继承自经过重构的/feature/hockshop.c
// created by Jason@pkuxkx
// 本文所有buy,sell，都是以买家为中心的。

/*
1. 由玩家经营，每4个小时竞标一次，价高者得。竞标款收归系统。
2. 当铺只收购店主指定的物品
3. 店主可以设定物品的收购价和卖出价
4. 店主可以投资当铺，扩大当铺可以买卖的物品种类和存放的物品数量。
   级别 种类 数量
     1 10 100
     2 20 200
线性递增，上限是level 10。每一级别投资金额是 500 * level * level 两黄金。
5. 竞标时，店铺等级和货物价值都会计算在内。其中货物价值用原价，对当前店主，
不需要付出这部分。
6. 所有货物都保存，当机不消失。
7. 玩家卖东西到当铺，当铺付出的钱来自店主。所以店主必须向当铺注入一笔资金。
   如果资金耗尽，就不能交易。
8. 不提供典当/赎回功能。
9. 店主可以给当铺起名字。
10.系统收取店主盈利的20%

普通玩家命令
sell,buy,bid
店主命令
cun --- 注入资金
qu --- 提钱
add --- 增加收购的货物种类
  格式：add name,id,buy_value,sell_value,limits
  举例：add 金创药,jinchuang yao,20000,25000,15
  以20 silver收购金创药，25silver卖出，库存不超过15个
del --- 删除一种货物种类
  格式：add number
cha --- 查询货物种类信息，查询店铺信息。
putin --- 上货，店主可以把自己得来的货物放进当铺里销售。货物也必须在收购列表中。
getout --- 取货，店主拿自己的东西

invest --- 投资，升级店铺。

*/
#include <ansi.h>
#include <localtime.h>
#define MIN_DISCOUNT 10
#define MAX_DISCOUNT 90
#define MAX_SHOP_BALANCE 2000000000
inherit F_HOCKSHOP;


//收购货物信息保存在query("good_list")内。结构如下
/*good_list = ([
"/d/city/obj/jinchuang.c":([
  "buy_price":1000,//玩家买入价
  "sell_price":800,//玩家卖出价
  "limit":10,//店铺最大收购量
  ]),
"/clone/weapon/yuxiao.c":([
  "buy_price":1200,
  "sell_price":900,
  "limit":20,
  ])
]);
*/

//店铺资金:query("balance")
//店铺等级:query("level")
//店铺主人:query("owner")
//店铺名字:query("name")

#define CHANGE_OWNER_VAL 86400*5

int sort_good_list(string name1,string name2);
int gettypelimit();
int getsinglelimit();
int getnextlevelcost();
int getnextlevelskill();
int getcapitallimit();

int getbidcost();

string get_base_name(object ob);

//竞标
int check_bidding();
//广告
int publish_ad();
string look_paizi();
//应该由具体的房间在create里调用
void setup_shop()
{
  string shortname,tmp;
  load_shop();

    set("item_desc", ([
        "paizi" : (:look_paizi:),
        ]));


  set("channel_id",query("short"));
  remove_call_out("check_bidding");
  call_out("check_bidding",80);

  remove_call_out("publish_ad");
  call_out("publish_ad",300);
}

void init()
{
  
  ::init();

  add_action("do_bid", "bid");
  add_action("do_drawback", "drawback");
  add_action("do_checkshare","checkshare");
  //查看货物种类和店铺信息
  add_action("do_query", "query");
  add_action("do_vip","vip");
  //店主的命令
  if(this_player()->query("id") == query("owner") || wizardp(this_player()))
  {  //自定义折扣率
    add_action("set_discount_rate","discount");
    add_action("unset_discount","undiscount");
    //自定义铺子名称
    add_action("do_name", "name");
    //增加货物种类
    add_action("do_add", "add");
    //删除货物种类
    add_action("do_del", "del");
    //向当铺注入资金
    add_action("do_cun", "cun");
    //从当铺取钱
    add_action("do_qu", "qu");
    //上货，等于店主‘卖’东西给店里
    add_action("do_putin", "putin");
    //取货
    add_action("do_getout", "getout");
    //投资，让店铺升级。
    add_action("do_invest", "invest");
    //盘点，升级技能点
    add_action("do_check","check");
    //设置广告
    add_action("do_setad","setad");
    //设置招牌描述
    add_action("do_setdesc","set_desc");
    //在这里检查，删除店主的bid_money。是个挺傻的办法。
    //竞标成功者的竞标金是要归系统所有的。
    //bug：如果竞标成功后店主一直不来，下次换了店主，他可以来取回竞标金。
    //不过，如果他不出现，当铺里就没有钱，无法开张。所以这个方案也可以。
        //最好的方案是在获得经营权的时候删除，但是当时玩家可能不在线。
        this_player()->delete("hockshop_"+unique_id+"/bid_money");    
  }

}
string paizi_desc()
{
  if (stringp(query("paizi_desc"))&&strwidth(query("paizi_desc"))>0)
  {
    return query("paizi_desc");
  }
  return "";
}
string look_paizi()
{
  string msg;
  msg="    卖东西：sell id(或name) [number]
    买东西：buy id(或name)
    看可卖物品：list
    估价：value id
    竞标：bid 钱数，单位是黄金
    取回竞标金:drawback
    旧店主取回资金:drawback
    查看红利状况:checkshare
    查询状态:query
    查询打折状况:vip\n";
  if (paizi_desc()!="")
  msg+="    "+HBWHT+HIR+"【"+paizi_desc()+"】"+NOR+"\n\n";
  if (this_player()->query("id") == query("owner"))
  msg+="    店主命令：
    增加货物种类:add
      格式：add name,id,buy_value,sell_value,limits
      举例：add 金创药,jinchuang yao,25000,20000,15
      以20 silver收购金创药，25silver卖出，库存不超过15个
    删除货物种类:del
      首先用query查看货物列表，然后del 序号。
    向当铺注入资金:cun
      cun 钱数，单位是铜板
    从当铺取钱:qu
      qu 钱数，单位是铜板
    上货，等于店主‘卖’东西给店里:putin
      putin 货物ID,必须是在货物种类中的货物。
    取货:getout
      getout 货物ID
    投资，让店铺升级:invest
    盘点，check
    定义店铺名，name
    设定折扣率，discount
    删除折扣率，undiscount
    设置描述，set_desc，将出现在招牌里\n";
    return msg;
}
int my_discount(object me)
{
  string id;
  int *num;
  if (!userp(me))
  return 0;
  id=me->query("id");
  for (int i=0;i<sizeof(num=query("discount_rates"));i++)
  {
    if (member_array(id,query("discounts/"+num[i]))!=-1)
      return num[i];
  }
  return 0;
}
int do_vip()
{
  int rate=my_discount(this_player());
  if (this_player()->query("id") == query("owner"))
  write ("你是这家店的东家。\n");
  else if (rate>0)
  write ("你是这里的常客，在这里购物将享受"+rate+"%的折扣。\n");
  else
  write ("你在这里不享受任何折扣。\n");
  return 1;
}

int del_discount(string id)
{
  int *num;
  string *ids;
  for (int i=0;i<sizeof(num=query("discount_rates"));i++)
  {
    if (member_array(id,query("discounts/"+num[i]))!=-1)
    {
      ids=query("discounts/"+num[i]);
      ids-=({id});
      set("discounts/"+num[i],ids);
      save();
      return 1;
    }
  }
  return 0;
}
int unset_discount(string arg)
{
  if (del_discount(arg)==1)
  write("你将"+HIY+arg+NOR+"从折扣列表中清除。\n");
  else
  write(arg+"并不在你的折扣列表中。\n");
  return 1;
}
int show_discount_list(object me)
{
  int *num;
  if (!sizeof(num=query("discount_rates")))
  {
    write(HIW+"本店未设定任何折扣。\n"+NOR+"请输入你要设定享受折扣的人物，命令格式是discount <id> to <折扣率>\n或者输入一个折扣率，命令格式是discount <折扣率>\n");
    return 1;
  }
  for (int j=0;j<sizeof(num);j++)
  {
    write("本店享受"+HIR+num[j]+"%"+NOR+"折扣的顾客有：\n");
    for (int i=0;i<sizeof(query("discounts/"+num[j]));i++)
    {
      write(HIY+query("discounts/"+num[j])[i]+NOR);
    }
    write("\n");
  }
  return 1;
}
int set_discount_rate(string arg)
{
  int discount,*rates=({});
  string id,*ids=({});
  if (!arg)
  {
    return show_discount_list(this_player());
  }
  if (sscanf(arg, "%s to %d", id, discount)!=2&&sscanf(arg,"%d",discount)!=1&&sscanf(arg,"%d cancel",discount)!=1)
  {
    write("请输入你要设定享受折扣的人物，命令格式是discount <id> to <折扣率>\n或者输入一个折扣率，命令格式是discount <折扣率>，比如 discount 60表示折扣率为60%。\n");
    write("折扣率范围在"+MIN_DISCOUNT+"到"+MAX_DISCOUNT+"之间。数字越大表示给出的折扣越高。\n");
    return 1;
  }
  if (!stringp(id))//设定折扣率
  {
    if (arg==discount+" cancel")
    {
      if (!arrayp(query("discount_rates"))||member_array(discount,query("discount_rates"))==-1)
      {
        write("本店并无"+HIR+discount+"%"+NOR+"这个折扣率，请用discount命令查询所有折扣率。\n");
        return 1;
      }
      rates=query("discount_rates");
      rates-=({discount});
      set("discount_rates",rates);
      delete("discounts/"+discount);
      save();
      write("你删除了"+HIR+discount+"%"+NOR+"这个折扣幅度，享受这个折扣的所有玩家将不再享受任何折扣。\n");
      return 1;
    }
    if (discount<MIN_DISCOUNT||discount>MAX_DISCOUNT)
    {
      write(BLINK+HIR+discount+"%"+NOR+"超过了允许的折扣范围，请重新设定。\n");
    }
    else if (query("discounts/"+discount))
    {
      write(HIR+discount+"%"+NOR+"这个折扣幅度已经存在，请添加玩家。\n");
    }
    else if (sizeof(query("discounts"))>=5)
    {
      write("目前每家店铺只允许五种折扣幅度。如需取消某种折扣幅度，请输入discount <折扣率> cancel。\n");
    }
    else
    {
      set("discounts/"+discount,ids);
      if (arrayp(query("discount_rates")))
      rates=query("discount_rates");
      rates+=({discount});
      set("discount_rates",rates);
      save();
      write("你建立了"+HIR+discount+"%"+NOR+"这个折扣幅度，你可以继续用discount <id> to "+discount+"这个命令增加可享受这个折扣的玩家。\n");
    }
  }
  else
  {
    if (!arrayp(ids=query("discounts/"+discount)))
    {
      write(HIR+discount+"%"+NOR+"这个折扣幅度不存在，请先设定这个折扣范围，命令是discount "+discount+"。\n");
    }
    else if (sizeof(ids)>=20)
    {
      write(HIR+discount+"%"+NOR+"这个折扣幅度享受的玩家列表超过20人，如需添加新玩家，请删除一些不常使用的玩家，命令是undiscount <id>。\n");
    }
    else if (member_array(id,ids)!=-1)
    {
      write(HIY+id+NOR+"已经在享受"+HIR+discount+"%"+NOR+"这个折扣幅度。\n");
    }
    else
    {
      del_discount(id);
      ids+=({id});
      set("discounts/"+discount,ids);
      save();
      write("你将"+HIY+id+NOR+"加入了享受"+HIR+discount+"%"+NOR+"折扣的列表。\n");
    }
  }
  return 1;
}
int do_pawn(string arg)
{
  write("抱歉，本店暂时不提供典当业务。\n");
    return 1;
}

varargs mixed do_every_sell(object ob, int num)
{
  //check whether ob is in the good list
  string basename;
  mixed value=0;
  string name;

  basename = get_base_name(ob);
  if (ob->query("no_sell_in_playershop"))
  {
    write("抱歉，这样东西本店不收购。\n");
  }
  else if(query("good_list/"+basename)) 
  {
    name = query("good_list/"+basename+"/name")+"("+query("good_list/"+basename+"/id")+")";
    if(findbox()->query_temp("numbers/"+name)+num >= query("good_list/"+basename+"/limits"))
    {
      write("抱歉，本店规模有限，不能再收购您的货物了。\n");      
    }
    else
    {
      if ( !num )
        value = ::do_every_sell(ob);
      else
        value = ::do_every_sell(ob,num);
    }
  }
  else
  {
    write("抱歉，这样东西本店不收购。\n");
  }

  return value;
}

int do_retrieve(string arg)
{
  write("抱歉，本店暂时不提供此项业务。\n");
  return 1;
}


//function:Get object's price
//price_type, possible values are:buy,sell
int get_price(object ob,string pricetype)
{
  string basename;
  mapping good_list;

  if(!objectp(ob)) return 0;
  if(pricetype != "buy" && pricetype != "sell") return 0;

  basename = get_base_name(ob);
  good_list = query("good_list");
  if(!mapp(good_list) || !good_list[basename]) return 0;
//  printf("ob name:%s,ob value:%d\n",basename,good_list[basename][pricetype+"_value"]);
  return good_list[basename][pricetype+"_value"];
}


int check_balance_enough(int value)
{
  if(value > query("balance")) return 0;
  return 1;
}

int pay_shop(object pl,int value)
{
  int taxrate = BUSINESS_D->get_tax("hockshop");
  mapping invests;
  string* ids;
  int* data;
  pl->pay_money(value);

  //收税
  value = value /1000 * (1000-taxrate);

  //分红！投资者才可以分红，分红公式:
  //level 1: 1/1000
  //level 2: 2/1000
  //level n: n/1000
  //投资到level 10者，可以获得和系统一样的收益比例
  invests = query("invests");
  if(mapp(invests))
  {
    ids = keys(invests);
    for(int i=0;i<sizeof(ids);i++)
    {
      //data = ({分红比例,积累收益})
      data = invests[ids[i]];
      value = value /1000 * (1000-data[0]);
      data[1] += value * data[0]/1000;
      invests[ids[i]] = data;
    }
  }
  if(query("balance") + value > MAX_SHOP_BALANCE)
  set("balance",MAX_SHOP_BALANCE);
  else
  add("balance",value);
}

void pay_player(object who, int amount)
{
  if(query("balance") < amount) 
  {
    write("当铺没钱了！不应该执行至此。报告bug吧！\n");
    return;
  }
  add("balance",-amount);
  ::pay_player(who,amount);  
}


//店主操作
int do_name(string arg)
{
  int i;
  string *legal_marks=({"馆","楼","坊","店","铺","号","肆"}),color="";
  string *colors=({"HIW","WHT","HIC","CYN","HIR","RED","HIG","GRN","HIM","MAG","HIY","YEL","HIB","BLU"});
  string *true_colors=({HIW,WHT,HIC,CYN,HIR,RED,HIG,GRN,HIM,MAG,HIY,YEL,HIB,BLU});
  mapping exits;
  mixed *h_exits=({});
  object exit;
  if (time()-query("shop_change_name")<86400)
  {
    write("才刚刚挂上招牌，老换名字是不合适的。\n");
    return 1;
  }
  if (this_player()->query("balance")<30000000)
  {
    write("你的账户小于三千两黄金，每次注册新的店铺名需要三千两黄金。\n");
    return 1;
  }
  if (!arg)
  {
    write("你要把这间店铺命名为什么？\n");
    return 1;
  }
  if (sscanf(arg,"%s %s",arg,color)==2)
  {
    i=member_array(color,colors);
    if (i==-1)
    {
      write("店铺招牌的颜色不在北侠定义的范围。\n");
      return 1;
    }
    else
    color=true_colors[i];
  }
  i = strwidth(arg);
  if (i < 2 || i > 6) 
  {
    write("你给店铺取的名字必须是 2 到 6 个中文字才行。\n");
    return 1;
  }
  while(i--)
    if( !is_chinese(arg[i..<1]) ) 
  {
    write("得用中文字取名才行。\n");
    return 1;
  }
  if ( !LOGIN_D->check_legal_name(arg) ) 
  {
    write("这个名字被禁止使用，重取。\n");
    return 1;
  }
  i = strwidth(arg);
  if (member_array(arg[i-2..i-1],legal_marks)==-1)
  {
    write("店铺的名字必须以馆、楼、坊、店、铺、号或肆结尾。\n");
    return 1;
  }
  if (color+arg+NOR==query("short"))
  {
    write("这不就是以前的招牌吗？\n");
    return 1;
  }
  this_player()->add("balance",-30000000);
  this_player()->save();
  set("short",color+arg+NOR);
  delete("realmap");
  exits=query("exits");
  h_exits=values(exits);
  for (i=0;i<sizeof(h_exits);i++)
  {
    exit=load_object(h_exits[i]);
    exit->delete("realmap");
  }
  set("shop_change_name",time());
  save();
  write("你将新的招牌"+query("short")+"挂了上去，官府收取了三千两黄金作为注册费。\n");
  CHANNEL_D->do_channel(this_object(), "jy", HIY+query("short")+HIY+"在"+TASK_D->place_belong(this_object())+"重新开业，欢迎新老顾客惠顾。" NOR);
  return 1;
}
//add name,id,buy_value,sell_value,limits
int do_add(string arg)
{
  string name,id;
  int buy_value,sell_value,limits;
  object ob;
  object pl = this_player();
  string basename;


  if(pl->is_busy())
  {
    write("掌柜的，您正忙着哪。\n");
    return 1;
  }

  if(!arg || sscanf(arg,"%s,%s,%d,%d,%d",name,id,buy_value,sell_value,limits) != 5)
  {
    write("命令格式:add name,id,buy_value,sell_value,limits。注意buy,sell是以买家为中心的。\n");
  }
  else
  {
    ob = present(id,pl);
    if(!objectp(ob))
    {
      write(id+"\n");
    }
    if(objectp(ob) && get_name(ob->query("name")) == name && check_can_sell_or_not(ob) == 1 && 
      !ob->query("no_drop") && ob->query("value") > 0 && !ob->query("unique") && !ob->query("money_id"))
    {
      basename = get_base_name(ob);

      if(buy_value > 0 && sell_value > 0 && limits > 0 && limits <= getsinglelimit())
      {
        if(mapp(query("good_list")) && sizeof(query("good_list")) >= gettypelimit() && !query("good_list/"+basename))
        {
          write(sprintf("你的店铺已经经营了%s种货物，要想更多，必须升级。升级到更高等级的费用是%s和%s级商业技能\n",
            chinese_number(sizeof(query("good_list"))),
            value_string(getnextlevelcost()),
            chinese_number(getnextlevelskill())
            ));
          return 1;
        }
        set("good_list/"+basename,([
          "name":name,
          "id":id,
          "buy_value":buy_value,
          "sell_value":sell_value,
          "limits":limits
          ]));
        //save_shop();
        pl->start_busy(2);
        write("行啦！以后我们就按这个上货出货。\n");
      }
      else
      {
        write(sprintf("掌柜的，您这不大对吧，是不是咱的仓库该扩建了？每种货物咱只能存%s件。要不就是您的价格定的不太对。\n",chinese_number(getsinglelimit())));
      }
    }
    else
    {
      write("你身上必须有这件物品，并且符合销售条件。\n");
    }
  }
  return 1;
}

int do_query()
{
  mapping good_list = query("good_list");
  string* basenames;
  string line;
  mixed* times;
  int hour;
  int newday = 0;
    string indent;

  write(query("short")+"\n");
  if(query("owner"))
  {
    write("大掌柜:"+HIY+query("owner")+"\n"NOR);
  }

  write(sprintf(WHT"等级:%s，升级到更高级别需要%s。\n现有资金:%s\n"NOR,chinese_number(query("level")),value_string(getnextlevelcost()),value_string(query("balance"))));

  times = localtime(time());
  hour = times[LT_HOUR];
  if(hour < 9)
  {
    hour = 9;
  }
  else if(hour < 21)
  {
    hour = 21;

  }
  else
  {
    hour = 9;
    newday = 1;
  }

  write("下次招募新店主的时间是");

  write(ctime(query("next_change_owner_time"))+"，请在此时间之前投标。(bid)\n");

  write("==================================================================\n\n收购商品清单：\n");

    
  if(mapp(good_list))
  {
    line = sprintf(BBLU"%-8s%-20s%-20s%-30s%-30s%-8s\n"NOR,
      "序号","名字","ID","收购价","卖出价","上限");

    write(line);
    basenames = keys(good_list);
    basenames = sort_array(basenames,"sort_good_list");
    for(int i=0;i<sizeof(basenames);i++)
    {
            indent = sprintf("%%-%ds",color_len(good_list[basenames[i]]["name"])+20);        
      line = sprintf("%-8d"+indent+"%-20s%-30s%-30s%-8d\n",i+1,
        good_list[basenames[i]]["name"],
        good_list[basenames[i]]["id"],
        value_string(good_list[basenames[i]]["sell_value"]),
        value_string(good_list[basenames[i]]["buy_value"]),
        good_list[basenames[i]]["limits"]);
      write(line);
    }
  }
  else
  {
    write("目前本店没有任何进货计划！\n");
  }
  return 1;
}

int do_cun(string arg)
{
  int amount = 0;
  object pl = this_player();

  if(!arg || sscanf(arg,"%d",amount) != 1) 
  {
    write("请输入存款金额的阿拉伯数字，单位是铜板。\n");
    return 1;
  }
  if(amount <= 0)
  {
    write("掌柜的，您要是想取钱就用qu。\n");
    return 1;
  }

  if(pl->query("balance") < amount)
  {
    write("掌柜的，您好像没这么多钱了，要不要找钱眼开借点高利贷？我跟他小舅子熟。\n");
    return 1;
  }
  if(query("balance") + amount > getcapitallimit())
  {
    write("掌柜的，咱的店小，用不了这许多钱。\n");
    return 1;
  }
  pl->add("balance",-amount);
  add("balance",amount);
  write("掌柜的，一共是"+value_string(amount)+"我给您收好了。\n");
  return 1;
}

int do_qu(string arg)
{
  int amount = 0;
  object pl = this_player();
  if(!arg || sscanf(arg,"%d",amount) != 1) 
  {
    write("请输入取款金额的阿拉伯数字，单位是铜板。\n");
    return 1;
  }
  if(amount <= 0)
  {
    write("掌柜的，您要是想存钱就用cun。\n");
    return 1;
  }
  if(query("balance") < amount)
  {
    write("掌柜的，咱店里没这么些现金了，要不您处理掉一些货物，回笼资金？\n");
    return 1;
  }
  pl->add("balance",amount);
  add("balance",-amount);
  write("掌柜的，一共是"+value_string(amount)+"，请您收好了。\n");
  return 1;
}

int do_del(string arg)
{
  int index = 0;
  mapping good_list;
  string* basenames;

  if(!arg || sscanf(arg,"%d",index) != 1)
  {
    write("掌柜的，您想把哪个货物下架，只要输入query,然后del 序号就可以了。\n");
    return 1;
  }

  if(index <= 0)
  {
    write("掌柜的，请吩咐要下架哪个编号的货物？\n");
    return 1;
  }

  good_list = query("good_list");

  if(mapp(good_list))
  {
    basenames = keys(good_list);
    basenames = sort_array(basenames,"sort_good_list");
    if(index > sizeof(basenames))
    {
      write("掌柜的，店里没有这么多货物啊。\n");
      return 1;
    }
    index--;
    write("掌柜了，按您的吩咐，以后咱不经营"+good_list[basenames[index]]["name"]+"了。\n");
    map_delete(good_list,basenames[index]);
  }
  return 1;
}

int do_invest()
{
  object pl = this_player();
  int cost = getnextlevelcost();
  int skill = getnextlevelskill();

  int* data;
  if(query("level") > BUSINESS_D->get_max_shop_level())
  {
    write("掌柜的，咱的店铺已经是天下最大，最高的了。\n");
    return 1;
  }

  if(cost > pl->query("balance"))
  {
    write("掌柜的，您好像没这么多钱了，要不要找钱眼开借点高利贷？我跟他小姨子熟。\n");
    return 1;    
  }

  if(pl->query_skill("business",1) < skill)
  {
    write("掌柜的，您的经商之道。。。至少需要"+chinese_number(skill)+"级。\n");
    return 1;    
  }

  pl->add("balance",-cost);
  add("level",1);
  write("掌柜的！咱的店铺又扩啦！现在咱是"+chinese_number(query("level"))+"级店铺了。\n");
  
  //投资者可以获得红利。data = ({红利千分比,红利收益金额})
  data = query("invests/"+pl->query("id"));
  if(arrayp(data))
  {
    data[0] += query("level");
  }
  else
  {
    data = ({query("level"),0});
  }
  set("invests/"+pl->query("id"),data);
  write("从此以后，您可以从店面的流水中获得千分之"+chinese_number(data[0])+"的红利！\n");
  return 1;
}

int do_check()
{
  object pl = this_player();
  int skpt = 0;  
  int lvlpt = 0;
  int sklvl = 0;

  skpt = query("skill_improved/"+pl->query("id"));
  sklvl = pl->query_skill("business");

  if(skpt && skpt > 0)
  {
    write("恭喜掌柜的，您的经商之道又提升了"+chinese_number(skpt)+"点！\n");
    while(skpt > 0)
    {
      lvlpt = sklvl*sklvl+1;
      if(skpt > lvlpt) 
      {
        skpt -= lvlpt;
      }
      else
      {
        lvlpt = skpt;
        skpt = 0;
      }
      pl->improve_skill("business",lvlpt);
    }
    delete("skill_improved/"+pl->query("id"));
  }  
  else
  {
    write("掌柜的，最近我们好像没什么长进。\n");
  }
  return 1;
}

int do_setad(string arg)
{
  if(!arg || arg == "")
  {
    write("掌柜的，您要发布什么广告？\n");
    return 1;
  }
  arg = F_NAME->replace_color(arg);
  set("advertisement",arg);
  write("掌柜的，我们的广告挂出去啦，您就等着顾客盈门吧！\n");
  return 1;
}

int do_bid(string arg)
{
  object pl = this_player();
  string* bidders;
  object ob;

  int amount = 0;

  if(!pl->is_realuser())
  {
    write("您在江湖上籍籍无名，毫无信用可言，不能担任本店掌柜。(help realuser)\n");
    return 1;
  }
  if(pl->query("level")<40)
  {
    write("您等级不够，无法经营这么大的当铺。\n");
    return 1;
  }

  if(query("no1_bidder"))
  {
    write(sprintf("目前最高的投标者是%s,他出资%s\n",query("no1_bidder"),value_string(query("bid_money"))));
  }

  if(!arg || sscanf(arg,"%d",amount) != 1) 
  {
    write("请输入您要竞标金额的阿拉伯数字，单位是黄金。\n");
    return 1;
  }
  if(pl->is_busy())
  {
    write("您正忙着呢。\n");
    return 1;
  }

  if(amount <= 0)
  {
    write("您怎么也得出‘点’钱吧！\n");
    return 1;
  }

  if(pl->query("id") == query("no1_bidder"))
  {
    write("您已经是目前最高价的竞标者了。\n");
    return 1;
  }

  amount *= 10000;
  if(amount < getbidcost()+10000)
  {
    write("您至少要出到"+value_string(getbidcost()+10000)+"才可能成为这家店的店主。\n");
    return 1;
  }

  if(amount > pl->query("balance")+pl->query("hockshop_"+unique_id+"/bid_money"))
  {
    write("您好像没有那么多钱。\n");
    return 1;
  }

  if(amount < pl->query("hockshop_"+unique_id+"/bid_money"))
  {
    write("您以前的竞标金还没取回呢。请drawback。\n");
    return 1;
  }
  
  pl->add("balance",-(amount - pl->query("hockshop_"+unique_id+"/bid_money")));
  pl->set("hockshop_"+unique_id+"/bid_money",amount);

  set("bid_money",amount);
  set("no1_bidder",pl->query("id"));

  write("恭喜，您是目前的最高竞标者："+value_string(amount)+"\n");



  if(!query("bidders") || !arrayp(query("bidders")))
  {
    set("bidders",({pl->query("id")}));
  }
  else
  {
    if(member_array(pl->query("id"),query("bidders")) == -1)
    {
      set("bidders",query("bidders") + ({pl->query("id")}));
    }
  }

  bidders = query("bidders");
  for(int i=0;i<sizeof(bidders);i++)
  {
    ob = find_player(bidders[i]);
    if(objectp(ob) && bidders[i] != pl->query("id"))
    {
      tell_object(ob,pl->query("name")+"以"+value_string(amount)+"竞标"+query("short")+"\n");
    }
  }
  
  CHANNEL_D->do_channel(this_object(), "jy", HIY+pl->query("name")+"以"+value_string(amount)+"竞标"+query("short")+NOR);
  pl->start_busy(2);

  return 1;

}

int do_putin(string arg)
{
  string goodname;
  int num;
  object* invs;
  object pl = this_player();
  int value = 0, *sells;
  int sellnum = 0;
  string cnname;

  if(!arg) 
  {
    write("掌柜的，您要上货，用putin 货物ID就行。货物一定要在您身上。\n");
    return 1;
  }

  if(sscanf(arg,"%s %d",goodname,num) != 2)
  {
    goodname = arg;
    num = 1;
  }

  invs = all_inventory(pl);
  for(int i=0;i<sizeof(invs);i++)
  {
    if( (member_array(goodname, 
        invs[i]->parse_command_id_list()) != -1 ) ||
      (goodname == get_name(invs[i]->name())) )  
    {
      cnname = invs[i]->name();
      if ( invs[i]->query_amount()<=0 )
      {
        value = do_every_sell(invs[i]);
        if(value > 0) sellnum++;
      }
      else
      {
        sells = do_every_sell(invs[i], num-sellnum);
        if ( sells && arrayp(sells) )
        {
          sellnum+=sells[1];
        }
      }
      if(sellnum >= num) break;      
    }
  }

  if(sellnum > 0)
  {
    write("掌柜的，这次咱又进了"+chinese_number(sellnum)+"件"+cnname+"\n");
  }
  return 1;
}

int do_getout(string arg)
{
  object good,ob;
  string goodname;
  int oldnum = 0;

  if(!arg) 
  {
    write("掌柜的，您要取货，用getout 货物ID就行。\n");
    return 1;
  }
  good = present(arg,findbox());
  if(objectp(good))
  {
      ob = new( base_name( good ) ); 
      if ( ob->query_amount()>0 )
        ob->set_amount(1); 
      ob->set_name(good->query("name"),
      good->parse_command_id_list());
      ob->set("value",good->query("value"));
      ob->move(this_player());
      write("掌柜的，"+ob->query("name")+"您自己保管吧。\n");

      goodname = good->query("name")+
      "("+good->query("id")+")";
//    goodname = get_name(goodname);

      oldnum = findbox()->query_temp("numbers/"+goodname);
      if(oldnum == 1)  
    {    
      findbox()->delete_temp("numbers/"+goodname);
      findbox()->delete_temp("goods/"+goodname);
      if(!living(good)&&!good->is_character()) catch(destruct(good));
      }
      else    
    {
      findbox()->set_temp("numbers/"+goodname, oldnum-1); 
      }
  }
  else
  {
    write("掌柜的，咱店里没这样货物。\n");
  }

  return 1;
}
//取回竞标金或者前任店主的剩余资金
//或者投资者的红利
int do_drawback()
{
  object pl = this_player();
  int dosth = 0;
  mapping invests;
  string* ids;
  int* data;


  if(query("legacy_balance/"+pl->query("id")))
  {
    pl->add("balance",query("legacy_balance/"+pl->query("id")));
    write("这是您留在本店的资金，一共是:"+value_string(query("legacy_balance/"+pl->query("id")))+"，请收好！感谢您曾经为本店付出的汗水。\n");
    delete("legacy_balance/"+pl->query("id"));
    dosth = 1;
  }
  
  if(pl->query("hockshop_"+unique_id+"/bid_money"))
  {
    if(query("no1_bidder") == pl->query("id"))
    {
      write("作为目前出价最高的竞标者，您不能取回竞标金。\n");
      return 1;
    }
    if(pl->query("id") == query("owner")) return notify_fail("你已经中标了，还想取回竞标金，太无耻了吧！\n");
    pl->add("balance",pl->query("hockshop_"+unique_id+"/bid_money"));
    write("这是您的竞标金，一共是:"+value_string(pl->query("hockshop_"+unique_id+"/bid_money"))+"。希望您下次能够中标！\n");
    pl->delete("hockshop_"+unique_id+"/bid_money");
    dosth = 1;
  }
  //收税

  invests = query("invests");
  if(mapp(invests))
  {
    ids = keys(invests);
    for(int i=0;i<sizeof(ids);i++)
    {
      if(ids[i] == pl->query("id"))
      {
        data = invests[ids[i]];
        if(data[1] > 0)
        {
          pl->add("balance",data[1]);
          write("老板，您的投资红利一共是"+value_string(data[1])+"！\n");

          data[1] = 0;
          invests[ids[i]] = data;
          dosth = 1;
        }
        break;
      }
    }
  }
  if(dosth != 1)
  {
    write("客官，您要买点什么吗？随便看看也行。\n");
  }
  return 1;
}

int do_checkshare()
{
  object pl = this_player();
  string id = pl->query("id");
  int* data;
  int dosth = 0;
  if(query("invests/"+id))
  {
    data = query("invests/"+id);
    if(arrayp(data) && sizeof(data) == 2)
    {
      write("您在本店有权获得千分之"+chinese_number(data[0])+"的营业红利。\n");
      write("目前您在本店尚未支取的红利还有"+value_string(data[1])+"。您可以马上支取(drawback)。\n");
      dosth = 1;
    }
  }

  if(dosth == 0)
  {
    write("您在本店没有股权。您可以先bid成为本店店主，然后投资本店(invest)，然后就可以分红了。\n");
  }
  return 1;
}
int sort_good_list(string name1,string name2)
{
  return strcmp(name1,name2);
}

int gettypelimit()
{
  return (query("level")+1)*10;
}

int getsinglelimit()
{
  return (query("level")+1)*100;
}

int getcapitallimit()
{
  return ((query("level")+1)*10000000>MAX_SHOP_BALANCE)?MAX_SHOP_BALANCE:(query("level")+1)*10000000;
}

int getnextlevelcost()
{
  return (query("level")+2)*(query("level")+2)*5000000;
}

int getnextlevelskill()
{
  return (query("level")+2)*(query("level")+2)*5;
}


//竞标时所需金额
//max(最高投标金,当铺基本价值)
//店铺基本价值=level*level*100g
int getbidcost()
{
  int shop_value = 0;
  shop_value = (query("level")+1)*(query("level")+1)*1100000;
  if(query("bid_money") && query("bid_money") > shop_value)
  {
    return query("bid_money");
  }
  return shop_value;
}

//玩家当铺不清除物品
int clean_goods()
{
  return 1;
}

string get_base_name(object ob)
{
  return replace_string(base_name(ob),"/","_-_");
}



int check_bidding()
{string str_len = query("short");
  mixed* times = localtime(time());
  if (str_len=="天字第一号当铺")
  {
	  set("ower","yhzzyahoo");
  }
  if(time() > query("next_change_owner_time"))
  {
    set("next_change_owner_time",time()+CHANGE_OWNER_VAL);

    //记录老店主的遗产
    if(query("owner") && query("owner") != query("no1_bidder"))
    {
      add("legacy_balance/"+query("owner"),query("balance"));
      delete("balance");
    }

    if(query("no1_bidder"))
    {
      CHANNEL_D->do_channel(this_object(), "jy", query("no1_bidder")+"今日成为本店掌柜！");
      CHANNEL_D->do_channel(this_object(), "jy", "竞标失败者请来本店取回质押的竞标金。");
      set("owner",query("no1_bidder"));
      
      //improve the owner's business skill
      add("skill_improved/"+query("owner"),(query("level")+1)*100);
      delete("no1_bidder");
      delete("bid_money");
    }
    else
    {
      //流拍！
      delete("owner");
      delete("good_list");
      delete("goods");
      findbox()->delete_temp("goods");
      findbox()->delete_temp("numbers");
      CHANNEL_D->do_channel(this_object(), "jy", "本店无人经营，今日宣布停业！");
    }
  }
  else
	{
		if ((query("next_change_owner_time")-time() < 80) && (!query("no1_bidder")))
		{
		 CHANNEL_D->do_channel(this_object(), "jy", "本店即将无人经营，请有志于经营自己产业的人速来竞标！");
		}
	}

  if(random(20) == 0) save_shop();

  remove_call_out("check_bidding");
  call_out("check_bidding",80);
  return 1;
}

int publish_ad()
{
  string advert = query("advertisement");
  if(!stringp(advert) || advert == "" || !query("owner") || query("owner") == "")
  {
    return 1;
  }
  CHANNEL_D->do_channel(this_object(), "jy", HIY + query("short") + HIG + "("+query("owner") + ")" + NOR + advert + NOR);
  return 1;
}

//allow some special thing such as wanzi to be selt in player shop
int check_can_sell_or_not(object ob)
{
  //we can sell everything that the system shop can sell, and more.
  if(ob->query("sell_in_playershop")) return 1;
  if(ob->query("no_sell")) return 0;
  if(ob->query("unique")) return 0;
  if( ob->query("material") == "ice" ) return 0;
  if(ob->query("no_drop")) return 0;
  if(ob->query("money_id")) return 0;
  if( (int)ob->query("skill_type") && (int)ob->query("rigidity")<50) return 0;

  return 1;
}

int do_setdesc(string arg)
{
  string desc;
  if (time()-query("paizi_change")<24*3600)
  {
    write("你刚刚写过牌子，老换可不好。\n");
    return 1;
  }
  if (stringp(desc=query("paizi_desc"))&&strwidth(desc)>0&&!this_player()->query_temp("my_hockshop_desc"))
  {
    this_player()->set_temp("my_hockshop_desc",1);
    write("你的店铺已经存在描述，再次输入将覆盖这个描述。");
    return 1;
  }
  if (strwidth(arg)>40)
  {
    write("你的描述太长了，必须在20个汉字或者40个字符以内。\n");
    return 1;
  }
  set("paizi_change",time());
  set("paizi_desc",arg);
  save();
  this_player()->delete_temp("my_hockshop_desc");
  write(HIR+"你在招牌上写上了"+arg+"的字样。\n"+NOR);
  return 1;
}

int forceemptyshop()	//清空商店
{
	findbox()->delete_temp("numbers");
    findbox()->delete_temp("goods");
	delete("discounts");
	delete("no1_bidder");
    delete("bidders");
    delete("bid_money");
    delete("skill_improved");
    delete("no1bidder");
    delete("legacy_balance");
    delete("invests");
    delete("balance");
    delete("good_list");
    delete("goods");
    delete("owner");
    delete("discount_rates");
    set("level", 1);
    save();
	return 1;
}
