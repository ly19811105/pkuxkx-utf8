// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "食堂");
	set("long", @LONG
这里是一品堂学员和教士的食堂。
LONG );
	set("exits", ([
		"west"      : __DIR__"yipin1",
	]));
	//set("outdoors", "lanzhou");
	setup();
}

