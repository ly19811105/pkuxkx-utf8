// Room: /u/kiss/quanzhen/fenxl.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", YEL"焚香楼"NOR);
	set("long", @LONG
这是全真教的焚香楼，许多在烧香坊中剩下的香就被送到这里烧掉。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"zoulang23.c",
  "north" : __DIR__"feinuang.c",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
