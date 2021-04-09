// Room: /u/kiss/quanzhen/zoulang4.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", YEL"走廊"NOR);
	set("long", @LONG
你走在一条走廊上，走廊两边的柱上雕着精美的花纹，四周一片寂静，南边
是骡马房。
LONG
	);
	set("exits", ([ /* sizeof() == 3 */
  "west" : __DIR__"zoulang5.c",
  "south" : __DIR__"luomaf.c",
  "east" : __DIR__"zoulang3.c",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
