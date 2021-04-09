// Room: /u/kiss/quanzhen/feinuang.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", RED"飞鸾阁"NOR);
	set("long", @LONG
这是一间宽敞的亭阁，几根大红圆柱顶在四周，柱上雕龙画栋，上刻一副对
联：阶下举杯邀月饮，篱边信步赏花开。北边是散花台，东边是迎风阁，西边是
凝灵阁，南边是焚香楼。
LONG
	);
	set("exits", ([ /* sizeof() == 4 */
  "south" : __DIR__"fenxl.c",
  "north" : __DIR__"sanhuat.c",
  "west" : __DIR__"ninglg.c",
  "east" : __DIR__"yingfg.c",
]));
   set("objects",([
    __DIR__"npc/liu.c" : 1,
  ]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
