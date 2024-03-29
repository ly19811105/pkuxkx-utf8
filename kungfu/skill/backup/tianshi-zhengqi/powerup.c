// powerup.c 天师正气加力
//made by hacky
#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if( target != me )
                return notify_fail("你只能用天师正气来提升自己的战斗力。\n");

        if( (int)me->query("neili") < 150  )
                return notify_fail("你的内力不够。\n");
        if( (int)me->query_temp("powerup") )
                 return notify_fail("你已经在运功中了。\n");
        if ((int)me->query_skill("tianshi-zhengqi", 1) < 50)
                return notify_fail("你的天师正气等级不够，不能提升战斗力。\n");

        skill = me->query_skill("force")+me->query_skill("tianshi-zhengqi");
        me->add("neili", -150);
        me->receive_damage("qi", 0);

        message_vision(
        HIR "$N气沉丹田，一股内力似源源不断的流入掌心,只觉得全身充满了力量\n" NOR, me
);

        me->add_temp("apply/attack", skill/5);
        me->add_temp("apply/dodge", skill/5);
        me->add_temp("apply/defense",skill/5);
        me->set_temp("powerup", 1);

        me->start_call_out(__FILE__, "remove_effect", skill, me, skill/5);

        if( me->is_fighting() ) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        me->add_temp("apply/attack", - amount);
        me->add_temp("apply/dodge", - amount);
        me->delete_temp("powerup");
        tell_object(me, "你的天师正气运行完毕，将内力收回丹田。\n");
}
