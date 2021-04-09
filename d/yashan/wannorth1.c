//模板
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "牙山湾北路");
	set("long", @LONG
牙山湾往北有几个兵营，里面驻扎着一部分
北洋舰队的官兵，
LONG
	);
	set("outdoors", "yanshan");
	set("objects", ([
		  
		]));
	set("exits", ([ 
          "south" : __DIR__"center.c",
		  "north" : __DIR__"nbingying.c",
		  "west"  : __DIR__"wbingying.c",
		  "east"  : __DIR__"ebingying.c",
		]));
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}

