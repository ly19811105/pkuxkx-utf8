 //entrance.c
//modified from xo
//by zoom
//2003.3.30

#include <ansi.h>

inherit ROOM;

void create()
{
set("short", HIG"北大侠客行接待室"NOR);
set("long", @LONG
欢迎你加入北大侠客行，从这里你将开始闯荡江湖。这里有豪情万丈，也有
柔情脉脉。你可以成为一代大虾，也可以成为无恶不作的大坏蛋，一切都取决于
你自己。快点开始行动吧。
    渴了饿了这里有吃的，输入eat baozi，drink jiudai吃喝点吧。
    
    请输入up往上到新手学堂学习基本指令的使用，并熟悉这里的环境。
    
LONG );
set("no_fight", 1);
set("exits",  ([
        "up"  : __DIR__"train1.c",
        "end"  : __DIR__"exit.c",
        "down" : "/d/city/shangyuetai.c",
      ]));
        set("objects", ([
                __DIR__"npc/advent" : 1,
                "/clone/food/baozi" : 1,
                "/clone/food/dongcaibao" : 1,
                "/clone/food/jitui" : 1,
                "/clone/food/jiudai" : 1,
                "/clone/food/suanmei-tang" : 1,
                
        ]));

        setup();
  //      replace_program(ROOM);
}

int valid_leave(object me, string dir)
{

        if (me->query("combat_exp")<1000)
        {
                if (dir == "down")
                {
                        return notify_fail("请您往上走，学习完新手指南后再闯荡江湖。\n");
                }
        }
        return ::valid_leave(me, dir);
}
