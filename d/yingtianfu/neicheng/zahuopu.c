// Zine Nov 26 2010
inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", "杂货铺");
        set("long", "这里是应天府的一家杂货铺。\n");
        set("exits", ([
               
               
               "south" : __DIR__"cyj",
               
               
                
        ]));
        set("objects", ([
		__DIR__"npc/xiaofan2" : 1,
        ]));
        
        setup();
   
}

