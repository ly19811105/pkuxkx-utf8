// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "将军府大门"NOR);
	set("long", @LONG
这里是兰州将军府的大门，不时有士兵来回巡弋着。
LONG );
	set("exits", ([
		"west"      : __DIR__"north_avenue2",
		//"west" : __DIR__"west_avenue1",
		//"north" : __DIR__"cishi",
		"east" : __DIR__"east_street2",
	]));
	set("outdoors", "lanzhou");
	setup();
}

