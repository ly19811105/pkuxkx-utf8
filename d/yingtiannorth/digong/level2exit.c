inherit __DIR__"karma_room.c";
#include <ansi.h>

void create()
{
	set("short", WHT"珍珠境出口"NOR);
	set("long", @LONG
这里是地宫第二层珍珠境的出口。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 2);
	set("exit", 1);
	set("exits", ([
		//"up" : (:get_path:),
		"down" : __DIR__"level3entry",
		//"north" : __DIR__"shanlus1",
		//"west" : __DIR__"wall1",
	]));

	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
