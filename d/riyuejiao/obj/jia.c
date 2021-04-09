// chai Zine RY newbie job
#include <ansi.h>
inherit ITEM;

void create()
{
	    set_name("兵器架", ({ "bingqi jia","jia", }) );
        set_weight(800);
        set("no_get",1);
        set("long", "这是一个兵器架，上面有日月弟子惯用的刀、剑和甲胄，你可以拿出来。\n");
        set("unit", "个");
        set("value", 0);
		setup();
}

void init()
{
    add_action("do_na","na");
}

int do_na(string arg)
{
    object me=this_player();
    object ob;
    if (me->query("family/family_name")!="日月神教")
    {
        tell_object(me,"神教的东西是你能乱拿的吗？\n");
        return 1;
    }
    if (me->is_busy()||me->is_fighting())
    {
        tell_object(me,"你正忙着呢。\n");
        return 1;
    }
    if (!arg)
    {
        tell_object(me,"你要拿什么？\n");
        return 1;
    }
    if (arg!="jia"&&arg!="jian"&&arg!="dao")
    {
        tell_object(me,"这里只有dao,jian和jia。\n");
        return 1;
    }
    if (arg=="jia")
    {
        ob=new("/d/wizard/npc/obj/armor.c");
        ob->move(me);
        tell_object(me,"你拿起一副甲胄。\n");
    }
    if (arg=="jian")
    {
        ob=new("/d/wizard/npc/obj/sword.c");
        ob->move(me);
        tell_object(me,"你拿起一把"+ob->name()+"。\n");
    }
    if (arg=="dao")
    {
        ob=new("/d/wizard/npc/obj/blade.c");
        ob->move(me);
        tell_object(me,"你拿起一把"+ob->name()+"。\n");
    }
    return 1;
    
}


