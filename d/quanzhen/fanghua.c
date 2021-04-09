// Room: /u/kiss/quanzhen/fanghua.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "芳花");
set("outdoors","quanzhen");
	set("long", @LONG
你走到了全真的后院，这里开满了各种各样的花朵、牡丹、月季、玫瑰……五
颜六色，应有尽有，一股花香扑鼻而来，你简直要被陶醉了。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"zoulang20.c",
  "west" : __DIR__"qichao.c",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
