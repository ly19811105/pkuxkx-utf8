// /d/xingxiu/silk4.c
// Jay 3/17/96

inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "丝绸之路");
          set("long", @LONG
这是一条中原和西域之间的商道。西面是一望无际的大沙漠，
传说那里常有盗匪出没。西北是赫赫有名的嘉峪关了，东面就是
通向黄河。路边有一块石碑(shibei)。
LONG );
        set("outdoors", "silk");

        set("exits", ([
                "east" : __DIR__"silk3",
                "northwest" : __DIR__"jiayuguan",
        ]));

        set("item_desc", ([
                "shibei" : "北至西域，东达中原。谁若西行，格杀勿论。白驼山主人启。\n",
                "石碑" : "北至西域，东达中原。谁若西行，格杀勿论。白驼山主人启。\n",
        ]));

        setup();
}

void init()
{
       /* add_action("do_push", "push");
        add_action("do_push", "tui");*/
}

/*int valid_leave(object me, string dir)
{
//暂时用一下
                object camel;
        if( dir=="west"&& (int)me->query("combat_exp")<3000000 && userp(me) && (!objectp(camel = me -> query_temp("riding"))

            || camel->name() != HIW"白骆驼"NOR ) )
    return notify_fail(HIR"你没有骑骆驼，去沙漠太危险了！\n"NOR);
    return ::valid_leave(me, dir);
}*/

int do_push(string arg)
{
        object me;
        mapping fam;

        me = this_player();

        if( !arg || arg=="" ) return 0;

        if( arg=="shibei" || arg=="石碑")
        {
                if( (fam = me->query("family")) && fam["family_name"] == "丐帮" ) 
                {
                        message_vision("$N推开石碑，只见泥沙纷纷跌落，地面上露出一个小洞。\n", me);
                        message("vision",
                                me->name() + "运起丐帮缩骨功，一弯腰往洞里钻了进去。\n",
                                environment(me), ({me}) );
                        me->move("/d/gaibang/underxx");
                        message("vision",
                                me->name() + "从洞里走了进来。\n",
                                environment(me), ({me}) );
                        return 1;
                }
                else 
                        return notify_fail("这么小的洞，你钻得进去吗？\n");
        }
}       

