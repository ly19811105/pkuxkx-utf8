// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "东门小巷");
	set("long", @LONG
这里是兰州东门内的向南的一条小巷，十分繁华也十分嘈杂。
LONG );
	set("exits", ([
		"east"      : __DIR__"qianzhuang",
		//"west" : __DIR__"datiepu",
		"north" : __DIR__"east_avenue1",
		"south" : __DIR__"east_lane2",
	]));
	set("outdoors", "lanzhou");
	setup();
}

