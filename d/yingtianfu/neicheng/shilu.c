//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", HIW"石路"NOR);
        set("long", 
"这里是一条石路，东北面通往太平门，南面通向皇城。\n"

        );
        set("exits", ([
                
              
                
                "northwest" : "/d/yingtianfu/taiping",
                "south" : __DIR__"beianmen",
                
                
                
        ]));
        
        set("outdoors", "yingtianfu");
        setup();
   
}

