inherit F_CLEAN_UP;
#include <ansi.h>
#include <condition.h>

int update_condition(object me, int duration)
{
    if( duration < 1||!me->query("myVeins/手阳明大肠经/completed") ) return 0;
    if( !living(me) ) 
	return CND_CONTINUE;
    else 
    {
		if (me->query("neili")<me->query("max_neili")*2)
		{
			me->add("neili","feature/vein/BasicVein/shouyangming.c"->benefit_effect(me));
			if (me->query("jingli")<me->query("max_jingli")*2)
			me->add("jingli","feature/vein/BasicVein/shouyangming.c"->benefit_effect(me)/2);
			tell_object(me, HIC "你腹中食物在手阳明大肠经的真气引导下又激活了更多潜藏的真气。\n" NOR );
        }
    }
    me->apply_condition("shouyangming", duration - 1);
    return CND_CONTINUE;
}
