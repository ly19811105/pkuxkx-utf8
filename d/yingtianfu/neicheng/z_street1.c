//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", "长街");
        set("long", 
"一条长长的大街，两旁是民居和店铺。\n"

        );
        set("exits", ([
                
              
                "north" : __DIR__"zhongcheng",
                "south" : __DIR__"z_street2",
                
                
        ]));
        
        set("outdoors", "yingtianfu");
        setup();
   
}

