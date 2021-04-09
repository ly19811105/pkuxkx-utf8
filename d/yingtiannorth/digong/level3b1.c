inherit __DIR__"karma_room.c";
#include <ansi.h>
#include "level3move.h"
void create()
{
	set("short", HBCYN+HIW"甬道乙一"NOR);
	set("long", @LONG
这里是一条长长的甬道，墙上泛出幽幽的荧光，勉强可以看清方向。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 3);
	set("passage", 1);
	set("row",1);
	set("col",1);
	set("exits", ([
		//"west" : __DIR__"level3b1",
		"north" : __DIR__"level3a1",
		"south" : __DIR__"level3c1",
		"east"  : __DIR__"level3b2",
		//"out" : __DIR__"level3entry",
	]));

	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
