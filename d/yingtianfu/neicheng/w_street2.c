//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", "城西大街");
        set("long", 
"这里是应天府的城西面的大街，北面是灵英观，东面通向朝天宫。\n"

        );
        set("exits", ([
                
              
                "northwest" : __DIR__"w_street1",
                "north" : __DIR__"lyg",
                "east" : __DIR__"ctg",
                "west" : "/d/yingtianfu/shicheng",
                
                
        ]));
        
        set("outdoors", "yingtianfu");
        setup();
   
}

