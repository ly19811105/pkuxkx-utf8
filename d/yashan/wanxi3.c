//模板
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "牙山湾西口");
	set("long", @LONG
这里就进入牙山湾了，由于这里即将开战，
这里的百姓能逃得了的，早就逃了，剩下的清
兵在这里列队忙出忙进．
LONG
	);
	set("outdoors", "yanshan");
	set("objects", ([
		 __DIR__"npc/qingbing.c": random(5), 
		]));
	set("exits", ([ 
		  "west" : __DIR__"yashanxi1.c",
		  "east" : __DIR__"wanxi2.c",
		]));
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}

