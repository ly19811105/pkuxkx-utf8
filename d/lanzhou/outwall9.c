// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "城墙脚下");
	set("long", @LONG
这里是兰州东城外的一段城墙脚下，城墙在这里和兰山形成一体。
LONG );
	set("exits", ([
		//"north" : __DIR__"dongmen",
		"north" : __DIR__"outwall8",
		//"north" : __DIR__"west_street2",
		//"south" : __DIR__"west_lane1",
	]));
	set("outdoors", "lanzhou");
	setup();
}

