// z-dan.c
// 星星(lywin)炼丹任务附属道具
#include <ansi.h>
inherit ITEM;

void setup()
{}

void init()
{
	add_action("do_eat", "eat");
}

void create()
{
	set_name("黄连解毒丸", ({"ndan1", "dan1"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "颗");
		set("long", "这是一颗黄连解毒丸。\n");
		set("value", 8000);
	}
	setup();
}

int do_eat(string arg)
{
        object me = this_player();
 	if (!id(arg))
	return notify_fail("你要吃什么？\n");

	me->apply_condition("snake_poison", 0);
        me->apply_condition("bt_poison", 0);
        me->apply_condition("xx_poison", 0);
        me->set("neili", 200);
        message_vision(HIG "$N吃下一颗黄连解毒丸，只觉得体内的毒素全部随真气流了出去!\n" NOR, me);
	
	destruct(this_object());
	return 1;
}