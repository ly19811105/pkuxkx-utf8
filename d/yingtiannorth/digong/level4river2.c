inherit __DIR__"karma_room.c";
#include <ansi.h>

void create()
{
	set("short", "地下河边"NOR);
	set("long", @LONG
这是一条地下河，完全阻挡了向西的道路。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 4);
	set("river",2);
	set("exits", ([
		//"up" : (:get_path:),
		//"east" : __DIR__"level4river",
		"out" : __DIR__"level4exit",
		//"north" : __DIR__"level4treed",
		//"south" : __DIR__"level4treef",
	]));

	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
