// biwuchang.cg.c
#include <ansi.h>
inherit ROOM;
int do_none();
void create()
{
        set("short", HIR"比武场"NOR );
        set("long", HIY@LONG
说英雄谁是英雄。这里是扬州城里唯一的比武场，四周旗杆林立。到处都是
观战的人群，不时发出一阵阵喝彩声。比武台中央站着江湖上黑白两道皆敬畏的
老侠「铁手丹心」。
LONG NOR);
        set("exits", ([
                "northwest" : "/d/city/beidajie1",
//              "up" : "/d/bwdh/square.c",
								"east" : "/u/vast/BM/bombroom.c",

        ]));
        set("objects",([
                "/d/city/npc/tieshou" : 1,
   //             "/d/city/npc/juemennpc" : 1,
                "/d/shaolin/npc/tie-ren" : 1,
				"/d/lvliu/npc/jiguanren0" : 1,
        ]));
        set("no_die", 1);
        set("no_clean_up", 0);
        set("outdoors", "xx" );
        set("room_location", "/d/city/");
        setup();
        call_other("/clone/board/fight_b", "???");
}
// changed by akuma 
// 防止有人利用比武来练功
void init()
{
        add_action("do_none",({"study","learn","tuna","exercise","dz","apprentice","research","practice",}));
// add_action("do_none1",({"kill","killall"}));
        add_action("do_quit",({"quit","suicide"}));
}
int do_none()
{
        write("对不起，比武场中请不要练功。\n");
        return 1;
}
int do_quit()
{
        this_player()->move("/adm/room/quitroom");
        return 1;
}
/*
void alternative_die (object me)
{
         if(userp(me))
         {
                message_vision("铁游夏上前扶起"+me->query("name")+"道：“切磋武功，不应伤及性命”。\n",me);
                if (me->query("qi")<10) me->set("qi",10);
                if (me->query("max_qi")<10) me->set("max_qi",10);
                if (me->query("jing")<10) me->set("jing",10);
                  me->remove_all_killer();
                  me->remove_all_enemy();
                if (me->query("max_jing")<10) me->set("max_jing",10);
                return;
        }       
         else
                me->die();
}
int do_none1()
{
        object ob = this_player();
        if(ob->is_busy())
        {
                write("你正忙着呢。\n");
                return 1;
        }
        tell_object(ob,HIR"铁游夏脸色一沉道：「这里是比试的场所，不可妄动杀念！」\n"NOR);
        ob->start_busy(2);
        return 1;
}
*/
