
// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "祖儒府大门"NOR);
	set("long", @LONG
西夏部落的大头领被称为祖儒，这里正是祖儒府的大门，不时有士兵来回巡弋着。
LONG );
	set("exits", ([
		"west"      : __DIR__"north_avenue1",
		//"west" : __DIR__"west_avenue1",
		//"north" : __DIR__"cishi",
		"south" : __DIR__"east_avenue2",
	]));
	set("outdoors", "lanzhou");
	setup();
}

