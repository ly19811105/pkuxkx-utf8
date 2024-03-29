// neilisuck.c

#include <ansi.h>

int exert(object me, object target)
{
	int sp, dp;

	if( !objectp(target) || target->query("id") == "mu ren" )
		return notify_fail("你要吸取谁的内力？\n");

	if ( me->query_temp("sucked") )
		return notify_fail("你刚刚吸取过内力！\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("你必须空手才能施用化功大法吸人内力！\n");

	if( !me->is_fighting() || !target->is_fighting())
		return notify_fail("你必须在战斗中才能吸取对方的内力！\n");

	if( (int)me->query_skill("huagong-dafa",1) < 60 )
		return notify_fail("你的化功大法功力不够，不能吸取对方的内力！n");

	if( (int)me->query("neili",1) < 20 )
		return notify_fail("你的内力不够，不能使用化功大法。\n");
	
	if ( me->query("neili")>=me->query("max_neili") * 3 )
		return notify_fail("你的内力吸的太多了，体内经脉已经容纳不下了。\n");

	if( (int)target->query("max_neili") <= 0 )
		return notify_fail( target->name() +
			"没有任何内力！\n");

	if( (int)target->query("neili") < (int)target->query("max_neili") / 10 )
		return notify_fail( target->name() +
			"已经内力涣散，你已经无法从他体内吸取任何内力了！\n");

	message_vision(
		HIR "$N一张脸突然变得惨白，右掌直出，猛地对准$n的膻中大穴按了上去！\n\n" NOR,
		me, target );

	if( !target->is_killing(me->query("id")) ) target->kill_ob(me);

	sp = me->query_skill("force") + me->query_skill("dodge") + me->query("kar");
	dp = target->query_skill("force") + target->query_skill("dodge") + me->query("kar");

	me->set_temp("sucked", 1);		
//命中率级别C-
	if( F_KUNGFU->hit_rate(sp, dp, 9, me, target) )
	{
		tell_object(target, HIR "你顿觉膻中微痛，如同被尖针刺了个小孔，全身内力如水银般循孔飞泄而出！\n" NOR);
		tell_object(me, HIG "你觉得" + target->name() + "的内力自手掌源源不绝地流了进来。\n" NOR);

		target->add("neili", -1*(int)me->query_skill("huagong-dafa", 1) );
		me->add("neili", (int)me->query_skill("huagong-dafa", 1) );

		if( target->query("combat_exp") >= me->query("combat_exp") ) {		
   if( (int)me->query("potential") - (int)me->query("learned_points") < 300 )
				me->add("potential", 1);
			me->add("combat_exp", 1);
		  me->add("exp/suck",1); //增加suck的经验记录，跟踪是否利用此bug
		}

		me->start_busy(random(4));
		target->start_busy(random(4));
		me->add("neili", -10);

		call_out("del_sucked", 2, me);
	}
	else
	{	
		message_vision(HIY "可是$p看破了$P的企图，机灵地闪了开去。\n" NOR, me, target);
		me->start_busy(4);
		call_out("del_sucked", 4, me);
	}
		if (me->query("neili") > me->query("max_neili")*2)
		{
			if (me->query("max_neili") > 20*me->query_skill("force"))
				tell_object(me,"你忽然觉得自己的内功有限，无法支持如此之高的内力。\n");
			else
			{
				tell_object(me,"你的内力增加了！\n");
				me->add("max_neili",1);
				me->set("neili",0);
			}
		}

	return 1;
}

void del_sucked(object me)
{
	if (objectp(me))
	{
		if ( me->query_temp("sucked"))
			me->delete_temp("sucked");
	}
}

