// 眩目 - 日月剑法 

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	string msg;
	int damage,jian;
	object weapon;

	if( !target ) target = offensive_target(me);
	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("眩目只能对战斗中的对手使用。\n");
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
        if (!objectp(weapon = me->query_temp("secondary_weapon"))
        || (string)weapon->query("skill_type") != "sword")
	        return notify_fail("你没拿剑,还想使剑法的绝招?别作梦了!\n");
	
	if(me->query_skill("riyue-jian",1)<100)
		return notify_fail("你日月剑法不太熟练，不能使出「眩目目」一式。\n");
	if(me->query("neili")<200)
		return notify_fail("你内力不够，不能使出「眩目」一式。\n");

	me->delete_temp("riyue/usingjian");
        if (objectp(weapon = me->query_temp("weapon"))
        && (string)weapon->query("id") == "riyue jian")
		me->add_temp("riyue/usingjian",1);
        
	if (objectp(weapon = me->query_temp("secondary_weapon"))
        && (string)weapon->query("id") == "riyue jian")
		me->add_temp("riyue/usingjian",1);
	jian = (int)me->query_temp("riyue/usingjian");

	msg = HIG "$N使出日月剑法的「眩目」一式，剑式突然加快，映出点点剑光。\n";
	me->start_busy(random(400 / (int)me->query_skill("riyue-jian",1)));
	if(random(me->query("combat_exp")) > (int)target->query("combat_exp")*2/(3+jian) ) 
	{
		msg += HIG "$p眼前出现千万支剑影，如道道电光，吓得不知该从何处进攻才好。\n" NOR;
         
		target->start_busy((int)me->query_skill("riyue-jian",1) * (jian + 1)/50);
	}
	else 	
	msg += HIG "可是$p看破了$P的企图，并没有上当。\n" NOR;
	message_vision(msg, me, target);
	return 1;
}
