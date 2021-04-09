//Cracked by Kafei
//jianzhang.c 华岳三神峰

#include <ansi.h>
#include <combat.h>
inherit F_DBASE;
inherit F_SSERVER;

int valid_target_arg(string target)
{
    if ( target == "version" ) return 2;
    return target=="null" || target=="other" ;
}

int perform(object me, object target)
{
    string weapon;
    object weapon1;
    int lvl1, lvl2, amount;
    mapping attack_val = ([
        "base" : ([ "weapon" : "blade", "no_weapon" : "cuff", ]),//基本功夫类型
        "skill" : ([ "weapon" : "fanliangyi-dao", "no_weapon" : "poyu-quan", ]),//高级技能名称
        ]);

    if( !target ) target = offensive_target(me);

    if( !target || !target->is_character() || !me->is_fighting(target) )
            return notify_fail("「华岳三神峰」只能对战斗中的对手使用。\n");

    weapon1 = me->query_temp("weapon");
    if( !objectp(weapon1) || weapon1->query("skill_type") != "blade" )
            return notify_fail("你手中无刀，如何使得「华岳三神峰」？\n");

/*    if( me->query_skill_mapped("cuff") != "poyu-quan" )
            return notify_fail("你所用的并非劈石破玉拳，不能与华山反两仪刀法配合施展华岳三神峰！\n"); */

/*    if( me->query_skill_prepared("cuff") != "poyu-quan" )
            return notify_fail("你所备的并非劈石破玉拳，不能与华山反两仪刀法配合施展华岳三神峰！\n"); */

    if( me->query_skill_mapped("force") != "zixia-shengong" && me->query_skill_mapped("force") != "huashan-neigong" )
            return notify_fail("你所用的并非华山嫡传内功，无法施展「华岳三神峰」！\n");

    if( me->query_skill("zixia-shengong", 1) < 60 )
            return notify_fail("你的紫霞功火候未到，无法施展「华岳三神峰」！\n");

    if( (lvl1=me->query_skill("cuff", "poyu-quan")) < 100 )
            return notify_fail("「华岳三神峰」需要精湛的劈石破玉拳配合，方能有效施展！\n");

    if( (lvl2=me->query_skill("blade", "fanliangyi-dao")) < 100 )
            return notify_fail("你反两仪刀法修为不足，还不会使用「华岳三神峰」！\n");

    amount = (lvl1+lvl2) / 15;

    if ( amount < 40 ) amount = 40;
    if ( amount > 80 ) amount = 80;

    if( me->query("neili") <= amount*4 )
            return notify_fail("你的内力不够使用华岳三神峰！\n");
    if( me->query("jing") <= amount*2 )
            return notify_fail("你的精不够使用华岳三神峰！\n");

/*    if( me->query_skill_prepared("strike") == "hunyuan-zhang" ) {
            me->set_temp("restore", 1);
            me->prepare_skill("strike");
    } */

    weapon = me->query_temp("weapon");

    me->add_temp("apply/dodge", amount*2);

    message_vision(HIR "\n$N仰天一声清啸，运足内力使出「华岳三神峰」，向$n雷霆般地击出两拳一刀！\n\n" NOR, me, target);

    // make the 1st attack without weapon add more hit chances and damage.
    me->add_temp("apply/attack", amount*2);
    me->add_temp("apply/damage", amount*2);
    weapon->unequip();
    me->set_temp("attack_val", attack_val);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SPECIAL);

    // make the 2nd attack with weapon add more damage and reduce hit chance.
    me->add_temp("apply/attack", -amount);
    me->add_temp("apply/damage", amount);
    weapon->wield();
    me->set_temp("attack_val", attack_val);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SPECIAL);

    // make the 3rd attack without weapon add more hit chance and reduce damage.
    me->add_temp("apply/attack", amount*2);
    me->add_temp("apply/damage", -amount*2);
    weapon->unequip();
    me->set_temp("attack_val", attack_val);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SPECIAL);
    weapon->wield();

    me->start_busy(1+random(2));
    me->add("neili", -amount*3);
    me->add("jing", -amount*3);
    me->add_temp("apply/damage", -amount);
    me->add_temp("apply/dodge", -amount*2);
    me->add_temp("apply/attack", -amount*3);

/*    if( me->query_temp("restore") ) me->prepare_skill("strike", "hunyuan-zhang"); */

    return 1;
}
