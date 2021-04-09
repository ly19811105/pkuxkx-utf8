// Room: /u/kiss/quanzhen/shoudy.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", YEL"受道院"NOR);
	set("long", @LONG
这里是全真教的受道院，是用来惩罚那些犯了过错的弟子的地方，房间陈设
很简单，几个蒲团，几张方桌，北边是九真楼，西边是说法院。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"shuofy.c",
  "north" : __DIR__"jiuzhenl.c",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
