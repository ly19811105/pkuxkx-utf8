// biwuchang.cg.c
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", HIR"比武场"NOR );
        set("long", HIY@LONG
说英雄谁是英雄。这里是扬州城里唯一的比武场，四周旗杆林立
到处都是观战的人群，不时发出一阵阵喝彩声。比武台中央站着江湖
上黑白两道皆敬畏的老侠“铁手丹心”。
LONG NOR
        );
        set("exits", ([ /* sizeof() == 1 */
//          "northwest" : __DIR__"beidajie1",
              "up" : "/d/bwdh/square.c",
        ]));
        set("objects",([
                "/d/city/npc/tieshou" : 1,
        ]));
       set("no_die", 1);
        set("no_clean_up", 0);
        set("outdoors", "xx" );
        setup();
	call_other("/clone/board/fight_b", "???");
}

// changed by akuma 
// 防止有人利用比武来练功

void init()
{
	object me=this_player();
	add_action("do_none",({"lian","study","xue","learn","dazuo","tuna","exercise","apprentice","du","research","practice",}));
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

int valid_leave(object me,string dir)
{
    if(dir == "up")
    {
        if(me->query("age")<18&&!wizardp(me))
            return notify_fail("小毛孩不能到这种地方去！\n");
        if(me->query("is_huoji") )
            return notify_fail("伙计不要去那里");
    }
    return ::valid_leave(me,dir);
}
