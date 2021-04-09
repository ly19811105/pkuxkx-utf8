// powerup.c 易筋经加力

#include <ansi.h>
inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
	int skill;

	if( target != me )
		return notify_fail("你只能提升自己的战斗力。\n");
	if( (int)me->query("neili")<200)
		return notify_fail("你的内力不够。\n");
	if( (int)me->query_temp("powerup"))
		return notify_fail("你已经在运功中了。\n");
	if( (int)me->query_temp("jingang") ) 
		return notify_fail(HIG"你的全部功力都运在大金刚拳上了。\n"NOR);
	if( (int)me->query_temp("zuida") ) 
		return notify_fail(HIG"你内息翻滚在八仙醉打中，一时提不起易筋神功。\n"NOR);

	skill = me->query_skill("force");

	message_combatd(
	HIR "$N舌尖一咬，喷出一口鲜血，运起易筋神功已将全身潜力尽数提起！\n" NOR, me);

	me->add_temp("apply/attack", skill/5);
	me->add_temp("apply/dodge", skill/5);
	me->set_temp("powerup", 1);
	me->add("neili", -100);

                me->start_call_out(__FILE__, "remove_effect", skill, me, skill/3);

	if( me->is_fighting() ) me->start_busy(3);

	return 1;
}

void remove_effect(object me, int amount)
{
        int skill;
        skill = me->query_skill("force");
	me->add_temp("apply/attack", - skill/5);
	me->add_temp("apply/dodge", - skill/5);
	me->delete_temp("powerup");
	tell_object(me, "你的易筋神功运行完毕，将内力收回丹田。\n");
}
