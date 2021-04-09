//by binlanging.c
//zhenting.c
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "正厅");
        set("long", @LONG
这是绿柳山庄的正厅，前有一匾，匾上横书「绿柳山庄」四个大字，
墙上挂着一幅「八骏图」，甚是高雅。
LONG
        );
        set("exits", ([
               "north" : __DIR__"yuan2.c",
                "south" : __DIR__"xiaoyuan",
                "west"  :__DIR__"xiceting.c",
                "east"  :__DIR__"dongceting.c",
        ]));
 set("objects",([
                 "/d/mingjiao/npc/zhao.c" : 1,
                "/d/mingjiao/npc/qian.c" : 1,
                "/d/mingjiao/npc/sun.c"  :1,
                "/d/mingjiao/npc/li.c"   :1,
            ]));
        set("no_mj_newbie",1);
        setup();
      replace_program(ROOM);
}
