//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", "内桥");
        set("long", 
"这是一座石桥，连着这南城和中城。\n"

        );
        set("exits", ([
                
              
                "north" : __DIR__"z_street2",
                "south" : __DIR__"s_street1",
                
                
        ]));
        
        set("outdoors", "yingtianfu");
        setup();
   
}

