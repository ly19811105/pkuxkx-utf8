//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", "下街口");
        set("long", 
"这里是下街口，西面是朝天宫，东面通向中城。\n"

        );
        set("exits", ([
                
              
                "west" : __DIR__"ctg",
                "east" : __DIR__"zhongcheng",
                "south" : __DIR__"dangpu",
                "north" : __DIR__"qianzhuang",
                
                
        ]));
        
        set("outdoors", "yingtianfu");
        setup();
   
}

