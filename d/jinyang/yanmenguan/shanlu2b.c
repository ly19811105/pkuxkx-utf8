#include <ansi.h>
inherit __DIR__"yanmenguan.c";

void create()
{
	set("short", "山路");
	set("long", @LONG
这里是一段郁郁葱葱的山路，行走起来极为艰难。
LONG
	);

    set("exits", ([
        "north" : __DIR__"shanlu1b",        
        "southwest" : __DIR__"shanlu3b",
        ]));
    set("road_no",11);
    set("objects", ([
		
        __DIR__"npc/mes" : 1,
		
	    ]));
	set("outdoors", "jinyang");
	setup();
	
}



