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
	set("wall",4);
	set("exits", ([
		"northdown" : __DIR__"ximen",
		"south" : __DIR__"wall5",
		//"north" : __DIR__"west_street2",
		//"south" : __DIR__"west_lane1",
	]));
	set("outdoors", "lanzhou");
	setup();
}

