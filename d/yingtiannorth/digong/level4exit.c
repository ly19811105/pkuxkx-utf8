inherit __DIR__"karma_room.c";
#include <ansi.h>

void create()
{
	set("short", HIY"珊瑚境出口"NOR);
	set("long", @LONG
这里是地宫第四层珊瑚境的出口。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 4);
	set("exit", 1);
	set("exits", ([
		//"up" : (:get_path:),
		"down" : __DIR__"level5entry",
		"enter" : __DIR__"level4river2",
		//"west" : __DIR__"wall1",
	]));

	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
