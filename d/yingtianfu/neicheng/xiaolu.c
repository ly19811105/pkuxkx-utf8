//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", "小路");
        set("long", 
"这里是一条近道，从仪凤门通往军营。\n"

        );
        set("exits", ([
                
                
                
                "southeast" : __DIR__"junying2",
                
                "west" : "/d/yingtianfu/yifeng",
                
                
                
        ]));
        
        set("outdoors", "yingtianfu");
        setup();
   
}

