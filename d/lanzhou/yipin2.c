// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "宿房");
	set("long", @LONG
这里是一品堂学员和教士的睡房。
LONG );
	set("exits", ([
		"east"      : __DIR__"yipin1",
	]));
	//set("outdoors", "lanzhou");
	setup();
}

