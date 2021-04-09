// Room: /u/kiss/quanzhen/jiaojf.c
// Made by: kiss
// modified by Zine Qz newbiejob
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIW"校经房"NOR);
	set("long", @LONG
这里是藏经阁，靠墙是一排书架，摆满了道教的典籍。中央有一个长方形的
大桌子，上面也堆满了书。几个道童正在整理书籍。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "east" : __DIR__"zoulang10.c",
]));
        set("objects", ([
          __DIR__"npc/daotong1.c" : 2,
          __DIR__"npc/obj/jing.c" : 2,
         ]));
	set("no_clean_up", 0);

	setup();
	
}

void init()
{
    add_action("do_write","write");
}

int writing(object me)
{
    if (!me||!living(me))
    {
        return 1;
    }
    if (me->query_temp("qznewbiejob/task3/write_degree")>7+random(4))
    {
        tell_object(me,"道童交给你的誊抄任务完成了。\n");
        me->delete_temp("qznewbiejob/task3");
        me->set_temp("qznewbiejob/task3/finish",1);
        return 1;
    }
    me->delete_temp("qznewbiejob/task3/writing");
    me->add_temp("qznewbiejob/task3/write_degree",1);
    tell_object(me,"你写完了一页，赶紧再蘸墨继续抄誊。\n");
    return 1;
}

int do_write()
{
    object me=this_player();
    if (me->query_temp("qznewbiejob/task3/type")!="誊写")
    {
        tell_object(me,"你想干嘛？\n");
        return 1;
    }
    if (me->is_busy()||me->is_fighting())
    {
        tell_object(me,"你正忙着呢！\n");
        return 1;
    }
    if (me->query_temp("qznewbiejob/task3/writing"))
    {
        tell_object(me,"你正在誊抄呢！\n");
        return 1;
    }
    message_vision("$N开始誊抄道德经……\n",me);
    me->add_busy(2);
    call_out("writing",2,me);
    me->set_temp("qznewbiejob/task3/writing",1);
    return 1;
}