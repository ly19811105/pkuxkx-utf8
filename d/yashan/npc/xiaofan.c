// shangren.c
// pingpang
#include <ansi.h>
inherit NPC;
inherit F_DEALER;

void create()
{
	set_name(YEL"穷小贩"NOR, ({"xiao fan","fan"}));
	set("shen_type", 1);

	set("str", 20);
	set("gender", "男性");
	set("age", 85);
	set("long",
		"他是牙山附近的渔夫，由于最近朝廷战前封海，他已经没有地方打渔了，\n只有靠。在海边见一些贝壳做一些小商品谋生。\n");
	set("combat_exp", 1000);
	set("attitude", "friendly");
	
	set("vendor_goods", ({
		__DIR__"obj/beike.c",
		__DIR__"obj/ring.c",
	}));

	setup();
 	add_money("coin",1);
}

void init()
{
	object ob;
	
	::init();
	if (interactive(ob = this_player()) && !is_fighting()) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

void greeting(object ob)
{
	if (!ob || environment(ob) != environment())
		return;
	say("看看这些小玩意吧？送给心上人好着呢！\n");
	command("sigh");
	return;
}
