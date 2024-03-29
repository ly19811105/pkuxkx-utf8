// chan.c 日月鞭法「缠绕」诀
#include <ansi.h>
inherit F_SSERVER;

int valid_target_arg(string target)
{
    if ( target == "version" ) return 2;
    return target=="null" || target=="other" ;
}

int perform(object me, object target)
{
    string msg;
    object weapon;

    if( !target ) target = offensive_target(me);

    if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
        return notify_fail("牵制攻击只能对战斗中的对手使用。\n");

    if( target->is_busy() )
        return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");

    if(!objectp(weapon = me->query_temp("weapon")) || (string)weapon->query("skill_type") != "whip")
        return notify_fail("你使用的武器不对。\n");

    if( (int)me->query("neili") < 400  )
        return notify_fail("你的内力不够。\n");

    msg =HIC "$N手中长索纵横盘绕驰骋往来展开一张"+HIR+"无形大网"+HIC+"封住了$n所有去路,
$n只看到"+RED+"杀气"+HIC+"劈天盖地而来,冥冥中又听见天外之音"+HIY+"如佛梵唱"HIC",心中
所有斗志都已消失只想抛下屠刀忏悔.\n在不知不觉间,$N竟然已经独自把"+HIY+"金刚伏魔"+HIC+
"的意境展现得淋漓尽致!\n\n" NOR ;

    me->start_busy(1+random(2));
    if( F_KUNGFU->hit_rate(me->query("combat_exp"), target->query("combat_exp"), 7, me, target) ) 
    {
        msg +=HIY "$p已完全陷入世俗争斗的自责中无法自拔,待惊觉却为时已晚.\n$P"+HIW+"金刚伏魔"HIY"法力收紧已将$p行动完全制住!\n\n" NOR;
        F_KUNGFU->hit_busy( "body", (int)me->query_skill("riyue-bian") / 20 + 2, target );
    }
    else 
    {
        msg +=WHT "$p面对无边的佛法正气，心中"+HIR+"魔念"+WHT+"大炽愈演愈烈，心中恶性骤起.\n
        龅?p悟到了成王败寇的规律，突然仰天大笑三声直上云霄！
        四野八荒竟充满了"+RED+"邪恶"+WHT+"之意。$P无法继续唱念佛竭只得作罢。\n" NOR;
        me->start_busy(3);
    }
    me->add("neili", -100);
    message_vision(msg, me, target);

    return 1;
}

