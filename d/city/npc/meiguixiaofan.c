// chen.c
// Jay 5/7/96

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("卖花小贩", ({ "xiao fan", "seller" }));
        set("shen_type", 1);

        set("str", 20);
        set("gender", "男性");
        set("age", 55);
        set("long",
                "这年头流行情人节，连原来卖鱼卖虾的小贩都改行来卖玫瑰花了。\n"
            );
        set("combat_exp", 8000);
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/d/city/obj/meiguihua.c",
                    }));

        setup();
}

void init()
{
        object ob;
        
        ::init();
        add_action("do_list", "list");
        add_action("do_buy", "buy");

}

void greeting(object ob)
{
        if( !this_object()->visible(ob)) return;
        if (!ob || environment(ob) != environment())
                return;
                say("情人节了，买朵玫瑰送给情人吧！很便宜的！只要十两黄金哦！\n");
}

