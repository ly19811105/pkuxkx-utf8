//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", "大中街");
        set("long", 
"这里是大中街，东面通向孔圣人的圣府，西面通往南城。\n"

        );
        set("exits", ([
                
              
                "west" : __DIR__"s_street2",
                "east" : __DIR__"shengfu",
                
                
        ]));
        
        set("outdoors", "yingtianfu");
        setup();
   
}

