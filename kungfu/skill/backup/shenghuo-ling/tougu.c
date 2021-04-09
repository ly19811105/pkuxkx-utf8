// tougu.c 透骨针
// by snowman

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{        
 object weapon;
//  mapping fam
        int damage,p;
        string msg, *limbs;
        weapon = me->query_temp("weapon");
        
        if( !target) target = offensive_target(me);
        if( !target || !me->is_fighting(target) )
                return notify_fail("透骨针只能在战斗中对对手使用。\n");
        if(!weapon)
                return notify_fail("你必须使用武器来传递透骨针内劲！\n");        
        if( (int)me->query_skill("shenghuo-shengong",1) < 100 )
                return notify_fail("你的圣火神功等级不够，不能施展透骨针内劲！\n");
        if( (int)me->query_skill("force", 1) < 100 )
                return notify_fail("你的基本内功等级不够，不能施展透骨针内劲！\n");
        if( (int)me->query("neili") < 500 )
                return notify_fail("你的真气不足，不能施展透骨针内劲！\n");
        if( (int)me->query("max_neili") < 1000 )
                return notify_fail("你的内力不足，不能施展透骨针内劲！\n");
        if( (int)me->query("jing") < 300 )
                return notify_fail("你的精力不足，不能施展透骨针内劲！\n");

        tell_object(me, HIW"你悄悄运起"HIB"透骨针"HIW"，将一股极阴寒的内力积贮于一点，从"+weapon->name()+"上传出，直刺"+target->name()+"！\n"NOR);       
        if(random(me->query_skill("force")) > target->query_skill("force")/3){           
           damage = me->query_skill("force");
           damage = damage/2 + random(damage);
           if(target->query_skill("force")-50 > me->query_skill("force"))
             damage = damage/2;            
           if(target->query_skill("force") > me->query_skill("force")*2)
             damage = random(10);
           if(me->query_skill("force") > target->query_skill("force")*2)
             damage = damage+random(damage);
           if(damage > 300)
              tell_object(target, HIB"\n突然之间，你胸口一痛，似乎被一枚极细的尖针刺了一下。这一下刺痛
突如其来，似有形，实无质，一股寒气突破你的护体神功，直钻入心肺！\n"NOR);
           else if(damage <= 10){
              damage = 10;
              tell_object(target, HIY"\n突然之间，你胸口一痛，似乎被一枚极细的尖针刺了一下。幸好你护体神功遍
护全身，这阴劲虽是凝聚如丝发之细，倏钻陡戳，难防难当，却也伤你不得！\n"NOR);
              tell_object(me, HIY"你连运“透骨针”的内劲，但见对方竟是毫不费力的抵挡了下来！\n"NOR);
              }
           else tell_object(target, HIB"\n突然之间，你胸口被尖针刺了一下。刺痛似有形，实无质，一股寒气突破你的
护体神功，直侵内脏！阴劲入体，立即消失，但这一刺可当真疼痛入骨！\n"NOR);
           target->receive_damage("qi", damage, me);
           target->receive_wound("qi", damage/3, me);
           target->add("neili", -damage/2); 
           limbs = target->query("limbs");
           p = (int)target->query("qi")*100/(int)target->query("max_qi");
           tell_room(environment(target), HIR + target->name()+"突然全身一颤，如同被尖针刺了一下！\n" NOR, ({ target }));  
           msg = damage_msg(damage, "内伤");
           msg += "( $n"+eff_status_msg(p)+" )\n";
           message_vision(msg, me, target);
           me->start_busy(2);
           me->add("neili", -150);
           me->add("jing", -20);
           target->start_busy(random(3));
           return 1;
           }
         
     else {
          me->add("neili", -50);
          me->add("jing", -5);
          tell_object(me, HIY"结果透骨针内劲还没触到"+target->name()+"便已经散了。\n"NOR);
          me->start_busy(2);         
          }
        return 1;
}
