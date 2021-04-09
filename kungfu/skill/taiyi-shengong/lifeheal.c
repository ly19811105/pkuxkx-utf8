// lifeheal.c
// 2009.8.15 edited by zgbl

#include <ansi.h>

int exert(object me, object target)
{
    if( !target )
        return notify_fail("你要用真气为谁疗伤？\n");

    if( me->is_fighting() || target->is_fighting())
        return notify_fail("战斗中无法运功疗伤！\n");

    if( (int)me->query("max_neili") < 300 )
        return notify_fail("你的内力修为不够。\n");

    if( (int)me->query("neili") < 150 )
        return notify_fail("你的真气不够。\n");

    if ((int)me->query_skill("taiyi-shengong", 1) < 150)
        return notify_fail("你的太乙神功修为还不够。\n");

    if( target != me )
    {
        message_vision( HIY "$N坐了下来运起内功，将手掌贴在$n背心，缓缓地将真气输入$n体内....\n"
        "过了不久，$N额头上冒出豆大的汗珠，$n吐出一口瘀血，脸色看起来红润多了。\n" NOR,
        me, target );
    }
    else
    {
        write( HIY "你盘膝而坐，双目微闭，眼观鼻鼻观心，运起内功开始疗伤。\n" NOR);
        message("vision", HIY + me->name() + "吐出一口瘀血，脸色看起来红润多了。\n" NOR,
        environment(me), me);
    }

    target->receive_curing("qi", 10 + (int)me->query_skill("force")/3 );
    target->add("qi", 30 + (int)me->query_skill("force")/3 );
    if( (int)target->query("qi") > (int)target->query("eff_qi") ) target->set("qi", (int)target->query("eff_qi"));

    me->add("neili", -100);
    me->set("jiali", 0);
	me->start_busy(random(2));

    return 1;
//busy为0或1，治疗系数为1/3，沿用原版
}
