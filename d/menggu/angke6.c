inherit ROOM; 
#include <ansi.h>
#include "angke.h"
void create() 
{ 
        set("short", "昂可刺河南岸");
        set("long", @LONG
这里是昂可刺河的南岸，河水流向大泽。
LONG
        );
	
        set("exits", ([ "northeast" : __DIR__"daze0",
                        //"southwest" : __DIR__"zaoze1",
                        "west" : __DIR__"angke5",
                        //"east" : __DIR__"angke6",
                        "north" : __DIR__"xiboliya",
]));
        set("outdoors", "menggu_n");
		setup();
}
