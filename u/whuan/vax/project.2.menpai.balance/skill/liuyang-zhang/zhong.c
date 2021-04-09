// zhong.c 种生死符

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
    object obj;
    string msg;

		 // dewolf 大弟子判定
    if( me->query("family/family_name")!="灵鹫宫" || !me->query("family/topone") )
        return notify_fail("只有本派大弟子才会种生死符呦！\n");
		
    if( !target ) target = offensive_target(me);
    if( !target || !target->is_character() )
        return notify_fail("生死符只能种在对手身上。\n");
    if( (int)me->query_skill("bahuang-gong", 1) < 120 )
        return notify_fail("你的八荒六合功不够娴熟，不能种生死符。\n");

    if( (int)me->query_skill("liuyang-zhang", 1) < 150 )
        return notify_fail("你的天山六阳掌不够娴熟，不能种生死符。\n");
    if( (int)me->query_skill("throwing", 1) < 100 )
        return notify_fail("你的暗器功夫不够娴熟，不能种生死符。\n");

    if (me->query_skill_mapped("throwing") != "liuyang-zhang")
        return notify_fail("你的暗器功夫不是天山六阳掌,无法种生死符。\n");
    if (!objectp(obj=present("jiudai", me)))
        return notify_fail("你身上没有酒袋，不能化水为冰。\n");

    if( (int)me->query("neili", 1) < 100 )
        return notify_fail("你现在内力太弱，不能发射暗器。\n");
    msg = CYN "$N从酒袋中倒出一些清水放在手掌中，倒运内力化水为冰，凝于掌中，轻飘飘地拍向$n。\n";

    me->add("neili", -100);
    if( random(me->query("combat_exp")) > (int)target->query("combat_exp")/2 ) 
    {
        msg += HIW " 结果$n身子一晃,双肩之后两下针刺般的疼痛直如万蚁咬啮！\n" NOR;
        target->receive_damage("qi",(int)me->query_skill("bahuang-gong",1), me);
        target->receive_wound("qi",15 + random(10));
        target->receive_wound("jing", 10);
        target->apply_condition("ss_poison", random(me->query_skill("liuyang-zhang",1)/10) +        target->query_condition("ss_poison"));
        me->start_busy(2);
        if( !target->is_killing(me->query("id")) ) target->kill_ob(me);
    } else {
        msg += "可是$p急忙闪在一旁，躲了开去。\n" NOR;
        me->start_busy(4);
    }
    message_vision(msg, me, target);
    target->start_busy(1 + random(2));
    destruct(obj);
    return 1;
}
