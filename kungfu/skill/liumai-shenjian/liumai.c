// qifa.c
// modified by advent & iszt@pkuxkx, 2007-01-17
// add rumor, write end_pfm()
// close skip_combat, it is better to use message_version to display.
//减弱六脉的北冥加成效果，去除枯荣的要求，去除外派不能用六脉 by huacuoh 2015/2/14
#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>
inherit F_SSERVER;

int valid_target_arg(string target)
{
    if (target == "version") return 2;
    return target == "null" || target == "other";
}

int end_pfm(object target, int extra, int flag)
{
    object me = this_player();
    string msg;
    me->add_temp("apply/attack", -extra / 2);
    if (!flag)
        me->add_temp("apply/damage", -extra * 7 / 15);
    else
        me->add_temp("apply/damage", -extra / 3);
    me->add_temp("apply/strength", -extra / 6);
    me->add("neili", -extra);
    //恢复combat设置
    //me->set("env/skip_combat",me->query_temp("combat_env"));
    //target->set("env/skip_combat",target->query_temp("combat_env"));
    me->start_busy(3);
    //me->set("actions", (: call_other, "/kungfu/skill/liumai-shenjian.c", "query_action" :));
/*        if(target->query("qi")<=0 && random(8)<1 && me->query("env/rumor"))
        {
                msg=NOR+HIY+me->name()+HIM"内力如泉涌，将"+MAG"天龙寺绝技"+HIM"「"HIR"六脉齐发"+HIM"」施展得纵横飞舞，听说"+target->name()+HIM"满身都是剑痕！\n"NOR;
                message("channel:rumor",HIM"【谣言】某人："+msg,users());
        }
*/
    return 1;
}

