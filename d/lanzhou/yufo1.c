// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "庭院");
	set("long", @LONG
这里是玉佛寺一进的一座庭院，种着几棵大树。
LONG );
	set("exits", ([
		//"west" : __DIR__"yaopu",
		"southup" : __DIR__"yufo2",
		"out" : __DIR__"yufosi",
	]));
	set("outdoors", "lanzhou");
	setup();
}

