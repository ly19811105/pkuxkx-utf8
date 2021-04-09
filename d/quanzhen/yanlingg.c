// Room: /u/kiss/quanzhen/yanlingg.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
         set("short", HIW"延灵阁"NOR);
	set("long", @LONG
这是一处别有韵味的阁楼，窗明几净，石桌上尚余一残局，棋路平和中正，
与全真之武学异曲同工，可见对弈者深得全真武学之要旨。由此向北乃寻真台，
向南为延真楼。
LONG
	);
	set("exits", ([ /* sizeof() == 3 */
  "north" : __DIR__"xunzhent.c",
  "south" : __DIR__"yanzhenl.c",
  "east" : __DIR__"chengyg.c",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
