//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", "纵星桥");
        set("long", 
"这里应天府通往皇城的一座石桥，驻有重兵。\n"

        );
        set("exits", ([
                
              
                
                "west" : __DIR__"street",
                "southwest" : __DIR__"lrj",
                "east" : __DIR__"xianmen",
                
                
                
        ]));
        
        set("outdoors", "yingtianfu");
        setup();
   
}

