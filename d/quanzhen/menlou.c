// Room: /u/kiss/quanzhen/menlou.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "门楼");
	set("long", @LONG
门楼与别的房间没有什么不同，只是比别的房间稍小些，房间里没有什么东
西。西边就是门屋，东边是天尊殿。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"menwu.c",
  "east" : __DIR__"tianzd.c",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
