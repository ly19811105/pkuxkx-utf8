// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "府前大道");
	set("long", @LONG
这里是兰州城南城的大道，两侧都是店铺，这里也是叫花子聚集的地方。
LONG );
	set("exits", ([
		"east" : __DIR__"datiepu",
		"west" : __DIR__"machehang",
		"south" : __DIR__"south_avenue2",
		"north" : __DIR__"guangchang",
	]));
	set("outdoors", "lanzhou");
	setup();
}

