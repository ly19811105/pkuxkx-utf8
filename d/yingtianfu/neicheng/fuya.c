//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", HIR"应天府"NOR);
        set("long", "这里是应天府的府衙，处理一些民事。\n"

        );
        set("exits", ([
                
                
                "east" : __DIR__"s_street1",
                
                
        ]));
        set("objects", ([
                __DIR__"npc/fuyin" : 1,
        ]));
        set("outdoors", "yingtianfu");
        setup();
   
}

