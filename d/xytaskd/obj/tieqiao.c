// 襄阳用的铁锹

#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(YEL "铁锹" NOR, ({ "tie qiao", "qiao" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", HIW"一柄铁锹,用于修筑城防工事(dig)。\n"NOR);
                set("value", 0);
                set("material", "iron");
      }
        setup();
}

void init()
{
	add_action("do_dig","dig");
}

int do_dig()
{
	object me = this_player();
	object tieqiao = this_object();
	object xytask = load_object("/adm/daemons/xytaskd.c");

    if (xytask->query("can_dig") != 1)
		if (xytask->query("victory"))
		{
			tell_object(me,"襄阳保卫战已经胜利了，不要再挖工事了。\n");
			return 1;
		}
		else
		{
			tell_object(me,"蒙古已经发兵，没有时间修筑工事了，赶快参加战斗或者逃难吧！\n");
			return 1;
		}
	if (me->is_busy())
	{
		tell_object(me,"你正忙着呢，修不了工事。\n");
		return 1;
	}
	if (me->query("jing")<20)
	{
	  tell_object(me,"你的精太少，没法修筑工事！\n");
	  return 1;
	}
	if (environment(me)->query("xytaskd/gongshi") >= 5)
	{
		tell_object(me,"这里的工事已经完全修好了，换个地方修吧！\n");
    return 1;
  }
	message_vision("$N抡起铁锹，修筑起工事来！\n",me);
	me->start_busy(20);
	if (this_object()->query_temp("xytaskd/taskid") != xytask->query("taskid"))
	{
		//icer added to avoid gongshi number accumulating
		me->delete_temp("xytaskd/gongshi");
		me->set_temp("xytaskd/taskid",xytask->query("taskid"));
		this_object()->set_temp("xytaskd/taskid",xytask->query("taskid"));
	}
	call_out("dig_done",10,me);
	return 1;
}

int dig_done(object me)
{
	message_vision("$N直起身来，看看已具规模的工事，擦了擦汗，停下来歇一歇。\n",me);
	me->add("jing",-20);
	if (base_name(environment(me))[0..12] == "/d/xiangyang/")
	{
		environment(me)->add("xytaskd/gongshi",1);
		me->add_temp("xytaskd/gongshi",1);
	}
	me->start_busy(0);
	return 1;
}
