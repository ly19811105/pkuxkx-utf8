// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "一品堂分堂");
	set("long", @LONG
这里西夏一品堂在兰州城分堂的大门口，几个黑衣人在门内若隐若现。虽不
禁止普通人经过，来这里的人却非常少。
LONG );
	set("exits", ([
		//"east"      : __DIR__"dangpu",
		//"west" : __DIR__"jiuguan",
		"north" : __DIR__"west_lane2",
		"enter" : __DIR__"yipin1",
	]));
	set("outdoors", "lanzhou");
	setup();
}

