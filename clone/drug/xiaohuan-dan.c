//Cracked by Roath
// xiaohuan-dan.c 小还丹

#include <ansi.h>

inherit ITEM;

void setup()
{}
int cure_ob(string);
void init()
{
	add_action("do_put", "put");
}

void create()
{
	set_name("小还丹", ({"xiaohuan dan", "xiaohuan", "dan"}));
	set_weight(10);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "颗");
		set("long", "这是一颗莹白溜圆的小还丹。此丹乃少林奇药，助长内力，灵效无比。\n");
		set("value", 5000);
		set("medicine", 1);
		set("no_drop", "这样东西不能离开你。\n");
	}

	set("shaolin",1);
	setup();
}

int cure_ob(object me)
{
	if ( me->query("neili") >= me->query("max_neili")*2 )
	return notify_fail("你现在没必要吃小还丹。\n");

	if ( me->query_skill_mapped("force") != "hunyuan-yiqi" )
	{
		me->set("neili", 0);
		message_vision(HIR "$N吃下一颗小还丹，只觉得五脏欲裂，原来所练内功不符，反而大损修为！\n" NOR, me);
		me->unconcious();
		destruct(this_object());
		return 1;
	}

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

	destruct(this_object());
	return 1;
}

int do_put(string arg1, string arg2, string arg3)
{
	if( present(arg1, this_player()) == this_object() ) return 1;

	return 0;
}

