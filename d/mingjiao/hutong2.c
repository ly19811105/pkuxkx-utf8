//by binlanging.c
//hutong2.c
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "小胡同");
        set("long", @LONG
这是一条小胡同，几个少年正在此玩耍。
LONG
        );
        set("exits", ([
              
                "west"  :__DIR__"hutong.c",
        ]));
 set("objects",([
                 "/d/mingjiao/npc/boy.c" : 2,
                "/d/mingjiao/npc/girl.c" : 1,
            ]));
        setup();
      replace_program(ROOM);
}
