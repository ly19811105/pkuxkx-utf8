//模板
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "破屋");
	set("long", @LONG
这是一个破屋，可以看得出这里原来是一家
渔夫居住的地方，地上散落着一些渔具，都破烂
不堪。
LONG
	);
	set("objects", ([
		"/d/lingxiao/npc/dizi_yashan" : random(2),
		]));
	set("exits", ([ 
		  "east"  : __DIR__"wansouth2.c",
		]));
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}

