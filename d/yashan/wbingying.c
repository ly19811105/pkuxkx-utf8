//模板
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "兵营");
	set("long", @LONG
这里是牙山的兵营，清政府已经把牙山变
成了，一个驻军的基地，由于和日本交战在即，
全国的兵都往牙山调度，这里的兵营已经拥挤
不堪了。
LONG
	);
	set("objects", ([
		__DIR__"npc/qingbing.c": random(5),
		  
		]));
	set("exits", ([ 
		  "east"  : __DIR__"wannorth1.c",
		]));
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}

