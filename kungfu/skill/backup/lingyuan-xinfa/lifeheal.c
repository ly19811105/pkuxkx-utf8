// lifeheal.c
// Modified by Venus Oct.1997

#include <ansi.h>

int exert(object me, object target)
{
    if ((!target)||target->query("id")==me->query("id"))
   return notify_fail("你要用真气为谁疗伤？\n");

    if( me->is_fighting() || target->is_fighting())
   return notify_fail("战斗中无法运功疗伤！\n");

    if( (int)me->query("max_neili") < 200 )
   return notify_fail("你的内力修为不够。\n");

    if( (int)me->query("neili") < 100)
   return notify_fail("你的真气不够。\n");

    if( (int)target->query("eff_qi") < (int)target->query("max_qi") / 5 )
   return notify_fail( target->name() + "受伤过重不能疗伤!\n");

    message_combatd(HIY"$N坐了下来运起内功，将手掌贴在$n背心，缓缓地将真气输入$n体内....\n\n"
"过了不久，$N额头上冒出豆大的汗珠，$n吐出一口瘀血，脸色看起来红润多了。\n" NOR, me, target);

    target->receive_curing("qi", 100 + (int)me->query_skill("force")/2 );
    target->add("qi", 100 + (int)me->query_skill("force")/3 );
    target->receive_curing("jing", 80 + (int)me->query_skill("force")/2 );      
    target->add("jing", 80 + (int)me->query_skill("force")/3 );
    if( (int)target->query("qi") > (int)target->query("eff_qi") ) target->set("qi", (int)target->query("eff_qi"));
    if( (int)target->query("jing") > (int)target->query("eff_jing") ) target->set("jing", (int)target->query("eff_qi"));

    me->add("neili", -50);

    return 1;
}
