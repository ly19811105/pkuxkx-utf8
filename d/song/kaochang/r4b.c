//城门
// By Zine 23 Nov 2010

inherit ROOM;
#include <ansi.h>
#include "zhua.h"
void create()
{
        set("short",RED"四排二座"NOR);
        set("long", 
"这里是考生的座位，一个考生正在思索着什么。\n"

        );
        set("row",4);
        set("line",2);
        set("exits", ([
                
              
                "northeast" : __DIR__"qiantai1",
                //"west" : __DIR__"qiantai1",
                "west" : __DIR__"r4a",
                "east" : __DIR__"r4c",
                "north" : __DIR__"r3b",
                
        ]));
        
        setup();
   
}

