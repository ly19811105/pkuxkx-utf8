// Room: /u/kiss/quanzhen/zoulang6.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", YEL"走廊"NOR);
	set("long", @LONG
你走在一条走廊上，走廊两边的柱上雕着精美的花纹，四周一片寂静，北边
是斋堂，东边是净人坊。
LONG
	);
	set("exits", ([ /* sizeof() == 3 */
  "north" : __DIR__"zhaitang.c",
  "west" : __DIR__"zhoulang1.c",
  "east" : __DIR__"jingrenf.c",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
