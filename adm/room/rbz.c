//修正两个bug   boost 2008-08-28
// 1 不能list，原因在于box内物品出现断层，原因未知，现在修改list解决问题
// 2 sell的时候因不能超过500件物品而回头覆盖原有物品时，原物品并未dest，可能会造成物品过多
// 现在改为sell到上限(MAX_SELL)的时候，砍掉最老的一半，剩下的一半顶替老的一半
// modified by Vast @ 2009.3.22  修改了List的显示方式，给list增加了参数，可以分类显示


#include <ansi.h>

inherit ROOM;
//这个值以后看情况调整
//根据最新的当铺修改，以防当东西的bug
//advent 2006-8-5



#define MAX_PAWN 50
#define MAX_SELL 200        

string *sell_msg = ({
	"破破烂烂，一文不值",
	"质地低劣，难看之极",
	"又脏又破，臭气熏天",
});

nosave object shop_box = 0;
nosave int sell_index = 0;      //指向被卖物品所应该给定的编号


int query_max_items() {return 50;}

void create()
{
	set("short", HIY"荣宝斋"NOR);

	set("long", CYN @LONG
这里是京城里最有名的珠宝店在扬州的分店。店主人见多识广，收藏的宝物
也颇不少，除了当世的名家珍品，还时常有些宝石兵器之类的。墙上挂着一块牌
子(sign)，牌子旁边贴着一张【最新公告】（paizi）。
LONG NOR);

	set("exits", ([
		"north" : "/d/city/dangpu",
	]));
	set("objects", ([
		"/d/beijing/npc/liulaoban":1,
	]));

	set("item_desc", ([
		"sign" : "公平交易，童叟无欺\n

			注意：本店只经营珠宝，并提供珠宝保管服务，按珠宝价值收取20%手续费。\n
			sell        卖
			buy         买
			pawn        当
			redeem      赎
			value       估价
			list        列表\n",
			
		"paizi":"         list 命令可以加以下参数，来显示具体的某类物品，并能看到较为详细的属性\n
			weapons  :   显示所有武器类物品列表，并可以看到武器的伤害数值
			armors   ：  显示所有防具类物品列表，并可以看到防具的防御数值
			gem      ：  显示所有宝石列表
      			sword/blade/staff/whip/axe/spear/hammer/halberd/throwing/dagger
               			:    显示具体某类武器类物品列表
			armor/boots/cloth/hands/head/shield/surcoat/waist/wrists/finger/neck
			         ：  显示具体某类防具类物品列表\n",
	]));
	set("no_beg",1);
	set("no_steal", 1);
//	set("no_fight", 1);
//	set("no_perform", 1);
	setup();
}

void init()
{
	add_action("do_value", "guji");
	add_action("do_value", "value");
	add_action("do_pawn", "pawn");
	add_action("do_pawn", "dang");
	add_action("do_retrieve", "redeem");
	add_action("do_sell", "sell");
	add_action("do_retrieve", "shu");
	add_action("do_buy", "buy");
	add_action("do_list", "list");
	add_action("do_quit", "quit");
}

// find the shopbox object for this shop to hold sold items.
object findbox()
{
	if(shop_box && environment(shop_box) == this_object())
		return shop_box;
	shop_box=new("/feature/shopbox");
	shop_box->move(this_object());
	sell_index = 0;
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

	if( !ob->is_gems())
		return notify_fail("本店不买卖普通物品！\n");

	value = ob->query("value");
	sale = ob->query_temp("sale_price");
	if(sale>0 && sale<value) value=sale;

