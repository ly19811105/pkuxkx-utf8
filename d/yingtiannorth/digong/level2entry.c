inherit __DIR__"karma_room.c";
#include "tiny_maze.h";
#include <ansi.h>

void create()
{
	set("short", WHT"珍珠境入口"NOR);
	set("long", @LONG
这里是地宫第二层珍珠境的入口。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 2);
	set("entry", 1);
	set("maze_index",5);
	set("exits", ([
		//"up" : (:get_path:),
		"up" : __DIR__"level1exit",
		//"north" : __DIR__"shanlus1",
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
	tell_object(this_player(),HIW+"在这一关中，玩家通过的是一个简易迷宫，迷宫里有一些盗墓贼，你需要清除他们。\n"+NOR);
	::init();
}