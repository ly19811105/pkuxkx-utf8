// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "府前大道");
	set("long", @LONG
这里是兰州城南城的大道，两侧是一些店铺，南面依稀可以望见一座山峰。
LONG );
	set("exits", ([
		"east" : __DIR__"yaopu",
		"west" : __DIR__"dangpu",
		"north" : __DIR__"south_avenue1",
		"south" : __DIR__"south_street1",
	]));
	set("outdoors", "lanzhou");
	setup();
}

