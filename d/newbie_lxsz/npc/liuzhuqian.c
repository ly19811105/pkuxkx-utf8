//D:\xkx\d\liuxiu-shanzhuang\npc\liuzhuqian.c柳住钱
// labaz 2012/10/22

#include <ansi.h>

inherit BANKER;

inherit NPC;


#include "../newbie_village.h"

void create()
{
	set_name("柳住钱", ({"liu zhuqian", "liu"}));
	set("title", "钱庄老板");
	set("long","他就是柳秀票号的老板,留住钱，哦不,叫柳住钱......\n");
	set("gender", "男性");
	set("age", 55);
	set("str", 28);
	set("int", 24);
	set("dex", 28);
	set("con", 28);
	set("max_jing", 100000);
	set("jing", 100000);
	set("shen", 1000);
	set("combat_exp", 30000);
	set("shen_type", 1);
	set("attitude", "friendly");
	set("env/wimpy", 50);
	add_money("coin", 88);
	add_money("silver", 88);
    carry_object(__DIR__"obj/gebu-changpao")->wear();
	set("startroom","/d/newbie_lxsz/liuxiu-piaohao.c");
	setup();
}

void init()
{
	::init();
	add_action("do_withdraw", "withdraw");
	add_action("do_withdraw", "qu");
}



int do_withdraw(string arg)
{
	int amount, v;
	string what;
	object me;

	if (query_temp("busy"))
		return notify_fail("哟，抱歉啊，我这儿正忙着呢……您请稍候。\n");

	me = this_player();
	
	if (!arg || sscanf(arg, "%d %s", amount, what) != 2)
	return notify_fail("命令格式：withdraw|qu <数量> <货币单位>\n");

	if (amount < 1)
	return notify_fail("你发疯啦，取负数？\n");

	if (amount > 1000)
	return notify_fail("你每次最多允许取一千两。\n");

	if (file_size("/clone/money/" + what + ".c") < 0)
	return notify_fail("你想取出什么钱？\n");

	what = "/clone/money/" + what;
	if ((v = amount * what->query("base_value")) > me->query("balance"))
	return notify_fail("你存的钱不够取。\n");

	//wight
//	printf("自己的负重=%d\n钱的重量=%d\n自己的最大负重=%d/t",me->query_encumbrance(),
//	amount *(what->weight()),me->query_max_encumbrance());
	if((me->query_encumbrance()+amount *(what->weight()))>me->query_max_encumbrance())
		return notify_fail("你带不了那么多钱，太重了。\n");


	me->add("balance",  -v);
//	MONEY_D->pay_player(me, v = v * 9 / 10);
// Disable bank charge.
	MONEY_D->pay_player(me, v);

	message_vision(sprintf("$N从银号里取出%s。\n", MONEY_D->money_str(v)),
		me);

	if (0==me->query("balance") && 1==check_questindex(me,"到票号把钱都给取出来"))
	call_out("set_nextquest",1,me,"到票号把钱都给取出来","取了钱，赶紧去药铺买药疗伤吧。", 20, 100);
	
	return 1;
}

void unconcious()
{
		  message_vision("\n突然，只见$N闪身拉开柜台下一道暗门，钻了进去，咔嚓从里
边把门锁上了。\n",
					 this_object());
        destruct(this_object());
}
