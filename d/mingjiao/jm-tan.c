#include <room.h>
inherit ROOM;
void create()
{
        set("short", "巨木坛");
        set("long", @LONG
这里是明教的巨木旗坛，巨木旗旗主正和几个旗众守旗。
LONG
        );
        set("exits", ([
              
                "east"  :__DIR__"damen.c",
        ]));
 set("objects",([
                 
                "/d/mingjiao/npc/jm_zhong.c" : 2,
          CLASS_D("mingjiao")+"/wen" :1
            ]));
set("outroom","明教");
        setup();
      replace_program(ROOM);
}
