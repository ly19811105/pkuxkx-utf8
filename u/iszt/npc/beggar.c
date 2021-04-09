// File         : beggar.c
// Created By   : iszt@pkuxkx, 2006-09-19

#include <ansi.h>
#include <combat.h>

inherit NPC;

void create()
{
        set_name("小丐", ({ "xiao gai", "beggar", "gai" }) );
        set("gender", "男性" );
        set("age", 12);
        set("long", "一个十二三岁的小叫化子。他有气没力的坐在墙角边，看来已经饿得很了。\n");

        set("str", 17);
        set("int", 28);
        set("con", 25);
        set("dex", 12);

        set("max_qi", 500);
        set("max_jing", 100);
        set("jiali", 0);
        set("shen_type", 0);

        set("attitude", "friendly");
        set("combat_exp", 20000);
        set("kar", 100);

        set_skill("unarmed", 10);
        set_skill("parry", 10);

        set("inquiry", ([
                "name" : "我……我叫狗杂种！",
                "here" : "我也不知道这是什么地方，我是来找妈妈和阿黄的。",
                "狗杂种" : "对啦！我就是狗杂种！你知道我妈妈和阿黄去哪了吗？",
                "妈妈" : "妈妈从来不允我开口求恳，我若开口求恳，妈妈便要打我。",
                "阿黄" : "阿黄是我养的一条狗，它听得懂我的话呢。",
                "狗" : "我要找我的阿黄……",
                "求恳" : "你要给我钱便给，我可不会求你什么。",
                "开口求恳" : "你要给我钱便给，我可不会求你什么。",
                "乞讨" : "你要给我钱便给，我可不会求你什么。",
        ]));

        setup();
}

void init()
{
        object ob;

        ::init();
        ob = this_player();
        if(ob->query("class") == "officer")
        {
                message_vision("$N看到官府中人$n，一转身不知道溜到哪里去了。\n", this_object(), ob);
                destruct(this_object());
        }
        if( interactive(ob) ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if(!ob || !living(ob) || !present(ob, environment()))
                return;
        if(ob->query("marks/xieyanke"))
                message_vision("$N友善地冲着$n笑了笑。\n", this_object(), ob);
        else
                message_vision("$N略有点惊恐地看着$n，茫然不知所措。\n", this_object(), ob);
}

int accept_object(object me, object obj)
{
        if (obj->query("money_id") == "silver")
        {
                message_vision("$N嘻嘻笑道：「好心人，多谢你的银子，饼儿我已经有啦！」\n", this_object());
                remove_call_out("eat_bing");
                call_out("eat_bing", 2, me);
        }
        else
        { 
                 message_vision("$N把" + obj->query("name") + "握在手里把玩一番，奇道：这是什么？\n", this_object());
                 command("thank " + me->query("id"));
        }

        return 1;
}

void eat_bing(object ob)
{
        if(!ob || !living(ob) || !present(ob, environment()))
                return;
        message_vision(YEL"$N伸手在怀中掏啊掏，掏出一个烧饼，张口往烧饼上用力咬下。\n"NOR, this_object());
        remove_call_out("find_ling");
        call_out("find_ling", 2, ob);
}

void find_ling(object ob)
{
        if(!ob || !living(ob) || !present(ob, environment()))
                return;
        if(ob->query("marks/xieyanke"))
        {
                message_vision("$N狼吞虎咽的吃着，$n叹了口气，不再理他。\n", this_object(), ob);
                return;
        }
        message_vision(HIR"只听得卜的一声响，似是咬到了铁石。那$N一拉烧饼，口中已多了一物，忙吐在左手掌中，见是黑黝黝的一块铁片。\n"NOR, this_object());
        ob->set("marks/xieyanke", 1);
        remove_call_out("xueshan_dizi");
        call_out("xueshan_dizi", 2, ob);
}

void xueshan_dizi(object ob)
{
        int i;
        object dizi, ling;
        if(!ob || !living(ob) || !present(ob, environment()))
                return;

        message_vision(HIW"$N正打不定主意，忽听得头顶有人叫道：「四面围住了！」\n"
                        "那$N一惊，抬起头来，只见屋顶上站着三个身穿白袍的男子，跟着身后飕飕几声，有人纵近。\n"
                        "$N转过身来，但见四名白袍人手中各持长剑，分从左右掩将过来。\n"NOR
                        HIG"\n$n心念一动，从$N手中抢过铁片，未及细看，便立刻成为众矢之的！\n"NOR, this_object(), ob);
        for(i=0; i<7; i++)
        {
                dizi = new("/d/lingxiao/npc/dizi_xuantieling");
                dizi->move(environment(ob));
                dizi->fight_ob(ob);
        }
        ob->start_busy(1);
        ling = new(__DIR__"obj/tiepian");
        ling->set("owner", ob);
        ling->move(ob);

        remove_call_out("xieyanke");
        call_out("xieyanke", 7, ob, ling);
}

void xieyanke(object ob, object ling)
{
        object xie;
        string msg;
        if(!ob || !living(ob) || !present(ob, environment()))
                return;
        xie = new(__DIR__"xieyanke");

        msg = HIY"忽听得一个低沉的声音说道：「还是给我！」\n"
                "一个人影闪进圈中，一伸手，便将$N手中的铁片拿了过去。\n"NOR;
        message_vision(msg, ob);
        destruct(ling);
        xie->move(environment(ob));

        COMBAT_D->do_attack(xie, ob, xie->query_temp("weapon"), TYPE_QUICK);
        msg = HIR"众人大惊之下，全部停手。\n"NOR;
        if(random( ob->query_dex() ) <= 10 || random(4) != 1)
        {
		msg += HIR"那人长笑声中，几个起落已经消失得无影无踪。\n"NOR;
                ob->set("marks/xieyanke", -1);
                log_file("static/xieyanke",sprintf(" %s(%s)于%s遇见谢烟客并错失机缘。\n", ob->query("name"),ob->query("id"),ctime(time()))); 
                destruct(xie);
        }
        message_vision(msg, ob);

        ob->remove_all_enemy();
}

int accept_fight(object me)
{
        command("nono");
        return 0;
}

