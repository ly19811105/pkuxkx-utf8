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
	set("path", 1);
	set("exits", ([
		//"up" : (:get_path:),
		"out" : __DIR__"level4entry",
		"east" : __DIR__"level4path2",
		"north" : __DIR__"level4treec",
		"south" : __DIR__"level4treee",
	]));

	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
