inherit __DIR__"karma_room.c";
#include <ansi.h>

void create()
{
	set("short", HIR"玛瑙境入口"NOR);
	set("long", @LONG
这里是地宫第六层玛瑙境的入口。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 6);
	set("entry", 1);
	set("exits", ([
		//"up" : (:get_path:),
		"up" : __DIR__"level5exit",
		"enter" : __DIR__"level6path1",
		//"west" : __DIR__"wall1",
	]));

	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
void init()
{
	tell_object(this_player(),HBWHT+HIR+"在这一关中，玩家需要组队打败拦路的沙盗，才能通过！\n"+NOR);
	::init();
}