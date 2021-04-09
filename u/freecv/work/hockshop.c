#pragma save_binary
// hockshop.c
// modified by Pal 2003-5-28

inherit ROOM;
#define MAX_PAWN 20

string *sell_msg = ({
  "破破烂烂，一文不值",
  "质地低劣，难看之极",
  "又脏又破，臭气熏天",
});

object shop_box;

int query_max_items() {return 50;}
string get_name(string str);

void init()
{
    add_action("do_value", "value");
    add_action("do_pawn", "pawn");
    add_action("do_pawn","dang");
    add_action("do_retrieve","shu");

    add_action("do_sell", "sell");
    add_action("do_retrieve", "retrieve");
    add_action("do_retrieve", "redeem");

    add_action("do_buy", "buy");
    add_action("do_list", "list");
    add_action("do_quit", "quit");

    set("no_clean_up", 1);
}

// find the shopbox object for this shop to hold sold items.
object findbox()
{
    if(shop_box && environment(shop_box)==this_object()) 
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

int do_value(string arg)
{
    object ob;
    int value, sale;

    if( !arg || !(ob = present(arg, this_player())) )
	return notify_fail("你要拿什么物品给当铺估价？\n");

    if( ob->query("money_id") )
	return notify_fail("这是「钱」，你没见过吗？\n");

    value = ob->query("value");
    sale=ob->query_temp("sale_price");
    if(sale>0 && sale<value) value=sale;

    if( !value) printf("%s一文不值。\n", ob->query("name"));
    else 
	printf("%s价值%s。\n如果你要卖断(sell)，可以拿到%s。\n",
	  ob->query("name"), value_string(value),
	  value_string(value * 80 / 100), value_string(value * 80 / 100));

    return 1;
}

int do_pawn(string arg)
{
    object ob, stamp_ob,me;
    int value, sale_price,pawn_count;
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
//	printf("pawn_num=%d,totalnum=%d,i=%d\n",pawn_num,totalnum,i);
    if( !arg || !(ob = present(arg, me))) 
//			return notify_fail("指令格式：pawn|dang [<物品ID>]\n");
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
				printf("%-3s：  %-15s  共有%-5d件    赎银：%s\n", terms[i], pawn[terms[i]],npawn[terms[i]],	value_string(vpawn[terms[i]]* 4/5));
			}
			printf("\t你还可以典当%d样%d件物品。\n",pawn_num-i,2*pawn_num-totalnum);
		}
		return 1;
	}
//	printf("pawn_num=%d,totalnum=%d,i=%d\n",pawn_num,totalnum,i);
    if (ob->query("shaolin"))
	return notify_fail("少林的宝物小的可不敢要呀！\n");
    if (ob->query("mingjiao"))
	return notify_fail("魔教的财产小的可不敢要呀！\n");


    if( ob->query("money_id") )	return notify_fail("你要当「钱」？\n");

    if( ob->query("material") == "ice" )
	return notify_fail("掌柜的说：冰的东西我们这里没法存放。\n");
    //cuz ice melts, will cause problem, so disabled...weiqi, 970930.

    value = ob->query("value");
    sale_price=ob->query_temp("sale_price");
	if (sale_price>0)
		sale_price= sale_price>value?value:sale_price;
	else
		sale_price=value;

	if( !(sale_price*6/10) ) return notify_fail("这样东西并不值很多钱。\n");
    if( !value || value < 10) return notify_fail("这样东西不值钱。\n");
    if(ob->query("no_sell") || ob->query("no_pawn") || ob->query("no_store"))
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
				write("掌柜的唱道："+ sell_msg[random(sizeof(sell_msg))] +
				ob->query("name") + "一" + ob->query("unit") + "，押"+
					value_string(sale_price*60/100)+ "。\n");
				message_vision("$N把身上的" + ob->query("name") + "拿出来典当了"
					+ value_string(sale_price * 60 / 100) + "。\n", me);
			    me->start_busy(1);
			    pay_player(me, sale_price * 60 / 100);
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
//		printf("pawn_count=%d\n",pawn_count);
	}
	else
		pawn_count=0;
//	printf("pawn_count=%d\n",pawn_count);
		write("掌柜的唱道："+ sell_msg[random(sizeof(sell_msg))] +
		ob->query("name") + "一" + ob->query("unit") + "，押"+
			value_string(sale_price*60/100)+ "。\n");
		message_vision("$N把身上的" + ob->query("name") + "拿出来典当了"
			+ value_string(sale_price * 60 / 100) + "。\n", me);
	    me->start_busy(1);
		term = ob->query("name");
		data = base_name(ob)+ ".c";
		me->set("pawn/"+ sprintf("%d",pawn_count),  term);
		me->set("vpawn/"+sprintf("%d",pawn_count), ob->query("value"));
		me->set("fpawn/"+sprintf("%d",pawn_count), data);
		me->set("npawn/"+sprintf("%d",pawn_count), 1);	
		me->save();
	    pay_player(me, sale_price * 60 / 100);
