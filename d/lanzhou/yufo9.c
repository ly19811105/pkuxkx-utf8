// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "祖师堂"NOR);
	set("long", @LONG
这里供奉着玉佛寺历代祖师的牌位，终年香火不断。出去通往后山。
LONG );
	set("exits", ([
		"out" : __DIR__"yufo10",
		"north" : __DIR__"yufo6",

	]));
	//set("outdoors", "lanzhou");
	setup();
}

