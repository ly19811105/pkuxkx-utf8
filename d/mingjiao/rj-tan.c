#include <room.h>
inherit ROOM;
void create()
{
        set("short", "锐金坛");
        set("long", @LONG
这里是明教的锐金旗坛，锐金旗主正和几个旗众守旗。
LONG
        );
        set("exits", ([
              
                "north"  :__DIR__"damen.c",
        ]));
 set("objects",([
                 
                "/d/mingjiao/npc/rj_zhong.c" : 2,
          CLASS_D("mingjiao")+"/zhuang" :1
            ]));
set("outdoors","明教");
        setup();
      replace_program(ROOM);
}
