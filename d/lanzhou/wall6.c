// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
#include "wall.h"
void create()
{
	set("short", "城墙上");
	set("long", @LONG
这里是兰州东城的一段城墙上。
LONG );
	set("wall",6);
	set("exits", ([
		"north" : __DIR__"wall7",
		"southdown" : __DIR__"dongmen",
		//"north" : __DIR__"west_street2",
		//"south" : __DIR__"west_lane1",
	]));
	set("jump_path",__DIR__"east_street1");
	set("outdoors", "lanzhou");
	setup();
}
