//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", "北门桥");
        set("long", 
"这里是应天府北门附近的一座石桥，往北通向北城，过了桥往南是一片大广场。\n"

        );
        set("exits", ([
                
                
                
                "northwest" : __DIR__"beicheng",
                "south" : __DIR__"gc2",
                
                
        ]));
        
        set("outdoors", "yingtianfu");
        setup();
   
}

