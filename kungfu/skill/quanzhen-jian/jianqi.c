#include <ansi.h>
inherit F_DBASE;
inherit F_SSERVER;

int valid_target_arg(string target)
{
    if (target == "version") return 2;
    return target == "null" || target == "self";
}

int perform(object me, object target)
{
    object weapon;
    int damage, sword;

    if ( !me->is_fighting() )
        return notify_fail("「剑气」只能在战斗中使用。\n");

    if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword")
        return notify_fail("你手中无剑，怎能运用「剑气」？！\n");

    if ( weapon->query("unique") )
        return notify_fail("你手中之剑已是锋利之极，使用「剑气」没有什么作用！\n");

    if (me->query_temp("qz_jianqi"))
        return notify_fail("你刚使完「剑气」，目前气血翻涌，无法再次运用！\n");

    if ((int)me->query_skill("quanzhen-jian", 1) < 150 ||
        (int)me->query_skill("sword", 1) < 150 ||
        (int)me->query_str() <= 25)
        return notify_fail("你修为还不够，还未能领悟「剑气」！\n");

    if (me->query_skill("xiantian-gong", 1) < 150)
        return notify_fail("你的内功修为火候未到，施展只会伤及自身！\n");
    // 考虑出师内功切换问题，不判断force
    //if( me->query_skill_mapped("force") != "xiantian-gong")
    //        return notify_fail("你所用的内功与「剑气」心法相悖！\n");
/*    if (me->query_skill_mapped("sword") != "quanzhen-jian" ||
        me->query_skill_mapped("parry") != "quanzhen-jian")
        return notify_fail("你现在无法使用「剑气」进行攻击。\n"); */

    if (me->query("max_neili") <= 2000)
        return notify_fail("你的内力修为不足，劲力不足以施展「剑气」！\n");

    if (me->query("neili") <= 600)
        return notify_fail("你的内力不够，劲力不足以施展「剑气」！\n");

    if (me->query("jing") <= 200)
        return notify_fail("你的精力有限，不足以施展「剑气」！\n");

    message_vision(GRN"\n刷的一声响，$N潜运内力将" + weapon->name() + GRN"一抖。这一下使得剑气纵横，竟然声震山谷。不明其理之人，无不骇异！\n\n" NOR, me);

    damage = me->query_skill("quanzhen-jian");
    damage = damage / 6;
    sword = me->query_skill("sword", "quanzhen-jian") / 3;
    if (userp(me))
    {
        me->add("neili", -300);
        me->add("jing", -50);
        if (damage > weapon->query("weapon_prop/damage") * 2)
            damage = weapon->query("weapon_prop/damage") * 2;
//                else weapon->add("rigidity", 1);
//删除自动增加耐久 by seagate@pkuxkx
    }

    me->set_temp("qz_jianqi", 1);
    me->add_temp("apply/damage", damage);
    me->add_temp("apply/attack", damage);

    me->set_temp("active_buffer/family", "全真派");
    me->set_temp("active_buffer/quanzhen-jian.jianqi/name", "剑气");                      //buff名称
    me->set_temp("active_buffer/quanzhen-jian.jianqi/last_time", time() + sword / 2);       //持续时间
    me->set_temp("active_buffer/quanzhen-jian.jianqi/effect1", "攻击命中+" + damage + "级");   //效果描述1
    me->set_temp("active_buffer/quanzhen-jian.jianqi/effect2", "攻击伤害+" + damage + "点");   //效果描述2

    call_out("remove_effect1", sword / 2, me, weapon, damage);
    call_out("remove_effect2", sword * 2 / 3, me);
    me->start_exert(sword * 2 / 3, "「剑气」");

    return 1;
}

void remove_effect1(object me, object weapon, int damage)
{
    if (!me) return;
    me->add_temp("apply/attack", -damage);

    if (!weapon)
    {
        me->add_temp("apply/damage", -damage);
        me->delete_temp("active_buffer/quanzhen-jian.jianqi");
        if (sizeof(me->query_temp("active_buffer")) == 1)
            me->delete_temp("active_buffer");
        return;
    }
    me->add_temp("apply/damage", -damage);
    me->delete_temp("active_buffer/quanzhen-jian.jianqi");
    if (sizeof(me->query_temp("active_buffer")) == 1) 
        me->delete_temp("active_buffer");

    message_vision("\n$N一套「全真剑法」使完，手中" + weapon->name() + "上的光芒渐渐也消失了。\n", me);
    weapon->add("jianqi", 1);
    if (weapon && weapon->query("jianqi") >= (3 + weapon->query("rigidity")))
    {
        message_vision(HIW"\n只听“嚓”的一声，$N手中的$n"HIW"被内力冲击，裂成了碎片！\n"NOR, me, weapon);
        weapon->unequip();
        weapon->move(environment(me));
        weapon->set("name", "碎裂的" + weapon->query("name"));
        weapon->set("value", 49);
        weapon->set("weapon_prop", 0);
        me->reset_action();
    }
}

void remove_effect2(object me)
{
    if (!me) return;
    me->delete_temp("qz_jianqi");
    tell_object(me, HIG"\n你经过一段时间调气养息，又可以使用「剑气」了。\n"NOR);
}

