// Room: /u/kiss/quanzhen/zhoulang1.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", YEL"走廊"NOR);
	set("long", @LONG
你走在一条走廊上，走廊两边的柱上雕着精美的花纹，四周一片寂静，西边
是玄宗台，北边是俗客房。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"xuanzt.c",
  "north" : __DIR__"sukefang.c",
  "east" : __DIR__"zoulang6",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
