// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", HIR"行宫大门"NOR);
	set("long", @LONG
这里是兰州行宫的大门，几位全身黑甲的士兵一丝不苟的站着岗。
LONG );
	set("exits", ([
		//"east" : __DIR__"jiangjun",
		//"west" : __DIR__"guoshi",
		//"north" : __DIR__"xinggong",
		"south" : __DIR__"north_avenue2",
	]));
	set("outdoors", "lanzhou");
	setup();
}

