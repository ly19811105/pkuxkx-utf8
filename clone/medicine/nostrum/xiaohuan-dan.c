// xiaohuan-dan.c 小还丹

#include <ansi.h>

inherit ITEM;

void setup()
{}

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(HIW"小还丹"NOR, ({"xiaohuan dan", "xiaohuan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "颗");
		set("vegetable", 46);
		set("nostrum", 78);
		set("level", 60);
		set("long","这是一颗莹白溜圆的小还丹。此丹乃少林奇药，助长内力，灵效无比。\n");
		set("value", 10000);
		set("no_drop", "这样东西不能离开你。\n");
	}
	set("pour_type", "1");

	set("shaolin",1);
	setup();
}

int do_eat(string arg)
{
	object me = this_player();

	if(!id(arg)) return notify_fail("你要吃什么？\n");
	if(!present(this_object(), me))
		return notify_fail("你要吃什么？\n");
	if( me->is_busy() )
		return notify_fail("别急，慢慢吃，小心别噎着了。\n");

	if( me->query("neili") >= me->query("max_neili")*2 )
		return notify_fail("你现在没必要吃小还丹。\n");
	me->start_busy(2);
	if( me->query_skill_mapped("force") != "hunyuan-yiqi" &&
		me->query_skill_mapped("force") != "zhanzhuang-gong" )
	{
		me->set("neili", 0);
		message_vision(HIR "$N吃下一颗小还丹，只觉得五脏欲裂，原来所练内功不符，反而大损修为！\n" NOR, me);
//		me->unconcious();
		me->start_busy(10);
	}
	else
	{
		if ( (int)me->query_condition("bonze_drug" ) > 0 )
		{
			me->add("neili", -200);
			message_vision(HIR "$N吃下一颗小还丹，只觉得头重脚轻，摇摇欲倒，原来服食太急太多，药效适得其反！\n" NOR, me);
		}
		else
		{
			me->add("neili", 200);
			message_vision(HIY "$N吃下一颗小还丹，只觉得身轻如燕，四肢百骸真气充盈无比，几欲奔腾而出！\n" NOR, me);
		}
		me->apply_condition("bonze_drug", 30);
	}
	destruct(this_object());
	return 1;
}
