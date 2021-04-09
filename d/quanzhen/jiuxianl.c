// Room: /u/kiss/quanzhen/jiuxianl.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", RED"九仙楼"NOR);
	set("long", @LONG
正如其名，一进九仙楼，就仿佛进入仙境一般，四周雾气弥漫，你仿佛有飘
飘成仙的感觉，东边是凝灵阁，北边是天尊殿，西边是游仙阁。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"zoulang19.c",
  "east" : __DIR__"ninglg.c",
   "west" : __DIR__"youxiang.c",
  "south" : __DIR__"tianzjt.c",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
