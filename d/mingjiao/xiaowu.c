//by binlanging.c
//xiaowu.c
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "小破屋");
        set("long", @LONG
这是一间小破屋，房内穷的几乎什么都没有，也倒显的干净。
LONG
        );
        set("exits", ([
              
                "north"  :__DIR__"hutong.c",
        ]));
 set("objects",([
                 
                "/d/mingjiao/npc/poorman.c" : 1,
            ]));
        setup();
      replace_program(ROOM);
}
