inherit __DIR__"karma_room.c";
#include <ansi.h>

void create()
{
	set("short", HIB"麝香境出口"NOR);
	set("long", @LONG
这里是地宫第一层麝香境的出口。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 1);
	set("exit", 1);
	set("exits", ([
		//"up" : (:get_path:),
		"down" : __DIR__"level2entry",
		//"north" : __DIR__"shanlus1",
		//"west" : __DIR__"wall1",
	]));

	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
