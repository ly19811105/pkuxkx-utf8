// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", HIB"地藏殿"NOR);
	set("long", @LONG
这里是玉佛寺的地藏殿，供奉着地藏菩萨的塑像。
LONG );
	set("exits", ([
		//"west" : __DIR__"yaopu",
		"west" : __DIR__"yufo3",
	]));
	//set("outdoors", "lanzhou");
	setup();
}

