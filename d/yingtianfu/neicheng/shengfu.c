//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", "圣府");
        set("long", 
"这里是供奉孔子的圣府，北面不远就是贡院了。\n"

        );
        set("exits", ([
                
              
                "west" : __DIR__"dazhongjie",
                "north" : __DIR__"gongyuan",
                "east" : __DIR__"huaiqingqiao",
                
                
        ]));
        
        set("outdoors", "yingtianfu");
        setup();
   
}

