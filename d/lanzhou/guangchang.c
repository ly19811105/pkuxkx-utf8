// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", WHT"府前广场"NOR);
	set("long", @LONG
这里是兰州城的中心，整块石条铺成的道路十分气派，北面只有高官显宦才
能居住，而南城是兰州商业的中心。
LONG );
	set("exits", ([
		"east" : __DIR__"east_avenue2",
		"west" : __DIR__"west_avenue2",
		"north" : __DIR__"north_avenue1",
		"south" : __DIR__"south_avenue1",
	]));
	set("outdoors", "lanzhou");
	setup();
}

