// Room: /u/hacky/quanzhen/shifang.c
// Made by: hacky

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "师房");
	set("long", @LONG
师房是王重阳休息的地方，内有一张宽大的木床，北边是门屋。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "north" : __DIR__"menwu.c",
]));
	set("objects", ([ /* sizeof() == 1 */
  CLASS_D("quanzhen")+"/wang" : 1,
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
