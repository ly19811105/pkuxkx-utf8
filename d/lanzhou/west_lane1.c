// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "西门小巷");
	set("long", @LONG
这里是兰州西门内的向南的一条小巷，说是小巷，却店铺林立。
LONG );
	set("exits", ([
		//"east"      : __DIR__"machehang",
		"west" : __DIR__"kedian",
		"north" : __DIR__"west_avenue1",
		"south" : __DIR__"west_lane2",
	]));
	set("outdoors", "lanzhou");
	setup();
}

