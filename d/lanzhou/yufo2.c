// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", HIC"天王殿"NOR);
	set("long", @LONG
这里是玉佛寺的天王殿，礼佛的善男信女们络绎不绝。
LONG );
	set("exits", ([
		//"west" : __DIR__"yaopu",
		"northdown" : __DIR__"yufo1",
		"south" : __DIR__"yufo3",
	]));
	//set("outdoors", "lanzhou");
	setup();
}

