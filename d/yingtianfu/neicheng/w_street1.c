//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", "城西大街");
        set("long", 
"这里是应天府的城西面的大街，北面是清凉山，东面是灵英观。\n"

        );
        set("exits", ([
                
              
                "northup" : __DIR__"qls",
                "southeast" : __DIR__"w_street2",
                "west" : "/d/yingtianfu/qingliang",
                "east" : __DIR__"lyg",
                
                
        ]));
        
        set("outdoors", "yingtianfu");
        setup();
   
}

