// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", HIY"大雄宝殿"NOR);
	set("long", @LONG
这里是玉佛寺的大雄宝殿，东西分别是观音殿和地藏殿。
LONG );
	set("exits", ([
		//"west" : __DIR__"yaopu",
		"north" : __DIR__"yufo2",
		"westup" : __DIR__"yufo4",
		"eastup" : __DIR__"yufo5",
		"south" : __DIR__"yufo6",
	]));
	//set("outdoors", "lanzhou");
	setup();
}

