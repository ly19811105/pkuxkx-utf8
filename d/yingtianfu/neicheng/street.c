//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", CYN"青石路"NOR);
        set("long", 
"这里一条青石路，西面是东广场，东面通往纵星桥。\n"

        );
        set("exits", ([
                
              
                
                "west" : __DIR__"gc6",
                "north" : __DIR__"hanfu",
                "east" : __DIR__"zongxingqiao",
                
                
                
        ]));
        
        set("outdoors", "yingtianfu");
        setup();
   
}

