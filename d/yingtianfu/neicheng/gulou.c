//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", "鼓楼");
        set("long", 
"这里是应天府的鼓楼。一个小厮一直在这里负责打扫。\n"

        );
        set("exits", ([
                
                
                
                "northwest" : __DIR__"beicheng",
                "south" : __DIR__"beimenqiao",
                
                
        ]));
        set("objects", ([
                __DIR__"npc/xiaosi" : 1,
        ]));
        set("outdoors", "yingtianfu");
        setup();
   
}

