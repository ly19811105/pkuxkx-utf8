// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "刺史府大门"NOR);
	set("long", @LONG
这里是兰州刺史府的大门，不时有士兵来回巡弋着。
LONG );
	set("exits", ([
		"east"      : __DIR__"north_avenue1",
		//"west" : __DIR__"west_avenue1",
		//"north" : __DIR__"cishi",
		"south" : __DIR__"west_avenue2",
	]));
	set("outdoors", "lanzhou");
	setup();
}

