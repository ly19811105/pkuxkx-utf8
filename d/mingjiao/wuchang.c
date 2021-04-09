// wuchang.c
// by airy
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "武场");
        set("long", @LONG
这是鹰王宫前的武场。鹰王殷天正年纪虽然不小了，但是武功却从
没停过，这是他练武的广场。他的几个弟子正在互相比划喂招。一块巨
大的石头非金非铁，可以用打磨(mo)刀剑。
LONG
        );
        set("exits", ([
               "north" : __DIR__"ywgong.c",
                "south" : __DIR__"suishilu3",
        ]));
        create_door("north", "宫门", "south", DOOR_CLOSED);
 set("outdoors", "mingjiao");
 set("objects",([
__DIR__"obj/jiguanren" :1,
]));
        setup();
      //replace_program(ROOM);
}

void init()
{
    add_action("do_mo","mo");
}

int do_mo()
{
    object me=this_player();
    object *all;
    int i;
    if (me->query_temp("mingjiao/tasks/taskno")!=2)
    {
        tell_object(me,"没有鹰王手令，不得擅自领取兵器。\n");
        return 1;
    }
    if (me->is_busy()||me->is_fighting())
    {
        tell_object(me,"你正忙着呢。\n");
        return 1;
    }
    else
    {
        all=all_inventory(me);
        for (i=0;i<sizeof(all);i++)
        {
            if (all[i]->query("mingjiaoquest")==1)
            {
                all[i]->set("moed",1);
                tell_object(me,"你使劲打磨"+all[i]->query("name")+"。\n");
            }
            if (all[i]->query("mingjiaoquest")==2)
            {
                all[i]->set("moed",1);
                tell_object(me,"你使劲打磨"+all[i]->query("name")+"。\n");
            }
            else
            {
                continue;
            }
        }
        return 1;
    }
}
