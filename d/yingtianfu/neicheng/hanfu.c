//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", "汉府故地");
        set("long", 
"。\n"

        );
        set("exits", ([
                
              
                
                
                "south" : __DIR__"street",
                
                
                
        ]));
        
        set("outdoors", "yingtianfu");
        setup();
   
}

