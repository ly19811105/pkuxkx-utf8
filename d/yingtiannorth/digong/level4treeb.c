inherit __DIR__"karma_room.c";
#include <ansi.h>
#include "chop.h"
void create()
{
	set("short", "树林"NOR);
	set("long", @LONG
这里是一片树林，满林都是参天的大树。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 4);
	set("tree",1);
	set("exits", ([
		//"up" : (:get_path:),
		//"east" : __DIR__"level4river",
		"west" : __DIR__"level4treea",
		//"north" : __DIR__"level4treed",
		"south" : __DIR__"level4treed",
	]));

	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
