// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "玉佛寺门口");
	set("long", @LONG
玉佛寺是兰州最大的一家寺庙，信徒众多，上香的人络绎不绝。
LONG );
	set("exits", ([
		//"west" : __DIR__"yaopu",
		"north" : __DIR__"east_lane2",
		"enter" : __DIR__"yufo1",
	]));
	set("outdoors", "lanzhou");
	setup();
}

