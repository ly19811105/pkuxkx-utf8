// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "弥勒殿"NOR);
	set("long", @LONG
这里是玉佛寺的弥勒殿，供奉着弥勒佛的塑像，游客到此止步了。
LONG );
	set("exits", ([
		"south" : __DIR__"yufo9",
		"west" : __DIR__"yufo7",
		"east" : __DIR__"yufo8",
		"north" : __DIR__"yufo3",
	]));
	//set("outdoors", "lanzhou");
	setup();
}

