// Room: /u/hacky/quanzhen/yaopu.c
// Made by: hacky
// modified by Zine qZ NEWBIE JOB
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "药圃");
	set("long", @LONG
药圃内种着许多罕见的奇药，一位老者正在这里精心照看这些草药。
LONG
	);
	set("exits", ([ /* sizeof() == 3 */
  "west" : __DIR__"mingmu.c",
  "south" : __DIR__"zoulang18.c",
  "north" : "/d/gumu/xiaodao.c",
  "east" : __DIR__"guoyuan.c",
]));
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/laozhe.c" : 1,
]));
	set("no_clean_up", 0);

	setup();
}

void init()
{
    add_action("do_zai","zai");
    add_action("do_shou","shouqi");
}

int do_shou()
{
    object me=this_player();
    object yao;
    int i,count=0;
    object *all;
    if (me->query_temp("qznewbiejob/task2/type")!="收药")
    {
        tell_object(me,"没有得到同意，别乱动别人的东西。\n");
        return 1;
    }
    if (me->is_busy())
    {
        tell_object(me,"你正忙着呢。\n");
        return 1;
    }
    me->add_busy(2);
    message_vision("$N开始精心挑选这里的药草。\n",me);
    if (random(10)>3)
    {
        yao=new(__DIR__"npc/obj/yaocao");
        yao->move(me);
        tell_object(me,"这株可以入药，你把它放入自己的背包。\n");
        me->add_temp("qznewbiejob/task2/shouyao",1);
    }
    else
    {
        tell_object(me,"这株完全烂掉了，你把它扔在一边。\n");
    }
    all=all_inventory(me);
    for (i=0;i<sizeof(all);i++)
    {
        if (all[i]->query("qz_yaocao"))
        {
            count=count+1;
        }
    }
    if (count>=10)
    {
        for (i=0;i<sizeof(all);i++)
        {
            if (all[i]->query("qz_yaocao"))
            {
                destruct(all[i]);
            }
        }
        tell_object(me,HIM"你凑齐十株药材，全部交给了老者。\n"NOR);
        me->delete_temp("qznewbiejob/task2");
        me->set_temp("qznewbiejob/task2/finish",1);
    }
    return 1;
}

int do_zai()
{
    object me=this_player();
    object yao;
    if (me->query_temp("qznewbiejob/task2/type")!="移栽")
    {
        tell_object(me,"没有得到同意，别乱动别人的东西。\n");
        return 1;
    }
    if (me->is_busy())
    {
        tell_object(me,"你正忙着呢。\n");
        return 1;
    }
    if (!present("yao cao",me))
    {
        tell_object(me,"你什么没有可移栽的药草。\n");
        return 1;
    }
    yao=present("yao cao",me);
    if (!yao->query("qz_yaocao"))
    {
        tell_object(me,"你没有可移栽的药草。\n");
        return 1;
    }
    if (yao->query("owner")!=me->query("id"))
    {
        tell_object(me,"你的药草已经枯死了。\n");
        return 1;
    }
    me->add_busy(2);
    message_vision("$N开始悉心移栽药草。\n",me);
    if (random(10)>3)
    {
        destruct(yao);
        tell_object(me,"药草被移栽到这里，终于成活了。\n");
        me->delete_temp("qznewbiejob/task2");
        me->set_temp("qznewbiejob/task2/finish",1);
        return 1;
    }
    else
    {
        tell_object(me,"土壤有些松动，移栽并未成功。\n");
        return 1;
    }
}