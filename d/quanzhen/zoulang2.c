// Room: /u/kiss/quanzhen/zhoulang2.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", YEL"走廊"NOR);
	set("long", @LONG
你走在一条走廊上，走廊两边的柱上雕着精美的花纹，四周一片寂静，东边
是玄真台。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "east" : __DIR__"xuanzt.c",
  "west" : __DIR__"zoulang3.c",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
