//城墙 /d/jinyang/citywall
// By Zine 23 Nov 2010

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "城墙脚下");
        set("long", 
"这里一段雄奇的古城墙，城砖仿佛在倾诉血与火的岁月。\n"

        );
        set("exits", ([
                
                "north" : __DIR__"citywall8",
                "south" : __DIR__"chaoyang"
                //"north" :
                
        ]));
        
        set("outdoors", "yingtianfu");
        setup();
   
}


