//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", "里仁街");
        set("long", 
"这里是里仁街，西面通往中城，。\n"

        );
        set("exits", ([
                
              
                
                "west" : __DIR__"cyj",
               // "east" : __DIR__"lrj",
                "southeast" : __DIR__"dazhongqiao",
                "northeast" : __DIR__"zongxingqiao",
                
                
        ]));
        
        set("outdoors", "yingtianfu");
        setup();
   
}

