//train4_lianwu.c
//by zoom
//2003.4.7

#include <ansi.h>

inherit ROOM;

void create()
{
set("short", HIR"练武场"NOR);
set("long", @LONG
这里是新手学堂的练武场，旁边摆满了十八般兵器，这里设备齐全，很多年
轻弟子正在这里勤修苦练，教头在一旁时不时的指点一二。
LONG );
set("exits",  ([
        "up"    : __DIR__"train5.c",
        "west"    : __DIR__"train4_lianwu2.c",
        "out"   : __DIR__"train4.c",
      ]));
        set("objects", ([
                __DIR__"npc/trainer" : 1,
        ]));
        setup();
}