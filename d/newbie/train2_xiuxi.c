//train2.c
//modified from xo
//by zoom
//2003.3.30

#include <ansi.h>

inherit ROOM;

void create()
{
set("short", "休息室");
set("long", @LONG
几张木板床一字排开，床的被褥叠的整整齐齐，床头各有一个小柜子， 除了
这些，屋内就别无它物。累了就睡一觉儿吧[1;32m(sleep)[37;0m。睡觉可以补充精气，是很好
的快速恢复的方法。
LONG );
set("no_fight", 1);
set("exits",  ([
        "south"  : __DIR__"train2_center.c",
      ]));
        set("objects", ([
//                __DIR__"npc/xx" : 1,
        ]));
        set("sleep_room",1);

        setup();
        replace_program(ROOM);
}