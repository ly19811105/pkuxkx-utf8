// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "卧房"NOR);
	set("long", @LONG
这里是玉佛寺的给一些居士留宿的卧房。
LONG );
	set("exits", ([
//		"south" : __DIR__"yufo9",
		"west" : __DIR__"yufo6",

	]));
	//set("outdoors", "lanzhou");
	setup();
}

