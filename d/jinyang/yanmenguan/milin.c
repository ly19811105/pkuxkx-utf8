#include <ansi.h>
inherit __DIR__"yanmenguan.c";

void create()
{
	set("short", "密林");
	set("long", @LONG
这是一片密林，看不清楚周围的情况，这里适合布置(dig)陷阱。
LONG
	);

    set("exits", ([
        "northeast" : __DIR__"xiaolu",        
        "southeast" : __DIR__"milin2",
        ]));
    set("road_no",5);
    set("objects", ([
		
        __DIR__"npc/mes" : 1,
		
	    ]));
	set("outdoors", "jinyang");
	setup();
	
}



