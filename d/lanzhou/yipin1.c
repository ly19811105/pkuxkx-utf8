// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "大院");
	set("long", @LONG
这里是一座空旷的院落，几个黑衣人正在比试着。
LONG );
	set("exits", ([
		"east"      : __DIR__"yipin3",
		"west" : __DIR__"yipin2",
		"south" : __DIR__"yipin4",
		"out" : __DIR__"yipin",
	]));
	set("outdoors", "lanzhou");
	setup();
}

