//凉亭
//by icer
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "桃源驿站");        set("long", @LONG
这里是通往桃源县境的一个凉亭。过往行人大都在这儿休息。
LONG
);
set("exits", ([
//                "east" : __DIR__"road3",
                "east" : __DIR__"road2",
           
            "northeast" : "/d/yueyang/shanlu",
            "southwest":"/d/jiaofei/road1.c",                
]));
    
set("objects",([
      __DIR__"npc/bangzhong" : 3,
      __DIR__"npc/qiu"	     : 1,
     ]));

set("outdoors", "taoyuan");
setup();
}

