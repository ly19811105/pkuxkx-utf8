#include <ansi.h>
inherit __DIR__"yanmenguan.c";

void create()
{
	set("short", HIC"河滩"NOR);
	set("long", @LONG
这里是一段河滩，应该是黄河的直流，水流湍急。
LONG
	);

    set("exits", ([
        "northwest" : __DIR__"hezhong",   
        "east" : __DIR__"shanluend",
        ]));
    set("road_no",15);
    set("objects", ([
		
        __DIR__"npc/mes" : 1,
		
	    ]));
	set("outdoors", "jinyang");
	setup();
	
}



