#include <ansi.h>
inherit __DIR__"yanmenguan.c";

void create()
{
	set("short", HIG"密林深处"NOR);
	set("long", @LONG
这是已经是密林的深处了，这里也很适合布置(dig)陷阱。
LONG
	);

    set("exits", ([
        "northwest" : __DIR__"milin",        
        "south" : __DIR__"chalu",
        ]));
    set("road_no",6);
    set("objects", ([
		
        __DIR__"npc/mes" : 1,
		
	    ]));
	set("outdoors", "jinyang");
	setup();
	
}



