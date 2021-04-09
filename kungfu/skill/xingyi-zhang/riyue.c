// canyun // bren

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;

	int i;
	i = me->query_skill("xingyi-zhang", 1)/2;
	if( !target ) target = offensive_target(me);

        if( !target ||	!target->is_character() || !me->is_fighting(target) )
                return notify_fail("「日月同辉」只能在战斗中对对手使用。\n");

        if( (int)me->query_skill("xingyi-zhang", 1) < 180 )
                return notify_fail("你的星移掌不够娴熟，不会使用「日月同辉」。\n");

        if( (int)me->query_skill("shenyuan-gong", 1) < 180 )
                return notify_fail("你的神元功等级不够，不能使用「星光点点」。\n");

        if( (int)me->query_dex() < 35 )
                return notify_fail("你的身法不够强，不能使用「日月同辉」。\n");

        if (me->query_skill_prepared("strike") != "xingyi-zhang"
        || me->query_skill_mapped("strike") != "xingyi-zhang")
                return notify_fail("你现在无法使用「日月同辉」进行攻击。\n");                                                                                
      

        if( (int)me->query("neili") < 700 )
                return notify_fail("你现在内力太弱，不能使用「日月同辉」。\n");
        me->add("neili", -300);
        me->add("jingli", -40);
        message_vision(CYN "\n$N双掌一搓，在双掌之间形成一个耀眼的「"HIW"气旋"CYN"」！\n" NOR,me, target);

//        me->add_temp("apply/strength", i);
        me->add_temp("apply/dexerity", i/5);
        me->add_temp("apply/attack", i);
        me->add_temp("apply/damage", i);
//C-&&C-=E
if ( F_KUNGFU->hit_rate( me->query("combat_exp"), (int)target->query("combat_exp"), 9, me, target) &&
	   F_KUNGFU->hit_rate( (int)me->query_skill("force"), (int)target->query_skill("force"), 9, me, target) )
{
msg = HIR"$N双掌收在胸前，移形换步闪电般将「"HIW"气旋"HIR"」击向$n的檀中穴！"NOR;
COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK,msg);

msg = HIG"紧接着$N抽出左掌，身形一矮，由下而上猛袭向$n的小腹！"NOR;
COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK,msg);

msg = HIR"只见$N右掌随后而至，凌空一跃，犹如晴空霹雳拍向$n的头部！"NOR;
COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK,msg);

msg = HIY"$N在空中一个回转，携「"HIR"日月之光"HIY"」, 双掌按向$n的丹田！"NOR;
COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK,msg);

}
else
{
msg = HIR"$N双掌收在胸前，移形换步闪电般将「"HIW"气旋"HIR"」击向$n的檀中穴！"NOR;
COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK,msg);

msg = HIG"紧接着$N抽出左掌，身形一矮，由下而上猛袭向$n的小腹！"NOR;
COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK,msg);

msg = HIR"只见$N右掌随后而至，凌空一跃，犹如晴空霹雳拍向$n的头部！"NOR;
COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK,msg);

me->start_busy(3);
me->start_perform(5,"「"HIR"日月同辉"NOR"」")  ;
call_out("perform2", 3, me, target);
}
message_vision(YEL "\n$N一式「日月同辉」发挥的淋漓尽致，双掌一分，气定神闲，信心倍增。
\n" NOR,me, target);
//       me->add("neili", -400);
        me->add_temp("apply/dexerity", -i/5);
        me->add_temp("apply/damage", -i);
//        me->add_temp("apply/strength", -i);
        me->add_temp("apply/attack", -i);
//        me->start_perform(5,"「"HIR"日月同辉"NOR"」")  ;
        me->start_busy(2+random(4));

        return 1;
}
int perform2(object me, object target)
{
   string msg;
   int i;
 i = me->query_skill("xingyi-zhang", 1)/2;
if (!me || !target) return 0;
        if(!living(target))
          return notify_fail("对手已经不能再战斗了。\n");

        if( (int)me->query("neili", 1) < 300 )
               return notify_fail("你待要再次进攻，却发现自己的内力不够了！\n");
        me->add_temp("apply/strength", i/5);
        me->add_temp("apply/dexerity", i/5);
        me->add_temp("apply/attack", i);
        me->add_temp("apply/damage", i);
msg = HIY"$N在空中一个回转，携「"HIR"日月之光"HIY"」, 双掌按向$n的丹田！"NOR;
COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK,msg);

msg = HIC"只见$N斜身半转，陡地拍出两掌，蓄势凌厉，直指$n左胁！"NOR;
COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK,msg);

msg = HIW"$N将神元神功发挥到极限，幻化出漫天掌影，向$n全身笼罩过去！"NOR;
COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK,msg);



 me->add("neili", -400);
        me->add_temp("apply/dexerity", -i/5);
        me->add_temp("apply/damage", -i);
        me->add_temp("apply/strength", -i/5);
        me->add_temp("apply/attack", -i);
//        me->start_perform(5,"「"HIR"日月同辉"NOR"」")  ;
        me->start_busy(2+random(5));

        return 1;
}


