#include <ansi.h>
inherit __DIR__"yanmenguan.c";

void create()
{
	set("short", YEL"荒路"NOR);
	set("long", @LONG
这里一条荒废的道路，其实根本不算路，被马蹄踩得乱七八糟，完全不辨方
向。
LONG
	);

    set("exits", ([
        "east" : __DIR__"huanglu0",   
        "west" : __DIR__"huanglu20",
        "northwest" : __DIR__"huanglu21",
        "southwest" : __DIR__"huanglu22",
        ]));
    set("road_no",62);
    set("huanglu",1);
    set("objects", ([
		
        __DIR__"npc/mes" : 1,
		
	    ]));
	set("outdoors", "jinyang");
	setup();
	
}
