// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "山间小路");
	set("long", @LONG
这里是兰州以南一条山间小路，两侧可以看见葱葱郁郁的山岭(hill)。
LONG );
	set("exits", ([
		"northdown" : __DIR__"south_street2",
		"eastup" : __DIR__"lanshan_w2",
	]));
	set("outdoors", "lanzhou");
	setup();
}

