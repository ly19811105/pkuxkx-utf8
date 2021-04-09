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
	set_name("玉灵散", ({"yuling san", "san"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "颗");
		set("long", "这是一颗玉灵散,据说有增长内力的功效，不过内力低的时候服食，反而无益。\n");
		set("value", 30000);
	}
	setup();
}

int do_eat(string arg)
{
        object me = this_player();
 	if (!id(arg))
	return notify_fail("你要吃什么？\n");

	if ( me->query("max_neili") < 200 )
	{
		me->add("max_neili", -1);
		message_vision(HIR "$N吃下一颗玉灵散，只觉得头重脚轻，摇摇欲倒，原来功力不够，药效适得其反！\n" NOR, me);
	}

	else
	{
        me->add("jing", 50);
        me->add("qi", 50);
        me->add("neili", 30);
        me->add("jingli", 5);
        message_vision(HIG "$N吃下一颗玉灵散，只觉得全身舒服了不少!\n" NOR, me);
	}
	
	destruct(this_object());
	return 1;
}