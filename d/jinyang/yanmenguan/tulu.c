#include <ansi.h>
inherit __DIR__"yanmenguan.c";

void create()
{
	set("short", YEL"土路"NOR);
	set("long", @LONG
这是一条土路，往北是一条笔直的官道，往南就更加难走了。
LONG
	);

    set("exits", ([
        "north" : __DIR__"guandao2",        
        "south" : __DIR__"xiaolu",
        ]));
    set("road_no",3);
    set("objects", ([
		
        __DIR__"npc/mes" : 1,
		
	    ]));
	set("outdoors", "jinyang");
	setup();
	
}



