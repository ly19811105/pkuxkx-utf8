//train4_lianwu.c
//by zoom
//2003.4.7

#include <ansi.h>

inherit ROOM;

void create()
{
set("short", HIR"比武场"NOR);
set("long", @LONG
这里是新手学堂专门给学员准备的用来，场上学员们两两捉对比试着，你不禁跃跃欲试。
旁边还有几个木人，显然是练习用的。
LONG );
set("exits",  ([
        "out"   : __DIR__"train5.c",
      ]));
set("objects",([
        "/d/shaolin/npc/mu-ren" : 4
]));
setup();
}