//城门
// By Zine 23 Nov 2010

inherit ROOM;
#include <ansi.h>
#include "zhua.h"
void create()
{
        set("short",BLU"二排三座"NOR);
        set("long", 
"这里是考生的座位，一个考生正在思索着什么。\n"

        );
        set("row",2);
        set("line",3);
        set("exits", ([
                
              
                //"southwest" : __DIR__"qiantai2",
                "west" : __DIR__"qiantai2",
                "east" : __DIR__"r2d",
                "south" : __DIR__"r3c",
                "north" : __DIR__"r1c",
                
        ]));
        
        setup();
   
}

