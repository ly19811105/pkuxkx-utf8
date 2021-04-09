// Room: /u/kiss/quanzhen/zoulang10.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", YEL"走廊"NOR);
	set("long", @LONG
你走在一条走廊上，走廊两边的柱上雕着精美的花纹，四周一片寂静，北边
是说法院，西边是校经房，南边是天尊殿，东边是写经房。
LONG
	);
	set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"shuofy.c",
  "west" : __DIR__"jiaojf.c",
  "south" : __DIR__"tianzd.c",
  "east" : __DIR__"xiejingf.c",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
