

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", GRN"奇草"NOR);
set("outdoors","quanzhen");
	set("long", @LONG
奇草里有种满了各种各样的珍奇植物，这些都是全真七子云游四方时带回来
的，现在都种在这里，一位道长正在这里细心的照料这些奇草。地上放着几个木
桶。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"guoyuan.c",
  "east" : __DIR__"fanghua.c",
  "north" : __DIR__"shuitang",
]));
	set("no_clean_up", 0);
    set("objects", ([ 
        __DIR__"npc/obj/tong1" : 2,
        __DIR__"npc/obj/tong2" : 2,
]));
	setup();
	
}

int valid_leave(object me,string dir)
{
    if ((present("shui tong",me)||present("fen tong",me))&&(dir=="west"||dir=="east"))
    {
        return notify_fail("你把桶带走了，别人怎么照看园子？\n");
    }
    return ::valid_leave(me,dir);
}



void init()
{
    object me=this_player();
    add_action("do_get","get");
    add_action("do_wa","wa");
    add_action("do_jiao","jiao");
    add_action("do_shifei","shifei");
}

int do_shifei()
{
    object me=this_player();
    object tong;
    if (me->query_temp("qznewbiejob/task2/type")!="施肥")
    {
        tell_object(me,"没有得到同意，最好什么也别做。\n");
        return 1;
    }
    if (me->is_busy())
    {
        tell_object(me,"你正忙着呢。\n");
        return 1;
    }
    if (!present("fen tong",me))
    {
        tell_object(me,"你的肥在哪？难道你要自己拉？容量也不够啊！\n");
        return 1;
    }
    tong=present("fen tong",me);
    if (tong->query("is_tong")!=2)
    {
        tell_object(me,"你的粪桶不太对劲啊。\n");
        return 1;
    }
    if (!tong->query("full"))
    {
        tell_object(me,"你的肥在哪？快去粪坑舀(yao)点过来吧。\n");
        return 1;
    }
    tong->set("full",0);
    message_vision("$N把一桶粪均匀地撒在地里。\n",me);
    me->add_busy(2);
    tell_object(me,"施肥任务完成了！\n");
    me->delete_temp("qznewbiejob/task2");
    me->set_temp("qznewbiejob/task2/finish",1);
    return 1;
}

int do_jiao()
{
    object me=this_player();
    object tong;
    if (me->query_temp("qznewbiejob/task2/type")!="浇水")
    {
        tell_object(me,"没有得到同意，最好什么也别做。\n");
        return 1;
    }
    if (me->is_busy())
    {
        tell_object(me,"你正忙着呢。\n");
        return 1;
    }
    if (!present("shui tong",me))
    {
        tell_object(me,"你的水在哪？怎么浇啊？\n");
        return 1;
    }
    tong=present("shui tong",me);
    if (tong->query("is_tong")!=1)
    {
        tell_object(me,"你的水在哪？怎么浇啊？\n");
        return 1;
    }
    if (!tong->query("full"))
    {
        tell_object(me,"桶里无水，浇什么浇？\n");
        return 1;
    }
    tong->set("full",0);
    message_vision("$N举起一桶水均匀地浇在地里。\n",me);
    me->add_busy(2);
    tell_object(me,"浇水任务完成了！\n");
    me->delete_temp("qznewbiejob/task2");
    me->set_temp("qznewbiejob/task2/finish",1);
    return 1;
}

int do_wa()
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
    message_vision("$N在地里翻找着什么。\n",me);
    me->add_busy(2+random(2));
    if (random(100)>60)
    {
        yao=new(__DIR__"npc/obj/yaocao");
        yao->set("owner",me->query("id"));
        yao->move(me);
        tell_object(me,"你挖出了一棵完整的药草。\n");
        return 1;
    }
    else
    {
        tell_object(me,"你不小心把挖出的药草根茎都弄伤，不能要了。\n");
        return 1;
    }
}

int do_get(string arg)
{
    object me=this_player();
    if (!arg)
    {
        tell_object(me,"你要拿什么？\n");
        return 1;
    }
    if (arg=="all")
    {
        tell_object(me,"你一下拿得起来吗？\n");
        return 1;
    }
    if (arg=="shui tong"||arg=="fen tong")
    {
        if (present("shui tong",me))
        {
            tell_object(me,"你身上不是有个水桶吗？\n");
            return 1;
        }
        if (present("fen tong",me))
        {
            tell_object(me,"你身上不是有个粪桶吗？\n");
            return 1;
        }
    }
}