int perform(object me, object target)
{
    string msg, str;
    int damage, flag = 0, cds;
    object weapon;
    int extra = me->query_skill("liumai-shenjian", 1);
    mixed *lm_msgs = (
    {
        ({GRN"$N"GRN"的「少商剑法」大开大阖，气派宏伟，每一剑刺出，都有石破天惊、风雨大至之势！"NOR,
               GRN"$N"GRN"大拇指连挥，「少商剑气」便如是一幅泼墨山水相似，纵横倚斜，寥寥数笔，却是剑路雄劲！"NOR,
               GRN"$N"GRN"双手围圈，左手紧压右手，右手大拇指慢慢按出，只见眼前气势一紧，「少商神剑」的无形之气缓缓推出！"NOR}),
           ({HIY"$N"HIY"把拇指一屈，食指点出，变成了「商阳剑法」，一缕剑气破空而去！"NOR,
               HIY"$N"HIY"使出「商阳剑法」，食指忽屈忽伸，每一下点出，都是一缕无形指风似剑刺出！"NOR,
               HIY"$N"HIY"食指连动，「商阳剑法」一剑又一剑的刺出，其轻灵迅速，快速无比！"NOR}),
           ({HIG"$N"HIG"身形一恭，双手前伸，一式「中冲剑法」,双手合使，两道凌厉无比的剑气破空刺出！"NOR,
               HIG"$N"HIG"脸色森然，中指一竖，一挑，一式「中冲剑法」,两道剑气交错而行，向前刺出！"NOR,
               HIG"电光火石之间，$N"HIG"一翻掌，身向右移，奋起神威，右手斗然探出，剑气如利剑般刺向$n"HIG"！"NOR}),
           ({YEL"$N"YEL"食指一收，无名指突然点出，「关冲剑气」一发，一条剑气直射而出，快捷无比！"NOR,
               YEL"$N"YEL"长笑一声，俯身斜倚，无名指弹出，指尖已对准$n"YEL"发出了一缕强烈的劲风！"NOR,
               YEL"$N"YEL"无名指一挥，拙滞古朴的关冲剑气直射而出，端端正正地刺向$n"YEL"！"NOR}),
           ({HIR"$N"HIR"手臂陡然一提，在手掌离$n"HIR"不到一尺之处，使一招「少泽剑法」,立即翻腕向上，屈掌成拳，小指弹出！"NOR,
               HIR"忽见$N"HIR"左手小指一伸，一条气流从$N"HIR"的少泽穴中激射而出，好一招「少泽剑法」,忽左忽右，变化无常，指向$n"HIR"！"NOR,
               HIR"$N"HIR"左手小指上翘，灵动异常，忽屈忽伸，连续划圈，发出无数劲风！"NOR}),
           ({HIB"$N"HIB"右手小指一弹，使出一招「少冲剑法」，剑势如同柳絮一般，飘而不乱！"NOR,
               HIB"$N"HIB"掌托于胸前，伸出右小指，一招「少冲剑法」,缓缓地点向$n"HIB"的周身大穴，弹指无声！"NOR,
               HIB"$N"HIB"一招「少冲剑法」，剑气回转，竟从左侧绕了过来，点向$n"HIB"的后心！"NOR})});
    mapping attack_val = ([
                          "base" : ([ "weapon" : "sword", "no_weapon" : "finger", ]), //基本功夫类型
                           "skill" : ([ "weapon" : "liumai-shenjian", "no_weapon" : "liumai-shenjian", ]), //高级技能名称
                           ]);

    if (!target) target = offensive_target(me);

    if (!objectp(target) || !target->is_character() || !me->is_fighting(target))
        return notify_fail("「六脉齐发」只能对战斗中的对手使用。\n");

    if ( (int)me->query_skill("liumai-shenjian", 1) < 200 )
        return notify_fail("你的六脉神剑不够火候, 使不出「六脉齐发」。\n");

  /*  if ( userp(me) && 
         (int)me->query_skill("beiming-shengong", 1) < 200 )
        return notify_fail("你的北冥神功不够火候, 使不出「六脉齐发」。\n");
*/
//去除北冥依赖，by yhzzyahoo 2015/2/15
   /* if ( userp(me) && 
         (int)me->query_skill("kurong-shengong", 1) < 100 )
        return notify_fail("你的枯荣神功不够火候, 使不出「六脉齐发」。\n");
*/
//去掉枯荣的依赖by huacuoh 2015/2/14
    if (   objectp(weapon = me->query_temp("weapon"))
        && (string)weapon->query("skill_type") != "sword" )
        return notify_fail("你需要装备剑类武器才能使用「六脉齐发」的绝招。\n");

    if (objectp(weapon = me->query_temp("weapon"))
        && (string)weapon->query("skill_type") == "sword")
        flag = 1;

    if ( (int)me->query("max_neili") < 5000 )
        return notify_fail("你内力修为不够使出六剑齐发。\n");

    if ( (int)me->query_temp("perform/liumai_cd") >= time() )
        return notify_fail("你刚刚使用过「六剑齐发」，目下气血翻涌，无法再次施展。\n");

    //extra=me->query_skill("liumai-shenjian", 1)/2+me->query_skill("beiming-shengong",1)/3;
    if ( me->query("family/family_name")=="天龙寺" && !me->query("chushi/done"))
	{
	extra=me->query_skill("liumai-shenjian", 1)+me->query_skill("beiming-shengong",1)/20;
//大致修改下by huacuoh/2015/2/14,加强下纯天龙寺的
 	} 
	if (extra>3000)
	{
		extra=3000;
	}
    if ( me->query("max_neili")>10000 && me->query("max_neili")<=20000)
      extra+=50;
    else if ( me->query("max_neili")>20000 && me->query("max_neili")<=30000)
      extra+=100;
    else if ( me->query("max_neili")>30000 && me->query("max_neili")<=40000)
      extra+=200;
    else if ( me->query("max_neili")>40000 )
      extra+=300;

    if ((int)me->query("neili") < extra / 2)
        return notify_fail("你的内力不够呀!\n");
 
    me->add_temp("apply/attack", extra / 2);
    if (!flag)
        me->add_temp("apply/damage", extra * 7 / 15);
    else
        me->add_temp("apply/damage", extra / 3);

    me->add_temp("apply/strength", extra / 6);

    if (extra <= 1000)
    {
        if (me->query("betrayer"))
            cds = 6;
        else if (me->query("chushi/last_family"))
            cds = 4;
        else
            cds = 3;
    }
    else
    {
        if (me->query("betrayer"))
            cds = 5;
        else if (me->query("chushi/last_family"))
            cds = 3;
        else
            cds = 2;
    }

    me->set_temp("perform/liumai_cd", time() + cds + random(2));

    msg = CYN "$N使出六脉神剑的「六脉齐发」...\n";

    //显示perform具体情况
    //me->set_temp("combat_env",me->query("env/skip_combat"));
    //me->set("env/skip_combat",0);
    //target->set_temp("combat_env",target->query("env/skip_combat"));
    //target->set("env/skip_combat",0);

    msg += "$N只觉得内力激荡，六道无形剑气接踵而至，射向$n。\n" NOR;
    message_vision(msg, me, target);
    msg = lm_msgs[0][random(3)] + "\n";;
    message_vision(msg, me, target);
    me->set_temp("attack_val", attack_val);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SPECIAL);
    if ((int)target->query("qi") < 0)
        return end_pfm(target, extra, flag);

    msg = lm_msgs[1][random(3)] + "\n";
    message_vision(msg, me, target);
    me->set_temp("attack_val", attack_val);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SPECIAL);
    if ((int)target->query("qi") < 0)
        return end_pfm(target, extra, flag);

    msg = lm_msgs[2][random(3)] + "\n";
    message_vision(msg, me, target);
    me->set_temp("attack_val", attack_val);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SPECIAL);
    if ((int)target->query("qi") < 0)
        return end_pfm(target, extra, flag);

    msg = lm_msgs[3][random(3)] + "\n";
    message_vision(msg, me, target);
    me->set_temp("attack_val", attack_val);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SPECIAL);
    if ((int)target->query("qi") < 0)
        return end_pfm(target, extra, flag);

//天龙派的才能出后两脉，纯天龙才能出第六脉--huacuoh去掉此修改2015/2/14
 // if ( me->query("family/family_name")=="天龙寺" )
 //   {
      msg = lm_msgs[4][random(3)] + "\n";
      message_vision(msg, me, target);
      me->set_temp("attack_val", attack_val);
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SPECIAL);
      if ((int)target->query("qi") < 0)
          return end_pfm(target, extra, flag);
      
//      if ( !me->query("chushi/done") )
  //    {
        msg = lm_msgs[5][random(3)] + "\n";
        message_vision(msg, me, target);
        me->set_temp("attack_val", attack_val);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SPECIAL);
        if ((int)target->query("qi") < 0)
          return end_pfm(target, extra, flag);
    //  }
 //   }
    //恢复combat设置
    //me->set("env/skip_combat",me->query_temp("combat_env"));
    //target->set("env/skip_combat",target->query_temp("combat_env"));
    //me->set("actions", (: call_other, "/kungfu/skill/liumai-shenjian.c", "query_action" :));
    me->add_temp("apply/attack", -extra / 2);
    if (!flag)
        me->add_temp("apply/damage", -extra * 7 / 15);
    else
        me->add_temp("apply/damage", -extra / 3);
    me->add_temp("apply/strength", -extra / 6);
    if (extra < 500)
        me->add("neili", -extra / 2);
    else if (extra > 1500)
        me->add("neili", -1500);
    else
        me->add("neili", -extra);
    me->start_busy(cds - 1 + random(2));
    return 1;
}

