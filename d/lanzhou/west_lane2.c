// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "西门小巷");
	set("long", @LONG
这里是兰州西门内的向南的一条小巷，东西头都是店铺，南面却禁止普通人
经过。
LONG );
	set("exits", ([
		//"east"      : __DIR__"dangpu",
		"west" : __DIR__"jiuguan",
		"north" : __DIR__"west_lane1",
		"south" : __DIR__"yipin",
	]));
	set("outdoors", "lanzhou");
	setup();
}

