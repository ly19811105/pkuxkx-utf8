//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", GRN"清凉寺"NOR);
        set("long", 
"这里清凉寺，庙里有个老方丈帮人算命。\n"

        );
        set("exits", ([
                
              
                "out" : __DIR__"qls",
                
        ]));
        
        set("objects", ([
                __DIR__"npc/monk" : 1,
        ]));
        setup();
   
}

