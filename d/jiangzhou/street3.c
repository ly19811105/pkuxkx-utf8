// Zine Nov 26 2010
inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "甘棠路");
        set("long", "这里是江州的主干道——甘棠路，不过确是东北西南走向。\n");
        set("exits", ([
               "northeast" : __DIR__"guangchang",
               "north" : __DIR__"gantanghu",
               "southwest" : __DIR__"street4",
               "south" : __DIR__"dangpu",
               
                
        ]));
        /*set("objects", ([
		"/d/city/npc/wujiang1"+random(2) : 1,
        "/d/city/npc/bing" : 2,
        ]));*/
        set("outdoors", "jiangzhou");
        setup();
   
}

