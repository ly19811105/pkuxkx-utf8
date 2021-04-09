// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", CYN"西门内大街"NOR);
	set("long", @LONG
这里是一条繁华的大街，全部青石铺就的路面在西北十分罕见，东面的广场
非常热闹。
LONG );
	set("exits", ([
		"east"      : __DIR__"guangchang",
		"west" : __DIR__"west_avenue1",
		"north" : __DIR__"cishi",
		"south" : __DIR__"machehang",
	]));
	set("outdoors", "lanzhou");
	setup();
}

