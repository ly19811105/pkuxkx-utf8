// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "城墙脚下");
	set("long", @LONG
这里是兰州西城外的一段城墙脚下，城墙经此筑入山体。
LONG );
	set("exits", ([
		//"north" : __DIR__"ximen",
		"north" : __DIR__"outwall4",
		//"north" : __DIR__"west_street2",
		//"south" : __DIR__"west_lane1",
	]));
	set("outdoors", "lanzhou");
	setup();
}

