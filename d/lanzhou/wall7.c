// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
#include "wall.h"
void create()
{
	set("short", "城墙上");
	set("long", @LONG
这里是兰州东城的一段城墙上，城墙到此而至，似乎断头路一般。
LONG );
	set("wall",7);
	set("exits", ([
		"south" : __DIR__"wall6",
		//"southdown" : __DIR__"dongmen",
		//"north" : __DIR__"west_street2",
		//"south" : __DIR__"west_lane1",
	]));
	set("outdoors", "lanzhou");
	set("jump_path",__DIR__"east_street2");
	setup();
}
