#include <ansi.h>
inherit __DIR__"yanmenguan.c";

void create()
{
	set("short", HIR"大辽军营"NOR);
	set("long", @LONG
这里大辽的军营，军容齐整，不容侵犯。
LONG
	);

    set("exits", ([
        "eastdown" : __DIR__"tulu2",   
        "out" : "/d/jinyang/yanmenguan",
        ]));
    set("road_no",19);
    set("objects", ([
		
        __DIR__"npc/weishi" : 2,
        __DIR__"npc/mes" : 1,
		
	    ]));
	set("outdoors", "jinyang");
	setup();
	
}



