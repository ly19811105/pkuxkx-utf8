// by binlangc
// tolvliu2.c
#include <room.h>
inherit ROOM;
void create()
{
       set("short","绿柳山庄小路");
       set("long", @LONG
这是一条通往绿柳山庄的小路。
这儿虽然尚不繁华，但已是有人烟的地方了，
路旁有花有草，中间还有一口井。
东边是一条小路，南边就是绿柳山庄了。
LONG
     );
        set("outdoors", "mingjiao");
        set("exits", ([
                "east" : __DIR__"tolvliu1",
                "southeast" : __DIR__"lvliu1",
// more direction here
        ]));
        set("resource/water",1);
        set("objects",([
                __DIR__"npc/dog.c" :1,
                
        ]));
        setup();
        replace_program(ROOM);
}
