// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "东门大街");
	set("long", @LONG
这里是东门内的大街，虽然一街之隔，南北两边却是两个不同的世界。
LONG );
	set("exits", ([
		"west"      : __DIR__"east_avenue2",
		"east" : __DIR__"dongmen",
		"north" : __DIR__"east_street1",
		"south" : __DIR__"east_lane1",
	]));
	set("outdoors", "lanzhou");
	setup();
}

