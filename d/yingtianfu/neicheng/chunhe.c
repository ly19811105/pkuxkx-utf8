//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", MAG"春和宫"NOR);
        set("long", 
"这里春和宫，皇帝的后宫，很多嫔妃居住在此。\n"

        );
        set("exits", ([
                
              
                
                
                "east" : __DIR__"jiaotai",
                
                
                
        ]));
        
        
        setup();
   
}

