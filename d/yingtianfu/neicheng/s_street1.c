//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", "南大街");
        set("long", 
"这里是应天府的南大街，西面是应天府衙门，东面是一处寺庙。\n"

        );
        set("exits", ([
                
                "west" : __DIR__"fuya",
                "east" : __DIR__"chengensi",
                "north" : __DIR__"neiqiao",
                "south" : __DIR__"s_street2",
                
                
        ]));
        
        set("outdoors", "yingtianfu");
        setup();
   
}

