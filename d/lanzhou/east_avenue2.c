// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", CYN"东门内大街"NOR);
	set("long", @LONG
这里是一条繁华的大街，全部青石铺就的路面在西北十分罕见，西面的广场
非常热闹。
LONG );
	set("exits", ([
		"west"      : __DIR__"guangchang",
		"east" : __DIR__"east_avenue1",
		"north" : __DIR__"zuru",
		"south" : __DIR__"datie",
	]));
	set("outdoors", "lanzhou");
	setup();
}

