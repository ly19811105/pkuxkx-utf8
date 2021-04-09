// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "西门大街");
	set("long", @LONG
这里是西门内的大街，北面是西夏官员的府邸，南面却十分繁华。
LONG );
	set("exits", ([
		"east"      : __DIR__"west_avenue2",
		"west" : __DIR__"ximen",
		"north" : __DIR__"west_street1",
		"south" : __DIR__"west_lane1",
	]));
	set("outdoors", "lanzhou");
	setup();
}

