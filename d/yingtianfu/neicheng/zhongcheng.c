//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", "中城");
        set("long", 
"这里是应天府的城中心，两旁的店铺林立，一条笔直的大道通向南城。\n"

        );
        set("exits", ([
                
              
                "north" : __DIR__"gc8",
                "west" : __DIR__"xjk",
                "east" : __DIR__"cyj",
                "south" : __DIR__"z_street1",
                
                
        ]));
        set("objects", ([
                __DIR__"npc/xianhan" : 1,
        ]));
        set("outdoors", "yingtianfu");
        setup();
   
}

