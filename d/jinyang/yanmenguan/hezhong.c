#include <ansi.h>
inherit __DIR__"yanmenguan.c";

void create()
{
	set("short", HIW"河中"NOR);
	set("long", @LONG
这里是大河之中，水流湍急，不注意就会被水流冲走。
LONG
	);

    
    set("road_no",16);
   set("objects", ([
		
        __DIR__"npc/mes" : 1,
		
	    ]));
	set("outdoors", "jinyang");
	setup();
	
}



