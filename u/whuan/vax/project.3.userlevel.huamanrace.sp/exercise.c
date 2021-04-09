// exercise.c

#include <skill.h>


int exercising(object me);
//int halt_exercise(object me, object who, string why);
int halt_exercise(object me, object who, string how);

int main(object me, string arg)
{
	int exercise_cost;
	object where;

	seteuid(getuid());
	where = environment(me);
	
	if (where->query("pigging"))
		return notify_fail("你还是专心拱猪吧！\n");

	if (me->is_busy() || me->query_temp("pending/exercising"))
		return notify_fail("你现在正忙着呢。\n");

	if( me->is_fighting() )
		return notify_fail("战斗中不能练内功，会走火入魔。\n");

	if( !stringp(me->query_skill_mapped("force")) )
		return notify_fail("你必须先用 enable 选择你要用的内功心法。\n");

	if( !arg || !sscanf(arg, "%d", exercise_cost))
		return notify_fail("你要花多少气练功？\n");
	if (exercise_cost < 10)
		return notify_fail("你的内功还没有达到那个境界！\n");

        if( ( (int)me->query("qi") < exercise_cost+10 )  ||  ( (int)me->query("qi") < exercise_cost + (int)(exercise_cost/10) ) )
		return notify_fail("你现在的气太少了，无法产生内息运行全身经脉。\n");

	if( (int)me->query("jing") <80 || (int)me->query("jing") * 100 / (int)me->query("max_jing") < 70 )
		return notify_fail("你现在精不够，无法控制内息的流动！\n");

	write("你坐下来运气用功，一股内息开始在体内流动。\n");

	me->set_temp("pending/exercise", 1);
	me->set_temp("exercise_cost", exercise_cost);
	message_vision("$N盘膝坐下，开始修炼内力。\n", me);
        me->start_busy( "exercising", "halt_exercise" );
	return 1;
}

int exercising(object me)
{
        int exercise_cost;
		int neili_gain;
		int max_possible_neili;
		
      if (!me) return 0;
        exercise_cost = (int)me->query_temp("exercise_cost");
          neili_gain = 1 + (int)me->query_skill("force") / 10;
	if (exercise_cost < 1)
		return 0;
	me->add("neili", neili_gain);
	me->set_temp("exercise_cost", exercise_cost -= neili_gain);
	me->add("qi", -neili_gain);

	if (exercise_cost > 0)
		return 1;

	me->set_temp("pending/exercise", 0);
	message_vision("$N运功完毕，深深吸了口气，站了起来。\n", me);
	if ((int)me->query("neili") < (int)me->query("max_neili") * 2)
		return 0;
	else {
		max_possible_neili = (int)me->query_skill("force") * 10;
		// 超出正常值，耗精
		if ((int)me->query("max_neili") > max_possible_neili)
		{
			me->add("jing", -50);
		}
		max_possible_neili += max_possible_neili * SPECIAL_D->query_effect(me, "neili")/200;
		if ((int)me->query("max_neili") > max_possible_neili ) {
			write("你的内力修为似乎已经达到了瓶颈。\n");
			me->set("neili", (int)me->query("max_neili"));
			return 0;
		}
		else {
			me->add("max_neili", 1);
			me->set("neili", (int)me->query("max_neili"));
			write("你的内力增加了！！\n");
			return 0;
		}
	}
}

int halt_exercise(object me, object who, string how)
{
       if (!me) return 1;
	if ((int)me->query("neili") > (int)me->query("max_neili") * 2)
		me->set("neili", (int)me->query("max_neili") * 2);
	me->set_temp("pending/exercise", 0);
	return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : exercise|dazuo [<耗费「气」的量> 必须多于 10]

运气练功，控制体内的气在各经脉间流动，藉以训练人体肌肉骨骼的耐
力、爆发力，并且用内力的形式将能量储备下来。
dz与dazuo不同的地方在于：dz在涨内力的同时还会增加内功的修习程度，
而且长期dz有可能会打通任督二脉，从而所有先天属性会随机增加1－2点。但
dz也有危险，在dz时halt或者战斗等可能导致走火，最大内力会减少一部分。
所以最好在安全的地方dz以避免走火。而dazuo就没有这方面的顾虑。

HELP
        );
        return 1;
}
