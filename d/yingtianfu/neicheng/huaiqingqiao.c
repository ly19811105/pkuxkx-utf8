//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", "淮清桥");
        set("long", 
"这里是淮清桥，连接着通济门和城内。\n"

        );
        set("exits", ([
                
              
                "west" : __DIR__"shengfu",
                "east" : "/d/yingtianfu/tongji",
                
                
        ]));
        
        set("outdoors", "yingtianfu");
        setup();
   
}

