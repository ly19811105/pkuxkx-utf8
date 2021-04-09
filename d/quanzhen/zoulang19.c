// Room: /u/kiss/quanzhen/zoulang19.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", YEL"走廊"NOR);
	set("long", @LONG
你走在一条走廊上，走廊两边的柱上雕着精美的花纹，四周一片寂静，南边
就是九仙楼。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"jiuxianl.c",
  "north" : __DIR__"zoulang18",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
