// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "城墙脚下");
	set("long", @LONG
这里是兰州东城外的一段城墙脚下。
LONG );
	set("exits", ([
		"south" : __DIR__"dongmen",
		"north" : __DIR__"outwall7",
		//"north" : __DIR__"west_street2",
		//"south" : __DIR__"west_lane1",
	]));
	set("outdoors", "lanzhou");
	setup();
}

