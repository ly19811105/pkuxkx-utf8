#include <ansi.h>
inherit __DIR__"yanmenguan.c";

void create()
{
	set("short", "河边");
	set("long", @LONG
这里是黄河支流的北岸，西面是一条土路。
LONG
	);

    set("exits", ([
        "south" : __DIR__"hezhong",   
        "west" : __DIR__"tulu2",
        ]));
    set("road_no",17);
    set("objects", ([
		
        __DIR__"npc/mes" : 1,
		
	    ]));
	set("outdoors", "jinyang");
	setup();
	
}



