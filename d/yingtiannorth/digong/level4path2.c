inherit __DIR__"karma_room.c";
#include <ansi.h>

void create()
{
	set("short", "小路"NOR);
	set("long", @LONG
这是一条小路，两旁是茂密的树林。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 4);
	set("path",2);
	set("exits", ([
		//"up" : (:get_path:),
		"east" : __DIR__"level4river",
		"west" : __DIR__"level4path1",
		"north" : __DIR__"level4treed",
		"south" : __DIR__"level4treef",
	]));

	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
