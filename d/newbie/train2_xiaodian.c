//train2.c
//modified from xo
//by zoom
//2003.3.30

#include <ansi.h>

inherit ROOM;

void create()
{
set("short", "小店");
set("long", @LONG
这里是一家小店，各种生活用品应有尽有，小二看你近来，赶忙迎了上来。
新手可以在这里练习[1;32m(buy，get，drop，list，eat，drink)[37;0m等指令。
要是没钱，就先去菜园赚点吧。
LONG );
set("no_fight", 1);
set("exits",  ([
        "north"  : __DIR__"train2_center.c",
      ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
        setup();
        replace_program(ROOM);
}