// ailao.c 哀牢山剑意

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int i, a;

        if (!target) target=offensive_target(me);

        if (!target
                || !target->is_character()
                || !me->is_fighting(target))
                return notify_fail("你不在战斗中！\n");

//      if (target->is_busy())
//              return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧ⅵ\n");
        
        weapon=me->query_temp("weapon");
        if (!objectp(weapon) || weapon->query("skill_type") != "sword")
                return notify_fail("你手中无剑，如何使得出哀牢山剑意？\n");

        if (me->query_skill("kurong-changong", 1)<70)
                return notify_fail("你的内功火候未到，无法架御哀牢山剑意！\n");
        
        if (me->query_skill("sword", 1) < 100)
                return notify_fail("你剑法修为不够，无法施展哀牢山剑意！\n");
        
        if (me->query_skill("duanjia-sword",1)<200)
                return notify_fail("你段家剑修为不够，无法施展哀牢山剑意！\n");
        
        if( me->query_skill_mapped("force") != "kurong-changong")
                return notify_fail("你所用的内功与哀牢山剑意气路相悖！\n");

        if (me->query("neili") <= 500)
                return notify_fail("你的内力不够使用哀牢山剑意！\n");
        
        message_vision(HIR "\n突然间$N剑法突变，剑气纵横，上六剑，下六剑，前六剑，后六剑，左六剑，\n\n"NOR, me, target);
        message_vision(HIR "\n右六剑，施展哀牢山剑意对$n虚虚实实连刺了三十六剑！\n\n" NOR, me, target);

        if (me->query("combat_exp")*100/target->query("combat_exp")<120)
                a=2;
        else {
                if (me->query("combat_exp")*100/target->query("combat_exp")<150)
                        a=3;
                else {
                        if (me->query("combat_exp")*100/target->query("combat_exp")<180)
                                a=4;
                        else a=5;
                }
        }

        for (i=1; i<=a; i++)
                COMBAT_D->do_attack(me, target, weapon);

        me->start_busy(1);
        if (a>3)
        {
        me->start_busy(a-random(3));
        }
        me->add("neili", -200);
        me->add("jing", -20);
        return 1;
}