// shield.c 北冥神功护体神功
// modified by xuanyuan to add restrict eunuch use force 10/31/2001

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
	int skill;

	
	 // dewolf 大弟子判定
    if( me->query("id") != DADIZI_D->query_name("tianlong") )
        return notify_fail("只有本派大弟子才有能领会护体神功！\n");
	
	if( target != me ) 
		return notify_fail("你只能用北冥护体神功来提升自己的防御力。\n");

	if( (int)me->query("neili") < 1000  ) 
		return notify_fail("你的内力不够。\n");

	if( (int)me->query_skill("beiming-shengong",1) < 300 ) 
		return notify_fail("你的北冥神功修为不够。\n");

	if ( me->query("gender") == "无性" )
		return notify_fail("你无根无性，阴阳不调，难以运用北冥护体神功。\n");

	if( (int)me->query_temp("shield") ) 
		return notify_fail("你已经在运功中了。\n");

	skill = me->query_skill("force");
	me->add("neili", -(1000-(int)me->query_skill("beiming-shengong",1)));
	me->receive_damage("qi", 0);

	message_vision(
	HIW "$N双手平举过顶，运起北冥护体神功，全身笼罩在劲气之中！\n" NOR, me);

	me->add_temp("apply/armor", skill*2);
//	me->add_temp("apply/defense",  skill*2);
	me->set_temp("shield", 1);

	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill*2 :), skill);

	if( me->is_fighting() ) me->start_busy(2);

	return 1;
}

void remove_effect(object me, int amount)
{
	me->add_temp("apply/armor", - amount);
//	me->add_temp("apply/defense", - amount);
	me->delete_temp("shield");
	tell_object(me, "你的北冥护体神功运行完毕，将内力收回丹田。\n");
}
