//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", "广场东北");
        set("long", 
"这里是应天府广场的东北角，人来人往，热闹非常。\n"

        );
        set("exits", ([
                
                "west" : __DIR__"gc2",
                "south" : __DIR__"gc6",
                
                
        ]));
        
        set("outdoors", "yingtianfu");
        setup();
   
}

