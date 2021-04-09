inherit __DIR__"karma_room.c";
#include <ansi.h>

void create()
{
	set("short", HIW"砗磲境入口"NOR);
	set("long", @LONG
这里是地宫第七层砗磲境的入口。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 7);
	set("entry", 1);
	set("exits", ([
		//"up" : (:get_path:),
		"up" : __DIR__"level6exit",
		//"north" : __DIR__"shanlus1",
		"enter" : __DIR__"level7path1",
	]));

	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
void init()
{
	tell_object(this_player(),HBCYN+HIW+"在这一关中，不同玩家必须分开出手，战胜地宫守卫后离开！\n"+NOR);
	::init();
}