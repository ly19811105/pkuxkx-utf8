// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "东门小巷");
	set("long", @LONG
这里是兰州东门内的向南的一条小巷，南面是著名的玉佛寺。
LONG );
	set("exits", ([
		"east"      : __DIR__"player_shop",
		//"west" : __DIR__"yaopu",
		"north" : __DIR__"east_lane1",
		"south" : __DIR__"yufosi",
	]));
	set("outdoors", "lanzhou");
	setup();
}

