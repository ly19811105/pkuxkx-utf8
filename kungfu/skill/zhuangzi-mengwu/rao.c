// rao.c 
// by hubo

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;
        object weapon;

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("绕蝶只能对战斗中的对手使用。\n");  
        if( me->query("hhh_zhuangzi") != 1 )
                return notify_fail("你还没有领悟到绕蝶的用法。\n");                
        if( target->is_busy() )
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧ⅵ\n");                
        if( (int)me->query_skill("zhuangzi-mengwu", 1) < 120 )
                return notify_fail("你的庄子梦舞不够娴熟，不会使用绕碟绝招。\n");

        msg = HIW "$N使出庄子梦舞的绕蝶绝招：轻轻念道：以神遇，而不以目视，官知止而神欲行。\n";

        me->start_busy(2);
        if( random(me->query("combat_exp")) > (int)target->query("combat_exp")/2 ) {
                msg += HIW"$p只感觉金蝶狂舞，只见全是$P的人影在晃，头晕眼花，不能攻击！\n" NOR;
                target->start_busy( (int)me->query_skill("zhuangzi-mengwu")/30 );
        } else {
                me->start_busy(2+random(2));
                msg += HIW"$p赶紧向后急退，跳出圈外，没被绕住，心里暗道一声：侥幸！\n" NOR;
        }
        message_vision(msg, me, target);

        return 1;
}

