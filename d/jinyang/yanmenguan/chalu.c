#include <ansi.h>
inherit __DIR__"yanmenguan.c";

void create()
{
	set("short", "岔路");
	set("long", @LONG
这里是一段三岔路口，向南的方向被分为两条。
LONG
	);

    set("exits", ([
        "north" : __DIR__"milin2",        
        "southwest" : __DIR__"shanlu1a",
        "southeast" : __DIR__"shanlu1b",
        ]));
    set("road_no",7);
    set("objects", ([
		
        __DIR__"npc/mes" : 1,
		
	    ]));
	set("outdoors", "jinyang");
	setup();
	
}



