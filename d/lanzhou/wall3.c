// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
#include "wall.h"
void create()
{
	set("short", "城墙上");
	set("long", @LONG
这里是兰州西城的一段城墙上，这段城墙和行宫的围墙连成一体。
LONG );
	set("wall",3);
	set("exits", ([
		"southwest" : __DIR__"wall2",
		//"northeast" : __DIR__"wall3",
		//"north" : __DIR__"west_street2",
		//"south" : __DIR__"west_lane1",
	]));
	set("outdoors", "lanzhou");
	setup();
}

