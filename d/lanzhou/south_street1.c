// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "出城小路");
	set("long", @LONG
这里是兰州城南城的边缘，再往南走两座山峰挡住了视线。
LONG );
	set("exits", ([
		"north" : __DIR__"south_avenue2",
		"south" : __DIR__"south_street2",
	]));
	set("outdoors", "lanzhou");
	setup();
}

