//train3_xiuxi.c  休息室
//by zoom
//2003.3.30

#include <ansi.h>

inherit ROOM;

void create()
{
set("short", "休息室");
set("long", @LONG
几张木板床一字排开，床的被褥叠的整整齐齐，床头各有一个小柜子， 除了
这些，屋内就别无它物。累了就睡一觉儿吧。
LONG );
set("no_fight", 1);
set("exits",  ([
        "east"  : __DIR__"train3_keting.c",
      ]));
        set("sleep_room",1);

        setup();
        replace_program(ROOM);
}