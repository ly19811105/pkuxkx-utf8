//by binlanging.c
//yuan2.c
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "小院");
        set("long", @LONG
这是绿柳山庄的后小院。
这儿香气甚重，你觉得有些不对，赶快离开吧。
LONG
        );
        set("exits", ([
                "south"  :__DIR__"zhengting",
                "west"  :__DIR__"yuan3.c",
                "east"  :__DIR__"yuan1",
/*                  "south"  :__FILE__,
                  "east"  :__FILE__,
                  "west"  :__FILE__,
*/
        ]));
 set("objects",([
                 "/d/mingjiao/npc/hudie.c" : 2,
                 "/d/mingjiao/npc/bee.c"    :2,
            ]));
        set("no_mj_newbie",1);
        setup();
//      replace_program(ROOM);
}
int valid_leave(object me, string dir)
{
 if(me->query("max_neili")<400)
{
        
          write("你感到有些头晕。\n");
      me->add("qi",-40);
      me->add("jing",-40);
 }      
        return ::valid_leave(me, dir);
}
