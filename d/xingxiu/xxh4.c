// Room: /d/xingxiu/xxh4.c
// Jay 3/18/96

inherit ROOM;
#include "/d/xingxiu/flower.h"
void create()
{
        set("short", "星宿海");
        set("long", @LONG
这里是星宿海边。说是海，其实是片湖泊和沼泽，地形十分险恶。
这里通向星宿海的深处。西面有一条新铺的石头路。
LONG
        );
        set("objects", ([
                __DIR__"npc/haoshou" : 1,
                flower:random(2) ,
        ]) );

        set("exits", ([
             "southeast" : __DIR__"xxh2",
             "northeast" : __DIR__"xxh5",
             "west" : __DIR__"xxh6",
        ]));

        set("no_clean_up", 0);
        set("outdoors", "xingxiuhai");

        setup();
        replace_program(ROOM);

}

