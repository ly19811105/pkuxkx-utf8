// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", HIW"观音殿"NOR);
	set("long", @LONG
这里是玉佛寺的观音殿，供奉着观音菩萨的塑像。
LONG );
	set("exits", ([
		//"west" : __DIR__"yaopu",
		"east" : __DIR__"yufo3",
	]));
	//set("outdoors", "lanzhou");
	setup();
}

