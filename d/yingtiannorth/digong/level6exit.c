inherit __DIR__"karma_room.c";
#include <ansi.h>

void create()
{
	set("short",HIR"玛瑙境出口"NOR);
	set("long", @LONG
这里是地宫第六层玛瑙境的出口。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 6);
	set("exit", 1);
	set("exits", ([
		//"up" : (:get_path:),
		"down" : __DIR__"level7entry",
		"enter" : __DIR__"level6path4",
		//"west" : __DIR__"wall1",
	]));

	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
