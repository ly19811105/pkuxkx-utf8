inherit __DIR__"lanzhou.c";
#include <ansi.h>
void create()
{
	set("short", "小酒馆"+NOR);
	set("long", @LONG
这里是一家露天的小酒馆，一个『酒』字大旗高高挂着。
LONG
	);
        //set("outdoors", "xitianmu");

	set("exits", ([
		//"northwest" : __DIR__"westgc",
		"east" : __DIR__"west_lane2",
		//"west" : __DIR__"datie",
		//"south" : __DIR__"jiuguan",
	]));
	set("outdoors","lanzhou");
	set("objects", ([
		__DIR__"npc/huoji" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
