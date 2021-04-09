// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
#include "wall.h"
void create()
{
	set("short", "城墙上");
	set("long", @LONG
这里是兰州西南角的一段城墙上，城墙夹山而建。
LONG );
	set("wall",5);
	set("exits", ([
		"north" : __DIR__"wall4",
		"eastup" : __DIR__"wuquan_w2",
		//"north" : __DIR__"west_street2",
		//"south" : __DIR__"west_lane1",
	]));
	set("jump_path",__DIR__"jiuguan");
	set("outdoors", "lanzhou");
	setup();
}

int valid_leave(object me,string dir)
{
	if (dir=="eastup"&&me->query_dex()<75)
	return notify_fail("东面山体实在过于陡峭，非人力可攀。\n");
	return ::valid_leave(me,dir);
}