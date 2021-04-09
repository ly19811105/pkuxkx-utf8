//xiaofan.c 小贩 
//by zoom
//2003.4.30

#include <ansi.h>
#include <command.h>

inherit NPC;
inherit F_DEALER;

void do_sell();
void greeting(object);

void create()
{
        set_name("小贩", ({ "xiao fan", "fan" }));
        set("shen_type", 1);
        set("gender", "男性");
        set("age", 15);
        set("long","这个小家伙看中了这个新手云集的地方，
只可惜没有本钱，只能做些小本买卖。\n");
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_temp("apply/damage", 15);

        set("combat_exp", 10000);
        set("attitude", "friendly");
        set("vendor_goods", ({
            "/d/city/obj/guide",
            "/d/xiangyang/npc/obj/shuming.c",
        }));
	set("inquiry", ([
			"庄主"   :  "庄主在书房。\n",
		]));
        setup();
}

void init()
{
        object me = this_player();        

        ::init();

        add_action("do_list", "list");
        add_action("do_buy", "buy");
        add_action("do_sell", "sell");

        if( interactive(me) )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }
}

void greeting(object me)
{	if (me->query_temp(this_object()->query("id")) == 0 )
	{	command("hi " + me->query("id"));
		command("say 
         这位" + RANK_D->query_respect(me) + 
	          "来看看吧，小的这里有好东西卖呢。
    一般每个城市都有当铺，可以买卖东西， 也有一些杂货
    铺或者专门卖某种东西的。
    当铺里除了买卖还可以当东西，当然是要有一定支出的。
    用("+HBRED+HIW"list"NOR+")来查看卖的东西，用("+HBRED+HIW"buy"NOR +")来买，"+HBRED+HIW"sell"NOR+"就是卖啦。");
		me->set_temp(this_object()->query("id"), 1);

	}
}

void do_sell()
{
	command("say 小的这里只卖不买，请勿见怪。");
}