inherit __DIR__"karma_room.c";
#include <ansi.h>
#include "level2maze.h"
void create()
{
	set("short", "地宫甬道");
	set("long", @LONG
这里是一条长长的甬道，不知通向何方。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 2);
	set("maze", 6);
	setup();
	init_maze(2);
}
