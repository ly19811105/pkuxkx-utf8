//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", "镇淮桥");
        set("long", 
"这座石桥名唤镇淮桥，南面是聚宝门，往北通向南城。\n"

        );
        set("exits", ([
                
              
                "north" : __DIR__"s_street2",
                "south" : "/d/yingtianfu/jubao",
                "west" : __DIR__"xing-prison",
                
                
        ]));
        
        set("outdoors", "yingtianfu");
        setup();
   
}

