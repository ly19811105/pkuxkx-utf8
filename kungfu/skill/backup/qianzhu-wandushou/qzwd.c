// qianzhu-wandushou.c 千蛛万毒
#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	string msg;
       int damage;
	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("千蛛万毒只能对战斗中的对手使用。\n");

//	if((int)me->query_skill("duji",1) < 100)
//		return notify_fail("你毒技太低,不能使用这一绝技!\n");

//	if((int)me->query_skill("wudu-shengong",1) < 80)
//		return notify_fail("你五毒神功的功力不够不能使用千蛛万毒!\n");

	if((int)me->query_skill("qianzhu-wandushou",1) < 150)
		return notify_fail("你的千蛛万毒手修为不够,还不能使用千蛛万毒的绝技!\n");

	if((int)me->query("max_neili") < 700)
		return notify_fail("你内力修为不够, 不能使用千蛛万毒! \n");

	if((int)me->query("neili") < 200)
		return notify_fail("你内力不够, 不能使用千蛛万毒! \n");

       if(me->query_temp("qzwd_used"))
		return notify_fail("你刚使用过千蛛万毒，无法在短时间里积聚毒力! \n");

	msg = HIR "$N一声狞笑飞身纵起，凌空一指向$n的眉心点去。\n";
	message_vision(msg, me, target);

	if( random(me->query_skill("qianzhu-wandushou",1)) > random((int)target->query_skill("dodge",1)* 2 / 3 )) {
		msg = HIR"只见一缕黑气从$N的指尖透出，只一闪就没入$n的眉心！\n" NOR;
	       message_vision(msg, me, target);
             if(target->query_skill("hunyuan-yiqi",1)>me->query_skill("qianzhu-wandushou",1)*12/10&&random(2)==0){             
		msg = RED"$N忽然觉得指力被一团无形的劲力包裹着，紧接着只听\n
$n一声大喝，$N顿时如一根稻草般被抛向远处。\n" NOR;
	       message_vision(msg, me, target);
		msg = RED"$P只觉得一股如山的劲力顺指尖猛攻过来，只觉得全身毒气狂窜。\n忽然胸口一痛，不由“哇”的一声吐出一口黑血！\n" NOR;
	       message_vision(msg, me);
              damage=(int)me->query_skill("qianzhu-wandushou",1)
                     +(int)me->query_skill("wudu-shengong",1);
              if(damage < 50 ) damage = 50;
		target->receive_wound( "qi",damage, me);
		me->add("neili", -100);
              me->start_busy(2);
              }    
              else{
		msg = HIR"$n不由一声惨嚎摔倒在地，身体已痛苦得蜷缩成一团！\n" NOR;
	       message_vision(msg, me, target);
              damage=(int)me->query_skill("duji",1)
                    +(int)me->query_skill("qianzhu-wandushou",1)
                    +(int)me->query_skill("wudu-shengong",1)/2;
              if(damage > 900 ) damage = 900;
		target->receive_wound( "qi",damage, me);
	       target->apply_condition("snake_poison",
		        (int)target->query_condition("snake_poison") + 50 );
	       target->apply_condition("wugong_poison",
		        (int)target->query_condition("wugong_poison") + 50 );
	       target->apply_condition("zhizhu_poison",
		        (int)target->query_condition("zhizhu_poison") + 50 );
	       target->apply_condition("xiezi_poison",
		        (int)target->query_condition("xiezi_poison") + 50 );
	       target->apply_condition("chanchu_poison",
		        (int)target->query_condition("chanchu_poison") + 50 );
		me->add("neili", -100);
             target->start_busy(4);
             }
	} 
       else {
		msg = HIG "可是$n早有准备，一个懒驴打滚，堪堪躲过了这一招。\n" NOR;
		me->start_busy(4);
	       message_vision(msg, me, target);
		me->add("neili", -100);
	}
	if( !target->is_killing(me->query("id")) ) target->kill_ob(me);
       me->set_temp("qzwd_used",1);
	remove_call_out ("qzwd_used");
	call_out ("qzwd_used", 6); 
	return 1;
}
void qzwd_used()
{
        this_player()->delete_temp("qzwd_used");
}
