// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "斋堂"NOR);
	set("long", @LONG
这里是玉佛寺的斋堂，提供一些斋菜给僧人和游客。
LONG );
	set("exits", ([
//		"south" : __DIR__"yufo9",
		"east" : __DIR__"yufo6",

	]));
	//set("outdoors", "lanzhou");
	setup();
}

