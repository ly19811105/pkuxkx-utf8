// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
#include "wall.h"
void create()
{
	set("short", "城墙上");
	set("long", @LONG
这里是兰州西城的一段城墙上。
LONG );
	set("wall",2);
	set("exits", ([
		"south" : __DIR__"wall1",
		"northeast" : __DIR__"wall3",
		//"north" : __DIR__"west_street2",
		//"south" : __DIR__"west_lane1",
	]));
	set("jump_path",__DIR__"west_street2");
	set("outdoors", "lanzhou");
	setup();
}