	if( !value) printf("%s一文不值。\n", ob->query("name"));
	else
		printf("%s价值%s。\n如果你要卖断(sell)，可以拿到%s。\n如果你要典当(pawn)，得付手续费%s。\n",
		ob->query("name"), value_string(value),
		value_string(value * 60 / 100), value_string(value * 20 / 100));

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

int do_pawn(string arg)
{
	object ob, me, stuff;
	int value, sale_price, pawn_count, time;
	string obj_file, file_name, data, list, tmp;
	int i, pawn_num, clone_number, totalnum, index, effect, hole;
	mapping pawn, vpawn;
	string term, *terms;
	totalnum=0;

	me = this_player();
	if(!me->query("ludingshan"))
		return notify_fail("你还没解开鹿鼎山的秘密，暂时无法在这里典当物品。\n");

	pawn = me->query("pawns");//物品名字
	vpawn = me->query("vpawns");//物品价值

	if( me->is_busy() )
		return notify_fail("你现在正忙着呢。\n");

	//玩家可以典当的物品的数量
	pawn_num=to_int(me->query("combat_exp")/1000000 + me->query("mud_age")/(3600*24))+1;
	if (pawn_num < 0)
		pawn_num=0;

	if (pawn_num > MAX_PAWN)
		pawn_num = MAX_PAWN;//不能超过最大限制

	if ( mapp(pawn) && sizeof(pawn) )
	{
		terms = keys(pawn);
		totalnum = sizeof(terms);//总数
	}
	if( !arg || !(ob = present(arg, me)))
	{

		if( !mapp(pawn) || !sizeof(pawn) )
		{
			write("你并没有典当任何物品。\n");
			printf("\t你一共可以典当%d件物品。\n",pawn_num);
		}
		else
		{
			list = "";
			list += "┌──┬────────────────┬────┬──┬──────────────────┐\n";
			list += "│编号│              名称              │  " + "数值" + "  │可塑性│                 费用               │\n";
						
			    for(i = 0; i < MAX_PAWN; i++)
        	{

        		obj_file = me->query("fpawns/" + i);
        		if(!stringp(obj_file)) continue;
        			
        		stuff = new(obj_file);
        		stuff->set("owner_id", me->query("id"));
        		stuff->set("savetime", me->query("tpawns/" + i));
        
        		if(stuff->restore())
        			{
        				hole = stuff->query("forge/max");
        				if(stuff->query("weapon_prop"))
        					effect = stuff->query("weapon_prop/damage");
        				else if(stuff->query("armor_prop"))
        					effect = stuff->query("armor_prop/armor");
        				destruct(stuff);
        			
						list += "├──┼────────────────┼────┼──┼──────────────────┤\n";
						tmp = COLOR_D->uncolor(pawn[sprintf("%d", i)]);
						list += sprintf("│%4d│%-32s│%|8d│%|4d│%-36s│\n", i, tmp, effect, hole, value_string(vpawn[sprintf("%d", i)]* 1/5) );
						list = replace_string(list, tmp, pawn[sprintf("%d", i)]);
					}
        			
        	}
        	list +="└──┴────────────────┴────┴──┴──────────────────┘\n";
					list = "┏"HBGRN + sprintf("目前典当物品列表(还可以典当%2d件物品)", pawn_num - sizeof(pawn))  + NOR"┓\n"+ list;

					me->start_more(list);        
						
/* 
			write("你目前典当的物品有：\n");
			terms = keys(pawn);
			for (i=0 ;i<sizeof(terms) ;i++ )
			{
				printf("%-3s：  %-20s     手续费：%s\n", terms[i], pawn[terms[i]], value_string(vpawn[terms[i]]* 1/5));
			}
			printf("\t你还可以典当%d件物品。\n", pawn_num-i);
		*/
		}
		return 1;
	}

	if (!ob->is_gems())
		return notify_fail("这种普普通通的东西，我可不要！\n");
        if (ob->is_gem())
                return notify_fail("宝石你放到无欢给你的宝石箱去吧！\n");


	if( ob->query("money_id") ) return notify_fail("你要当「钱」？\n");

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

	if(ob->query("no_drop"))
		return notify_fail("这样东西不能离开你。\n");

	if (totalnum >= pawn_num)
		return notify_fail("你典当物品数量太多，小店没有地方存了。\n");
	if( mapp(pawn) && sizeof(pawn))
	{
		terms = keys(pawn);

		for(i=0; i<sizeof(terms); i++)
		{
			pawn_count = i;
			if(!((int) me->query("vpawns/" + sprintf("%d", i))))
				break;
			else pawn_count = i+1;
		}
		if (sizeof(terms) >= pawn_num)
			return notify_fail("你已典当太多物品了。\n");
	}
	else
		pawn_count=0;


	me->start_busy(2);
	
	time = time();
	if(ob->query("equipped"))
		ob->unequip();
	ob->set("owner_id", me->query("id"));
	ob->set("savetime", time);
	ob->save();
	//              write("掌柜的唱道："+ sell_msg[random(sizeof(sell_msg))] +
	//              ob->query("name") + "一" + ob->query("unit") + "，押"+
	//                      value_string(sale_price*60/100)+ "。\n");
	write("掌柜的说道:您暂时将"+ob->query("name") +"寄存在我这里，等赎出来的时候我们加收20％寄存费用。\n");
	//              message_vision("$N把身上的" + ob->query("name") + "拿出来典当了"
	//                      + value_string(sale_price * 60 / 100) + "。\n", me);
//	me->start_busy(1);
	term = ob->query("name");
	data = base_name(ob)+ ".c";
	me->set("pawns/"  + sprintf("%d",pawn_count),  term);
	me->set("vpawns/" + sprintf("%d",pawn_count), ob->query("value"));
	me->set("tpawns/" + sprintf("%d",pawn_count), time);
	me->set("fpawns/" + sprintf("%d",pawn_count), data);
	me->set("ipawns/" + sprintf("%d",pawn_count), ob->parse_command_id_list());
	me->save();
	//          pay_player(me, sale_price * 60 / 100);

	destruct(ob);

	return 1;
}

int do_retrieve(string arg)
{
	int num;
	int amount;
	string ob_file, save_file, *id;
	object ob;
	object me;
	int afford;
	if( !arg || sscanf(arg, "%d", num)!=1 )
		return notify_fail("指令格式：redeem <物品标号>\n");
	me = this_player();
	amount = (int) me->query("vpawns/" + sprintf("%d", num));
	if( !amount )
		return notify_fail("有这个物品标号吗？\n");
	amount = amount * 1 /5;
	if( !(afford = this_player()->can_afford(amount)) )  {
		return notify_fail("你没有足够的钱来赎回。\n");
	}
	else if( afford == 2 )
		return notify_fail("你没有足够的零钱，而银票又没人找得开。\n");
	if( afford = affordable(me, amount) ) {
		me->start_busy(1);
		me->pay_money(amount);
		ob_file = me->query("fpawns/"+sprintf("%d",num));
		ob = new(ob_file);
		ob->set("owner_id", me->query("id"));
		ob->set("savetime", me->query("tpawns/"+sprintf("%d",num)));
		save_file = ob->query_save_file();
		if(ob->restore())
        {
			rm(save_file + ".o");
            id = me->query("ipawns/" + sprintf("%d",num));
            ob->set_name(ob->query("name"), id);
            ob->set_weight(ob->query("base_weight") + ob->query("item/weight"));
            ob->move(me);

            me->delete("tpawns/" + sprintf("%d",num));
            me->delete("pawns/" + sprintf("%d",num));
            me->delete("vpawns/" + sprintf("%d",num));
            me->delete("fpawns/" + sprintf("%d",num));
            me->delete("ipawns/" + sprintf("%d",num));

            me->save();
            message_vision("$N赎回了$n。\n", me, ob);
        }
        else
        {
            write("你在敝处没有这样东西。\n");
        }
		return 1;
	} else
		return notify_fail("你的钱不够。\n");

}

int sell_and_move_to_box(object ob)
{
	object old_object, box = findbox();
	int i, half = MAX_SELL / 2;
	if (sell_index >= MAX_SELL)     //砍掉最老的 MAX_SELL/2个物品
	{
		for (i = 1; i <= half; i++)
		{
			old_object = box->query("goods/" + i);
			if (old_object)
			{
				destruct(old_object);
				box->delete("goods/" + i);
			}
		}
		for (; i <= MAX_SELL; i++)
		{
			old_object = box->query("goods/" + i);
			if (old_object)
			{
				box->set("goods/" + (i - half), old_object);
				box->delete("goods/" + i);
			}
		}
		sell_index = half;
	}

	box->set("goods/" + (sell_index + 1), ob);
	ob->move(box);
	sell_index++;
	return 0;
}

int do_sell(string arg)
{
	object ob, *obj, box, oldobject;
	int value, sale, allvalue = 0, sum;
	string obj_file, goods = "";
	int i, j, oldnum;
	string index;

	if( this_player()->is_busy() )
		return notify_fail("你现在正忙着呢。\n");


	box = findbox();


	if(arg == "all") //全卖，嘿嘿
	{
		j = 0;
		obj = all_inventory(this_player());
		for(i = sizeof(obj); i > 0; i--)
		{
                        if(obj[i - 1]->is_gems() && !obj[i - 1]->is_gem() && !obj[i-1]->query("gem_ob_autoloaded") && !obj[i-1]->query("no_drop"))
			{
				j++;
				value = obj[i - 1]->query("value");
				sale = obj[i - 1]->query_temp("sale_price");
				if(sale > 0 && sale < value) value = sale;
				allvalue += value;
				goods += obj[i - 1]->query("name") + "、\n";
				sell_and_move_to_box(obj[i-1]);
			}
		}
		if(j)
		{
			allvalue = allvalue /100 * 60;
            if(allvalue <= 0) 
            {
                write("你身上的东西 一文不值。\n");
                return 1;
            }
			this_player()->start_busy(1);
			message_vision("$N把身上的" + goods + "一共" + chinese_number(j) + "件物品卖掉，当"
				+ value_string(allvalue) + "。\n", this_player());
			pay_player(this_player(), allvalue );
		}
		else
			tell_object(this_player(), "你身上没有什么特殊的物品可以出售。\n");
		return 1;
	}

	if( !arg || !(ob = present(arg, this_player())) )
		return notify_fail("指令格式：sell <物品名|all>\n");

	if( !ob->is_gems())
		return notify_fail("本店不买卖普通物品！\n");

	value = ob->query("value");
	sale = ob->query_temp("sale_price");
	if(sale>0 && sale<value) value=sale;
	if( !value ) return notify_fail("这样东西不值钱。\n");

	if(ob->query("no_drop"))
		return notify_fail("这样东西不能离开你。\n");


	write("掌柜的唱道："+ sell_msg[random(sizeof(sell_msg))] +
		ob->query("name") + "一" + ob->query("unit") + "，当"+
		value_string(value*60/100)+ "。\n");
	message_vision("$N把身上的" + ob->query("name") + "卖掉。\n",
		this_player());

	sell_and_move_to_box(ob);

	this_player()->start_busy(1);
	pay_player(this_player(), value * 60 / 100);
	return 1;
}


int do_list(string arg)
{
	object goods;
	string list, name, tmp, type;
	int i, j, value, hole;
	object me=this_player();
	string *weapon = ({"sword", "blade", "staff", "whip", "axe", "spear", "hammer", "halberd", "throwing", "dagger"});
	string *armor = ({"armor", "boots", "cloth", "hands", "head", "shield", "surcoat", "waist", "wrists", "finger", "neck"});
	

	//        return notify_fail("抱歉，本店主人曾言明所有收购的货色都要亲自过目，不能给客官看。\n");
	if( (i = sizeof( goods = findbox()->query("goods") )) == 0 )
		return notify_fail("当铺目前没有任何货物可卖。\n");

	list = "你可以购买下列这些东西：(请使用命令 buy <物品编号> 来购买)\n\n";
	
//	write(list);

	i = 1;
	
	if (arg == "new")
	{
		i = sell_index - 20;
		if (i < 1)
			i = 1;
	}
	
	if (stringp(arg) && (member_array(arg, weapon) != -1 || member_array(arg, armor) != -1))
		{
			if(member_array(arg, weapon) != -1)
				type = "伤害";
			else type = "防御";
				
			list += "┏" + HBGRN"所有" + arg + "列表"NOR + "┓\n";
			list += "┌──┬────────────────┬────┬──——┬──────────────────┐\n";
			list += "│编号│              名称              │  " + type + "  │ 可塑性 │                 价格               │\n";
			         
			    for(j = i; j <= MAX_SELL; j++)
        	{
        		goods = findbox()->query("goods/" + j);
        		if(!goods)
        			continue;    
        		if(goods->query("skill_type") == arg || goods->query("armor_type") == arg)
        			{
        				if(goods->query("skill_type") == arg) value = goods->query("weapon_prop/damage");
        				if(goods->query("armor_type") == arg) value = goods->query("armor_prop/armor");
        		
        		hole = goods->query("forge/max");			
        		name = goods->query("name") + "(" + goods->query("id") + ")";
        		list += "├──┼────────────────┼────┼─——─┼──────────────────┤\n";
        		tmp = COLOR_D->uncolor(name);
        		list += sprintf("│%4d│%-32s│%|8d│%|8d│%-36s│\n", j, tmp, value, hole, value_string(goods->query("value")) );
        		list = replace_string(list, tmp, name);
        			}
        	}
        	list +="└──┴────────────────┴────┴─——─┴──────────────────┘\n";

		}
		else if(stringp(arg) && arg == "weapons")
			{
			list += "┏" + HBGRN"所有武器列表"NOR + "┓\n";
			list += "┌──┬────────────────┬────┬──——┬──────────────────┐\n";
			list += "│编号│              名称              │  " + "伤害" + "  │ 可塑性 │                 价格               │\n";
						
			    for(j = i; j <= MAX_SELL; j++)
        	{
        		goods = findbox()->query("goods/" + j);
        		if(!goods)
        			continue;    
        		if(goods->query("weapon_prop"))
        			{
        				hole = goods->query("forge/max");		
        		name = goods->query("name") + "(" + goods->query("id") + ")";
        		list += "├──┼────────────────┼────┼─——─┼──────────────────┤\n";
        		tmp = COLOR_D->uncolor(name);
        		list += sprintf("│%4d│%-32s│%|8d│%|8d│%-36s│\n", j, tmp, goods->query("weapon_prop/damage"), hole, value_string(goods->query("value")) );
        		list = replace_string(list, tmp, name);
        			}
        	}
        	list +="└──┴────────────────┴────┴──——┴──────────────────┘\n";

			}
		else if(stringp(arg) && arg == "armors")
			{
			list += "┏" + HBGRN"所有防具列表"NOR + "┓\n";
			list += "┌──┬────────────────┬────┬──——┬──────────────────┐\n";
			list += "│编号│              名称              │  " + "防御" + "  │ 可塑性 │                 价格               │\n";
						
			    for(j = i; j <= MAX_SELL; j++)
        	{
        		goods = findbox()->query("goods/" + j);
        		if(!goods)
        			continue;    
        		if(goods->query("armor_prop"))
        			{
        				hole = goods->query("forge/max");	
        		name = goods->query("name") + "(" + goods->query("id") + ")";
        		list += "├──┼────────────────┼────┼─——─┼──────────────────┤\n";
        		tmp = COLOR_D->uncolor(name);
        		list += sprintf("│%4d│%-32s│%|8d│%|8d│%-36s│\n", j, tmp,goods->query("armor_prop/armor"),hole,value_string(goods->query("value")) );
        		list = replace_string(list, tmp, name);
        			}
        	}
        	list +="└──┴────────────────┴────┴─——─┴──────────────────┘\n";

			}
		else if(stringp(arg) && arg == "gem")
			{
			list += "┏" + HBGRN"所有宝石列表"NOR + "┓\n";
			list += "┌──┬────────────────┬─────────────────┐\n";
			list += "│编号│              名称              │             价格                 │\n";	
						
			    for(j = i; j <= MAX_SELL; j++)
        	{
        		goods = findbox()->query("goods/" + j);
        		if(!goods)
        			continue;    
        		if(goods->is_gem())
        			{
        		name = goods->query("name") + "(" + goods->query("id") + ")";
        		list += "├──┼────────────────┼─────────────────┤\n";
        		tmp = COLOR_D->uncolor(name);
        		list += sprintf("│%4d│%-32s│%-34s│\n", j, tmp,value_string(goods->query("value")) );
        		list = replace_string(list, tmp, name);
        			}
        	}
        	list +="└──┴────────────────┴─────────────────┘\n";

			}
		else //list all
			{
			list += "┏" + HBGRN"所有商品列表"NOR + "┓\n";
			list += "┌──┬────────────────┬─────────────────┐\n";
			list += "│编号│              名称              │             价格                 │\n";	
						
			    for(j = i; j <= MAX_SELL; j++)
        	{
        		goods = findbox()->query("goods/" + j);
        		if(!goods)
        			continue;    
        		name = goods->query("name") + "(" + goods->query("id") + ")";
        		list += "├──┼────────────────┼─────────────────┤\n";
        		tmp = COLOR_D->uncolor(name);
        		list += sprintf("│%4d│%-32s│%-34s│\n", j, tmp,value_string(goods->query("value")) );
        		list = replace_string(list, tmp, name);
        	}
        	list +="└──┴────────────────┴─────────────────┘\n";
			}			
        	me->start_more(list);
	return 1;
}

int do_buy(string arg)
{
	object *goods;
	object ob;
	int value, afford;
	int i, j, num;
	string arg1, arg2;

	//        return notify_fail("抱歉，本店主人曾言明所有收购的货色都要亲自过目，不能卖给客官。\n");
	if( this_player()->is_busy() )
		return notify_fail("你现在正忙着呢。\n");

	if( !arg )  {
		write("指令格式：buy <物品编号>\n");
		return 1;
	}

	// players are used to the "buy sth from sb" format.
	if( sscanf(arg, "%s from %s", arg1, arg2) == 2 )   {
		arg = arg1;
	}

	if( (i = sizeof( goods = all_inventory(findbox()) )) == 0  )
		return notify_fail("当铺目前没有任何货物可卖。\n");

	num = atoi(arg);

	if(num && objectp(ob = findbox()->query("goods/" + num)))
	{
		value = ob->query("value");
		if( !(afford=this_player()->can_afford(value)) )  {
			write("你没有足够的钱。\n");
			return 1;
		}
		else if( afford == 2 )  {
			write("你没有足够的零钱，而银票又没人找得开。\n");
			return 1;
		}

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
		else
		{
			//                      //偷懒了:P，这里只是简单的交换了一下物品的顺序，如果有必要可以重新排序
			//                      findbox()->set("goods/" + num, findbox()->query("goods/" + i));
			//                      findbox()->delete("goods/" + i);

			//不再交换，就留下空位
			findbox()->delete("goods/" + num);
		}

		return 1;
	}
	else
		write("指令格式：buy <物品编号>。\n");

	return 1;
}

int do_quit()
{
//          this_player()->move("/adm/room/quitroom");
        if(this_player()->is_busy())
        {
            write("你正忙着呢。\n");
            return 1;
        }
        this_player()->move("/d/city/guangchang");;
		call_other(find_object("/cmds/usr/quit"),"main",this_player(),"");
//	       write("请不要在当铺quit，谢谢。\n");
	return 1;
}

// no clean up at hockshop to prevent items lose.
int clean_up()
{
	return 0;
}


string do_buy1(string arg)
{
	return "本店只收购宝石，并不提供售出服务！\n";
}

