// Room: /u/kiss/quanzhen/menwu.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "门屋");
	set("long", @LONG
你走到了一间门屋内，四周静悄悄的，没有一点声音。南边就是师房，东边
是门楼。
LONG
	);
	set("exits", ([ /* sizeof() == 3 */
  "south" : __DIR__"shifang.c",
  "west" : __DIR__"zoulang11.c",
  "east" : __DIR__"menlou.c",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
