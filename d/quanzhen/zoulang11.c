// Room: /u/hacky/quanzhen/zoulang11.c
// Made by: hacky

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", YEL"走廊"NOR);
	set("long", @LONG
你走在一条走廊上，走廊两边的柱上雕着精美的花纹，四周一片寂静，南边
是浴堂，东边是门屋。
LONG
	);
	set("exits", ([ /* sizeof() == 3 */
  "west" : __DIR__"zoulang12.c",
  "south" : __DIR__"gengyis.c",
  "east" : __DIR__"menwu.c",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
