//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", HIY"贡院"NOR);
        set("long", 
"这里是贡院。\n"

        );
        set("exits", ([
                
              
                
                "south" : __DIR__"shengfu",
                "enter" : __DIR__"kaochang/qianyuan"
                
        ]));
        
        set("outdoors", "yingtianfu");
        setup();
   
}