/*    stamp_ob = new(__DIR__"obj/stamps");

    stamp_ob->set_temp("file", ob);
    stamp_ob->set_temp("value", value*70/100);
    stamp_ob->set_temp("player", this_player()->query("id"));
    stamp_ob->set_temp("long_1", this_player()->name()+"典当" +
      ob->query("name") + "一" + ob->query("unit") +
      "讫，破烂缺损不堪。");
    stamp_ob->set_temp("long_2", "赎回应付"+
      value_string(value*70/100)+"整，一手交钱，一手交货。");
    stamp_ob->set("long", this_player()->name()+"典当" +
      ob->query("name") + "一" + ob->query("unit") +
      "讫，破烂缺损不堪。\n" + "赎回应付"+
      value_string(value*70/100)+"整，一手交钱，一手交货。\n");
*/

//    stamp_ob->move(this_player());

	destruct(ob);
//    ob->move(findbox());

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

int do_every_sell(object ob)
{
    int value, sale;
    string obj_file;
	object oldob;
    int i, oldnum;
    string index;

    if (ob->query("shaolin"))
    {
	write("少林的宝物小的可不敢要呀！\n");
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
    value = ob->query("value");
    sale=ob->query_temp("sale_price");
    if(sale>0 && sale<value) value=sale;
    if( !value ) 
    {
    	write("这样东西不值钱。\n");
    	return 0;
    }
    if(ob->query("no_sell") || ob->query("no_pawn"))
    {
    	write("这样东西不能买卖。\n");
    	return 0;
    }

    if(ob->query("no_drop"))
    {
    	write("这样东西不能离开你。\n");
    	return 0;
    }

    if( ob->query("material") == "ice" )
    {
    	write("掌柜的说：冰的东西我们这里没法存放。\n");
    	return 0;
    }
    //cuz ice melts, will cause problem, so disabled...weiqi, 970930.

/*    write("掌柜的唱道："+ sell_msg[random(sizeof(sell_msg))] +
      ob->query("name") + "一" + ob->query("unit") + "，当"+
      value_string(value*80/100)+ "。\n");
    message_vision("$N把身上的" + ob->query("name") + "卖掉。\n",
      this_player());
*/
    index=ob->query("name")+"("+ob->query("id")+")";
    this_player()->set_temp("sell_unit/"+index,ob->query("unit"));
    this_player()->add_temp("sell_value/"+index,value*80/100);
    this_player()->add_temp("sell_count/"+index,1);

    if(!(oldob = findbox()->query_temp("goods/"+index)) ){
	findbox()->set_temp("goods/"+index, ob);
	findbox()->set_temp("numbers/"+index, 1);
	ob->move(findbox());
    }
    else {
	oldnum = findbox()->query_temp("numbers/"+index);
	findbox()->set_temp("numbers/"+index, oldnum+1);
	if (ob->query("value") > oldob->query("value"))
		oldob->set("value",ob->query("value"));
	destruct(ob);
    }

    return value*80/100;
}

int do_sell(string arg)
{
    object ob;
    int value, sale, pay_value;
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
	    	index = ob_list[i]->query("unit");
	    	oldnum++;
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
		if ( (value=do_every_sell(ob_list[i])) > 0)
		    	num_sold++;
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
    return 1;
}

/*int do_retrieve(string arg)
{
    object ob;
    int value, afford;
    object pawn_ob;


    if( this_player()->is_busy() )
	return notify_fail("你现在正忙着呢。\n");

    if( !arg || !(ob = present(arg, this_player())) )
	return notify_fail("你要赎回什么物品。\n");

    if( ob->query("id") != "pawn stamp")
	return notify_fail("你要用当票才能赎回物品。\n");

    value = ob->query_temp("value");
    if(!value) 
	return notify_fail("用空白当票来赎物，光天化日之下想打劫不成！\n");

    if( !(afford = this_player()->can_afford(value)) )  {
	return notify_fail("你没有足够的钱来赎回。\n");
    }
    else if( afford == 2 )
	return notify_fail("你没有足够的零钱，而银票又没人找得开。\n");

    if( ob->query_temp("player") != this_player()->query("id"))
	return notify_fail("又不是你当的，想趁火打劫啊！\n");

    pawn_ob = ob->query_temp("file");
    if(!pawn_ob) {
	destruct(ob);
	return notify_fail
	("掌柜的惊道：糟糕！你要的东西找不着了。\n");
    }

    if(!pawn_ob->move(this_player())) return 0;
    destruct(ob);

    write("掌柜的唱道："+ sell_msg[random(sizeof(sell_msg))] +
      pawn_ob->query("name") + "一" + pawn_ob->query("unit") + "，赎银"+
      value_string(value)+ "。\n");
    message_vision("$N用当票赎回一"+pawn_ob->query("unit")+
      pawn_ob->query("name")+"。\n", this_player());

    this_player()->start_busy(1);
    this_player()->pay_money(value);
    this_player()->save();

    return 1;
}
*/
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
int do_retrieve(string arg)
{
        int num;
        int amount;
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
     // below is modified by freecv
     afford = affordable(me,amount);
     if (!afford)
            return notify_fail("你没有足够的钱来赎回。\n");
    if (afford == 2)
        return notify_fail("你没有足够的零钱，而银票又没人找得开。\n");
    else{
				me->start_busy(1);
                me->pay_money(amount);
                ob_file = me->query("fpawn/"+sprintf("%d",num));
                ob = new(ob_file);
                ob->move(me);
				me->add("npawn/"+sprintf("%d",num),-1);
				if (me->query("npawn/"+sprintf("%d",num))<1)
				{
					me->delete("npawn/"+sprintf("%d",num));
					me->delete("pawn/"+sprintf("%d",num));
					me->delete("vpawn/"+sprintf("%d",num));
					me->delete("fpawn/"+sprintf("%d",num));
				}					
				me->save();
                message_vision("$N赎回了$n。\n", me, ob);
                return 1;
        }

}

int do_list(string arg)
{
    mapping goods;
    string list, *name;
    int i;
    string tlist;
    object me=this_player();

    if( !mapp(goods = findbox()->query_temp("goods")) )
	return notify_fail("当铺目前没有任何货物可卖。\n");
    name = keys(goods);
    if(!sizeof(goods)) 
	return notify_fail("当铺目前没有任何货物可卖。\n");

    if( !arg )   {
	list = "你可以购买下列这些东西：\n";
	write(list);
	i=sizeof(goods);
	while(i--) {
	    if(!goods[name[i]]) {
		findbox()->delete_temp("numbers/"+name[i]);
		findbox()->delete_temp("goods/"+name[i]);
		continue;
	    }
	    //mon 2/4/98 because some items may destruct themselves
	    //after being sold.

	    tlist = get_name(name[i]);
	    list = sprintf("%-30s：%-20s：还剩%s%s\n", tlist,
	      value_string(goods[name[i]]->query("value")),
	      chinese_number(findbox()->query_temp("numbers/"+name[i])),
	      goods[name[i]]->query("unit") );
	    me->start_more(list);
	}
    }
    else if( arg == "book" )  {
	list = "";
	i=sizeof(goods);
	while(i--) {
	    if(!goods[name[i]]) {
		findbox()->delete_temp("numbers/"+name[i]);
		findbox()->delete_temp("goods/"+name[i]);
		continue;
	    }

	    if( mapp(goods[name[i]]->query("skill")) )   {
		tlist = get_name(name[i]);
		list += sprintf("%-30s：%-20s：还剩%s%s\n", tlist,
		  value_string(goods[name[i]]->query("value")),
		  chinese_number(findbox()->query_temp("numbers/"+name[i])),
		  goods[name[i]]->query("unit") );
	    }
	}
	if( list == "" )
	    write("当铺目前没有这种货品．\n");
	else {
	    list = "你可以购买下列这些东西：\n"+list;
	    me->start_more(list);
	}
    }
    else if( arg == "drug" )  {
	list = "";
	i=sizeof(goods);
	while(i--) {
	    if(!goods[name[i]]) {
		findbox()->delete_temp("numbers/"+name[i]);
		findbox()->delete_temp("goods/"+name[i]);
		continue;
	    }
	    if( goods[name[i]]->query("drug_type") )   {
		tlist = get_name(name[i]);
		list += sprintf("%-30s：%-20s：还剩%s%s\n", tlist,
		  value_string(goods[name[i]]->query("value")),
		  chinese_number(findbox()->query_temp("numbers/"+name[i])),
		  goods[name[i]]->query("unit") );
	    }
	}
	if( list == "" )
	    write("当铺目前没有这种货品．\n");
	else {
	    list = "你可以购买下列这些东西：\n"+list;
	    me->start_more(list);
	}
    }
    else if( arg == "axe" || arg == "blade" || arg == "dagger" || 
      arg == "fork" || arg == "hammer" || arg == "spear" || arg == "mace" || arg == "rake" ||
      arg == "staff" || arg == "stick" || arg == "sword" || arg == "whip" ||
      arg == "throwing" )  {
	list = "";
	i=sizeof(goods);
	while(i--) {
	    if(!goods[name[i]]) {
		findbox()->delete_temp("numbers/"+name[i]);
		findbox()->delete_temp("goods/"+name[i]);
		continue;
	    }

	    if( goods[name[i]]->query("skill_type") == arg )   {
		tlist = get_name(name[i]);
		list += sprintf("%-30s：%-20s：还剩%s%s\n", tlist,
		  value_string(goods[name[i]]->query("value")),
		  chinese_number(findbox()->query_temp("numbers/"+name[i])),
		  goods[name[i]]->query("unit") );
	    }
	}
	if( list == "" )
	    write("当铺目前没有这种货品．\n");
	else {
	    list = "你可以购买下列这些东西：\n"+list;
	    me->start_more(list);
	}
    }
    else if( arg == "archery" )  {
	list = "";
	i=sizeof(goods);
	while(i--) {
	    if(!goods[name[i]]) {
		findbox()->delete_temp("numbers/"+name[i]);
		findbox()->delete_temp("goods/"+name[i]);
		continue;
	    }
	    if( goods[name[i]]->query("apply/skill_type") == arg )   {
		tlist = get_name(name[i]);
		list += sprintf("%-30s：%-20s：还剩%s%s\n", tlist,
		  value_string(goods[name[i]]->query("value")),
		  chinese_number(findbox()->query_temp("numbers/"+name[i])),
		  goods[name[i]]->query("unit") );
	    }
	}
	if( list == "" )
	    write("当铺目前没有这种货品．\n");
	else {
	    list = "你可以购买下列这些东西：\n"+list;
	    me->start_more(list);
	}
    }
    else if( arg == "armor" || arg == "boots" || arg == "cloth" ||
      arg == "finger" || arg == "hands" || arg == "head" || arg == "neck" ||
      arg == "shield" || arg == "surcoat" || arg == "waist" ||
      arg == "wrists" )   {
	list = "";
	i=sizeof(goods);
	while(i--) {
	    if(!goods[name[i]]) {
		findbox()->delete_temp("numbers/"+name[i]);
		findbox()->delete_temp("goods/"+name[i]);
		continue;
	    }
	    if( goods[name[i]]->query("armor_type") == arg )   {
		tlist = get_name(name[i]);
		list += sprintf("%-30s：%-20s：还剩%s%s\n", tlist,
		  value_string(goods[name[i]]->query("value")),
		  chinese_number(findbox()->query_temp("numbers/"+name[i])),
		  goods[name[i]]->query("unit") );
	    }
	}
	if( list == "" )
	    write("当铺目前没有这种货品．\n");
	else {
	    list = "你可以购买下列这些东西：\n"+list;
	    me->start_more(list);
	}
    }
    else   {
	list = "";
	i=sizeof(goods);
	while(i--) {
	    if(!goods[name[i]]) {
		findbox()->delete_temp("numbers/"+name[i]);
		findbox()->delete_temp("goods/"+name[i]);
		continue;
	    }
	    if( member_array(arg, goods[name[i]]->parse_command_id_list()) != -1 )   {
		tlist = get_name(name[i]);
		list += sprintf("%-30s：%-20s：还剩%s%s\n", tlist,
		  value_string(goods[name[i]]->query("value")),
		  chinese_number(findbox()->query_temp("numbers/"+name[i])),
		  goods[name[i]]->query("unit") );
	    }
	}
	if( list == "" )
	    write("当铺目前没有这种货品．\n");
	else {
	    list = "你可以购买下列这些东西：\n"+list;
	    me->start_more(list);
	}
    }

    return 1;
}


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
	    value = obj_file->query("value"); 
	    if( !(afford=this_player()->can_afford(value)) )  {
		write("你没有足够的钱。\n");
		return 1; 
	    }
	    else if( afford == 2 )  {
		write("你没有足够的零钱，而银票又没人找得开。\n");
		return 1;
	    }

	    ob = new( base_name( obj_file ) ); 
	    ob->set_name(obj_file->query("name"),
	      obj_file->parse_command_id_list());
		ob->set("value",value);

	    this_player()->pay_money(value);

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
          this_player()->move("/adm/room/quitroom");
    return 1;
}

// no clean up at hockshop to prevent items lose.
int clean_up()  
{
    return 0;
}

