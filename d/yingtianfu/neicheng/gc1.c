//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", "广场西北");
        set("long", 
"这里是应天府广场的西北角，人来人往，热闹非常。\n"

        );
        set("exits", ([
                
                "east" : __DIR__"gc2",
                "south" : __DIR__"gc4",
                
                
        ]));
        
        set("outdoors", "yingtianfu");
        setup();
   
}

