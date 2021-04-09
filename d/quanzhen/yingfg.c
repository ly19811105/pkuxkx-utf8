// Room: /u/kiss/quanzhen/yingfg.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIW"迎风阁"NOR);
	set("long", @LONG
站在迎风阁前，有一种居高临下的感觉，一切仿佛尽收于眼底，朱红色的八
角形阁顶由八棵紫檀木制成的柱子支撑。

LONG
	);
	set("exits", ([ /* sizeof() == 3 */
  "west" : __DIR__"feinuang.c",
  "south" : __DIR__"jingnl.c",
  "north" : __DIR__"chenglt.c",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
