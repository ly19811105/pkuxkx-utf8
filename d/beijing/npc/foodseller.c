//Cracked by Roath
// seller.c

inherit NPC;
inherit F_VENDOR;
#include "/d/beijing/killme.h"
void create()
{
        set_name("小贩", ({ "seller" }) );
        set("gender", "男性" );
        set("age", 32);
        set("long",
                "这是个小贩，别看他长的老老实实，可你别想从他那儿掏便宜。\n");
        set("combat_exp", 300);
        set("str", 17);
        set("dex", 20);
        set("con", 17);
        set("int", 22);
        set("attitude", "friendly");
        set("vendor_goods", ({
                __DIR__"obj/guozi",
                __DIR__"obj/liangmian",
        }) );
	set("chat_chance", 10);
	set("chat_msg", ({
	"小贩高声叫道：煎饼果子，又新鲜又便宜啊。\n",
	"小贩高声叫道：吃凉面吗，刚做好的嘞。\n",
	}));
        set("shen_type",1);set("score",200);setup();
        carry_object("/d/city/obj/cloth")->wear();
        add_money("coin", 60);
}

void init()
{
        ::init();
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}
