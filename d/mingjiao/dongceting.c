//by binlanging.c
//dongceting.c
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "东侧厅");
        set("long", @LONG
这是绿柳山庄的东侧厅，室内放着几张非常古朴的桌子椅子。
   另有两个弟兄在此
LONG
        );
        set("exits", ([
                "north"  :__DIR__"yuan1",
                "west"  :__DIR__"zhengting.c",
        ]));
 set("objects",([
                 "/d/mingjiao/npc/wu.c" : 1,
                "/d/mingjiao/npc/zhou.c" : 1,
                
            ]));
        set("no_mj_newbie",1);
        setup();
      replace_program(ROOM);
}
