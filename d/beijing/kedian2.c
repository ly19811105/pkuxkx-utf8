//Cracked by Roath
// ROOM:  /d/beijing/kedian2.c
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIC"客栈二楼"NOR);
        set("long",
CYN"这是一间很大的客房，陈设十分简陋。靠墙放了十几张小
木床，不少客人正和衣而卧，满屋子都是呼呼的打酣声。西边
有张床是空的，你蹑手蹑脚地走了过去。\n"NOR
        );

        set("sleep_room",1);

        set("exits", ([
                "down" : __DIR__"kedian",
        ]));

        set("cost", 2);
        setup();
}

int valid_leave(object me, string dir)
{

        if (dir == "down" ) me->delete_temp("rent_paid");

        return ::valid_leave(me, dir);
}
