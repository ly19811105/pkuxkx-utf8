#include <ansi.h>
inherit __DIR__"yanmenguan.c";

void create()
{
	set("short", "水底暗流");
	set("long", @LONG
这里是水底的潜流，力量极大，让人根本不辨方向。
LONG
	);

    set("road_no",100);
    set("objects", ([
		
        __DIR__"npc/mes" : 1,
		
	    ]));
	setup();
	
}



