#include <ansi.h>
inherit __DIR__"yanmenguan.c";

void create()
{
	set("short", "山路尽头");
	set("long", @LONG
终于走出了山间，前面是一段开阔的河滩。
LONG
	);

    set("exits", ([
        "northeast" : __DIR__"shanlu3b",   
        "north" : __DIR__"shanlu3a",
        "west" : __DIR__"hetan",
        ]));
    set("road_no",14);
    set("objects", ([
		
        __DIR__"npc/mes" : 1,
		
	    ]));
	set("outdoors", "jinyang");
	setup();
	
}



