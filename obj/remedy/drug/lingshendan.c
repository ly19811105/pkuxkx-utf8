#include <ansi.h>
inherit COMBINED_ITEM;
#include "eat.h"
void create()
{
        set_name(HIB"上品灵参丹"NOR, ({"shangpin lingshendan", "dan"}));
        set_weight(300+random(60));
        set("long", "这是一粒上品灵参丹，能够快速补充真元。\n");
        set("unit", "粒");
		set("value",1000);
		set_amount(1);
		setup();
}
int do_eat(string arg)
{
	int diff=3000;
	object me=this_player(),ob=this_object();
	if (!can_eat(ob,arg)) return 0;
	if (me->is_busy())
	{
		tell_object(me,"你忙着呢，根本腾不开手。\n");
		return 1;
	}                 
	if (base_name(environment(me))[0..10] == "/d/xiakedao")
	return notify_fail("什么？\n");  
	if (time()-me->query_temp("last_eat_renshenwan")<40)
	{
		tell_object(me,"等等，你上次吃的参王效果还没有完全发挥呢。\n");
		return 1;
	}
	if (me->query("neili")>me->query("max_neili")*3)
	{
		tell_object(me,"你现在的状态恐怕无法通过外力再获得内力提升了。\n");
		return 1;
	}
	me->set_temp("last_eat_renshenwan",time());
	if (me->query("max_neili")<3000) diff=me->query("max_neili");
	me->add("neili", diff*9/10+random(diff/10));   
	message_vision("$N服下一粒$n，经脉各处内息充盈多了。\n", me, this_object());
	if(query_amount()<=1)
	{
		write("你把剩下的"+name()+"都吃完了。\n");
	}
	add_amount(-1);
	return 1;
}


