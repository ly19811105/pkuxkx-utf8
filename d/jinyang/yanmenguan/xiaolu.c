#include <ansi.h>
inherit __DIR__"yanmenguan.c";

void create()
{
	set("short", YEL"泥泞小路"NOR);
	set("long", @LONG
这是一条泥泞的土路，深一脚浅一脚的走得极为困难，前方是一片密林。不
远处却是一道河流的拐弯。
LONG
	);

    set("exits", ([
        "north" : __DIR__"tulu",        
        "southwest" : __DIR__"milin",
        ]));
    set("road_no",4);
    set("objects", ([
		
        __DIR__"npc/mes" : 1,
		
	    ]));
	set("outdoors", "jinyang");
	setup();
	
}



