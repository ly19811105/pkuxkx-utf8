//城墙 /d/jinyang/citywall
// By Zine 23 Nov 2010

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "城墙");
        set("long", 
"这里一段雄奇的古城墙。\n"

        );
        set("exits", ([
                
                "northeast" : __DIR__"chaoximen",
                "southwest" : __DIR__"citywall4"
                //"north" :
                
        ]));
        
        set("outdoors", "jinyang");
        setup();
   
}


