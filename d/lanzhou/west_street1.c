// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
#include "look_wall.h"
void create()
{
	set("short", "西门内街");
	set("long", @LONG
这里是被称为西门内街，却是一些显宦们府邸的后巷，虽没有很多人经过，
士兵也偶尔巡逻至此。西面可以眺望兰州西城的城墙头(wall)。
LONG );
	set("item_desc",(["wall":(:look_wall:)]));
	set("exits", ([
		"south" : __DIR__"west_avenue1",
		//"west" : __DIR__"ximen",
		"north" : __DIR__"west_street2",
		//"south" : __DIR__"west_lane1",
	]));
	set("wall",__DIR__"wall1");
	set("outdoors", "lanzhou");
	setup();
}

