//by binlanging.c
//yuan1.c
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "小院");
        set("long", @LONG
这是绿柳山庄的后小院，院内花草繁茂，香气袭人。
LONG
        );
        set("exits", ([
                "south"  :__DIR__"dongceting",
                "west"  :__DIR__"yuan2.c",
        ]));
 set("objects",([
                 "/d/mingjiao/npc/hudie.c" : 2,
              
                
            ]));
        set("no_mj_newbie",1);
        setup();
      replace_program(ROOM);
}

