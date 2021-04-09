//Cracked by Roath
// renshen-guo.c 人参果

#include <ansi.h>

inherit ITEM;

int do_eat(string);
void init();

void init()
{
        if (!wizardp(this_player())) {
	}

	add_action("do_eat", "eat");
}

void create()
{
	set_name(HIG "人参果" NOR, ({"renshen guo", "guo"}));
	set_weight(20);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "枚");
		set("long", "这是一枚人参果，看上去就像一个白白胖胖的小娃娃。\n");
		set("value", 1000);
	}

	setup();
}

int do_eat(string arg)
{
	object me = this_player();

	if (!id(arg))
		return notify_fail("你要吃什么？\n");
	if (base_name(environment(me))[0..7] != "/d/bwdh/")
		return notify_fail("人参果不能在外面吃！\n");
	me->set("eff_jing", (int)me->query("max_jing"));
	me->set("jing", (int)me->query("max_jing"));
	me->set("eff_qi", (int)me->query("max_qi"));
	me->set("qi", (int)me->query("max_qi"));
	me->set("jingli", (int)me->query("max_jingli"));
	me->set("neili", (int)me->query("max_neili"));
	me->set("food", (int)me->max_food_capacity());
        me->set("water", (int)me->max_water_capacity());
        
	message_vision(HIG "$N吃下一枚人参果，只觉得精神健旺，气血充盈，体内真力源源滋生，甚至不再感到饥饿干渴! \n" NOR, me);

	destruct(this_object());
	return 1;
}
