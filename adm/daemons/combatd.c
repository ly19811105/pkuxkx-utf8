// combatd.c
//Leon Modified 97-12-1
//对年龄在15岁以下的player,被杀只降很少exp,potential
//#pragma optimize all
//draw_attack改为定义在功夫本身，zine@pkuxkx 2013/5/1,且优先于dodge判断。
#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>
#include <localtime.h>

inherit F_DBASE;
#include <combat/message.h>     //战斗信息显示有关的所有设定
#include <combat/probable.h>    //战斗命中率、防御命中率等几率相关函数
#include <combat/reward.h>      //战斗结束以后奖励相关的所有函数
#include <combat/learn.h>       //战斗过程中获得增益的相关函数
#include <combat/skill.h>       //战斗过程中和技能相关的函数
#include <combat/autofight.h>   //自动触发战斗有关的所有接口函数
#include <combat/equip.h>       //战斗中装备特效相关的所有函数
#include <combat/damage.h>      //战斗过程中和伤害计算相关的函数

string  absorb_skill;
string msg;
int absorb_vic;
int qdamage;
int jibie;
int randnum;

mapping family_dodgeskill = ([
	"datengnuo-bufa":"明教",
    "jinyan-gong":"全真派", 
    "shaolin-shenfa":"少林派",
    "zhutian":"峨嵋派",
    "xiaoyaoyou":"丐帮",
    "yanyi-shenfa":"雪山派",
    "huashan-shenfa":"华山派",
    "lingbo-weibu":"天龙寺",
    "duanshi-shenfa":"天龙寺",
    "tiyunzong":"武当派",
    "feitian-shenfa":"日月神教",
	"pixie-jian":"日月神教",
    "xianyun":"古墓派",
    "yanling-shenfa":"姑苏慕容",
	"luoying-shenfa":"桃花岛",
	"chanchu-bufa":"白驼山",
	"yuxue-dunxing":"大轮寺",
	"yueying-wubu":"灵鹫宫",
	"yixingbu":"神龙教",
	"lingding-piao":"天地会",
	"zhaixinggong":"星宿派",
]);


void create()
{
    seteuid(getuid());
    set("name", "战斗精灵");
    set("id", "combatd");
}

// do_attack()
//
// Perform an attack action. This function is called by fight() or as an
// interface for some special utilize in quests.
//
//attack_type
//  TYPE_REGULAR 普通攻击模式
//  TYPE_QUICK   反击模式，理论上来说这个反击模式会额外有命中加成，但是目前没有，暂时不建议修改，因为有些技能采用TYPE_QUICK模式进行调用
//  TYPE_RIPOSTE 反击模式 
//  TYPE_SPECIAL 特殊攻击模式，三个命中算法（ap，dp，pp）将由外部提供，不需要依赖于combatd中的命中率算法
//               这部分临时数据设置在attacker的query_temp("attack_val")下的ap,dp,pp属性中 
//               也就是说当该模式的时候只要attack_val属性中配置了ap，dp，pp命中数据，则直接用该数据作为命中判断依据，而不需要依赖于默认命中率算法
varargs int do_attack(object me, object victim, object weapon, int attack_type, string attack_msg)
{
	mapping my, your, action, attval, tact, force_effect;
	string limb, *limbs, result ,skill_action;
	string attack_skill, force_skill, martial_skill, dodge_skill, parry_skill, iron_skill,retort_skill;
	mixed foo;
	object report_ob, ob, armor;
	int ap, dp, pp;
	int damage;
	int wounded = 0;
	int i = 0;
	int atype; //攻击模式
	int dgap;  //纯门派轻功躲闪反击概率
	int do_attack_result = 0; // 战斗结果标记，0 命中；1 躲闪了；2 招架了
	mixed ret;

	if(!me || !victim ||  environment(me) != environment(victim))
		return 1;
	if (!living(me))
		return 1; // iszt@pkuxkx, 2007-03-13
	/*if (draw_attack(victim,me,weapon,attack_type,attack_msg)==1)
	return 1;*/
	my = me->query_entire_dbase();
	your = victim->query_entire_dbase();	
	
	atype=attack_type;
	//特殊攻击模式获取外部传入参数，并且对外部传入区域设置攻击模式
	if ( atype==TYPE_SPECIAL )
	{
        attval = me->query_temp("attack_val");
        if ( mapp(attval) && attval["attack_type"]!=TYPE_SPECIAL )
            attval["attack_type"]=TYPE_SPECIAL;
        if ( !mapp(attval) )
            atype=TYPE_QUICK;
    }

    //Choose skills.
    if( atype==TYPE_SPECIAL && mapp(attval) && mapp(attval["skill"]) && mapp(attval["base"]) )
    {
        if ( objectp(weapon) && (weapon == me->query_temp("weapon")) && 
             stringp(attval["base"]["weapon"]) && stringp(attval["skill"]["weapon"]) )
        {
            attack_skill = attval["base"]["weapon"];
            martial_skill = attval["skill"]["weapon"];
            if ( !mapp(attval["skill_action"]) || !stringp(attval["skill_action"]["weapon"]) )
                skill_action = attval["skill"]["weapon"];
            else
                skill_action = attval["skill_action"]["weapon"];
        }
        else if ( !me->query_temp("weapon") && 
              stringp(attval["base"]["no_weapon"]) && stringp(attval["skill"]["no_weapon"]) )
        {
            attack_skill = attval["base"]["no_weapon"];
            martial_skill = attval["skill"]["no_weapon"];
            if ( !mapp(attval["skill_action"]) || !stringp(attval["skill_action"]["no_weapon"]) )
                skill_action = attval["skill"]["no_weapon"];
            else
                skill_action = attval["skill_action"]["no_weapon"];
        }
        else
            return 0;
    }

    if ( !stringp(skill_action) || file_size(SKILL_D(skill_action)+".c") <= 0 
         || !stringp(attack_skill) || !stringp(martial_skill) )
    {
        attack_skill = choose_attack_skill(me,weapon);
        martial_skill = me->query_skill_mapped(attack_skill);	
    }

	//
	// (1) Find out what action the offenser will take.
	//
	me->reset_action();
	action = me->query("actions");
	if( !mapp(action) ) 
    {
		//      me->reset_action();
		action = me->query("actions");
	}
	
	//特殊攻击模式，如果定义了attack_skill技能，则以该技能作为攻击技能
    if ( atype==TYPE_SPECIAL && stringp(skill_action) )
    {
        if ( find_object(SKILL_D(skill_action)) || file_size(SKILL_D(skill_action)+".c") > 0 )
        {
            tact = call_other(SKILL_D(skill_action), "query_action", me, weapon);
            if ( mapp(tact) ) action=tact;
        }
    }
	
    if( !mapp(action) ) {
        CHANNEL_D->do_channel( this_object(), "sys",
            sprintf("%s(%s): bad action = %O act:%d weapon:%O",
            me->name(1), me->query("id"), me->query("actions", 1), attack_type, weapon));
        return 0;
    }

    //加入暗器，在工夫里把action写成skip_action就会忽略原来的战斗系统，
	//调用功夫里的hit_ob,加入新暗器可以参照/kungfu/skill/guishoushe.c。
	//iszt@pkuxkx: 不一定限于暗器
	if(action["action"]=="skip_action")
	{
		return anqi_attack(me,victim,martial_skill);
	}
	
	//
	// (2) Prepare AP, DP for checking if hit.
	//
	limbs = victim->query("limbs");
	limb = limbs[random(sizeof(limbs))];
	
	if (me->query_temp("action_flag") == 0)
		result = "\n" + action["action"] + "！\n" + NOR;
	else
		result = "\n" + "紧跟着"+action["action"] + "！\n";
	
	if( stringp(attack_msg) ) 
    {
        result = "\n" + attack_msg + "\n";
        if ( atype == TYPE_SPECIAL )
        {
            /* perform的攻击中如存在attack_msg信息则显示，不会被屏蔽 */
            result = replace_string( result, "$l", limb );
            if( victim->query_temp("weapon")) result = replace_string( result, "$v", victim->query_temp("weapon")->name() );
            if( objectp(weapon)) result = replace_string( result, "$w", weapon->name() );
            else if( stringp(action["weapon"]) ) result = replace_string( result, "$w", action["weapon"] );
            else if( attack_skill == "finger" ) result = replace_string( result, "$w", "手指" );
            else if( attack_skill == "strike" ) result = replace_string( result, "$w", "手掌" );
            else result = replace_string( result, "$w", "拳头" );
            message_vision(result, me, victim);
            result = "";
        }
    }
	
	//特殊攻击模式，可以直接传入ap、dp、pp作为攻击的命中算法，也可以传入ap_factor, dp_factor, pp_factor适当调整命中百分比
	if ( mapp(attval) &&
	     atype==TYPE_SPECIAL &&
	     attval["ap"] && 
	     attval["dp"] &&
	     attval["pp"] )
	  ap=attval["ap"];
	else
	{       
	  ap = skill_power(me, attack_skill, SKILL_USAGE_ATTACK,victim);
	  ap = ap_factor(ap,me,victim);
	  if ( mapp(attval) &&
	       atype==TYPE_SPECIAL &&
	       floatp(attval["ap_factor"]) &&
	       attval["ap_factor"]>=0.01 &&
	       attval["ap_factor"]<=10.0 )
	  {
	    ap=to_int(ceil(ap*attval["ap_factor"]));
	    if ( !ap )
	      ap=1;
	  }
  }
  
  if(ap<0) 
  {
  	log_file( "wiz/combatd", sprintf("\n%s\n异常数据（攻击命中率溢出）：计算目标：%s(%s)，对方：%s(%s), 类型：%s，命中率修正系数：%.2f，命中：%d\n", 
  	  ctime(time()), me->query("name"), me->query("id"), victim->query("name"), victim->query("id"), attack_skill, victim->query_temp("combat_factor"), ap ) );
  	ap=2100000000;
  }
	
	if (userp(me) && intp(action["dodge"]))
		me->set_temp("fight/dodge", action["dodge"]);

  //特殊攻击模式，可以直接传入ap、dp、pp作为攻击的命中算法，也可以传入ap_factor, dp_factor, pp_factor适当调整命中百分比
	if ( mapp(attval) &&
	     atype==TYPE_SPECIAL &&
	     attval["ap"] && 
	     attval["dp"] &&
	     attval["pp"] )
	  dp=attval["dp"];
	else	
	{
	  dp = skill_power(victim, "dodge", SKILL_USAGE_DEFENSE,me);
    if ( mapp(attval) &&
	       atype==TYPE_SPECIAL &&
	       floatp(attval["dp_factor"]) &&
	       attval["dp_factor"]>=0.01 &&
	       attval["dp_factor"]<=10.0 )
	  {
	    dp=to_int(ceil(dp*attval["dp_factor"]));
	    if ( !dp )
	      dp=1;
	  }
	}

	
	if( dp < 1 ) dp = 1;
	
	if(wizardp(me))
	{
		tell_object(me, sprintf("%s:ap%d,%s:dp%d\n",me->query("name"),ap,victim->query("name"),dp));
	}

	if(wizardp(victim))
	{
		tell_object(victim, sprintf("%s:ap%d,%s:dp%d\n",me->query("name"),ap,victim->query("name"),dp));
	}
	//
	// (3) Fight!
	//     Give us a chance of AP/(AP+DP) to "hit" our opponent. Since both
	//     AP and DP are greater than zero, so we always have chance to hit
	//     or be hit.
	//
	dodge_skill = victim->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
	parry_skill = victim->query_skill_mapped("parry");
		if( !parry_skill ) parry_skill = "parry";
	if (SKILL_D(parry_skill)->draw_attack(victim,me,weapon,atype,attack_msg)==1)
	return 1;
  ret = SKILL_D(dodge_skill)->dodge(ap,dp,me,victim);//试着用武功自己的dodge去闪躲
  if(stringp(ret) || ret > 0)//轻功技能的特殊闪躲
	{	
    if(!stringp(ret))
    {
      result += SKILL_D(dodge_skill)->query_dodge_msg(limb);	
    }
    else
    {
      result += ret;
    }
		damage = RESULT_DODGE;
	}
  else if (ret == 0 && random(ap/2 + dp/2) < dp/2)// 一般性闪躲
  {
  //ret == 0,证明该轻功没定义dodge方法
  //凡是定义了dodge方法的，不可以再判断一次闪躲。
		result += SKILL_D(dodge_skill)->query_dodge_msg(limb);	
		damage = RESULT_DODGE;    
  }

  if(damage == RESULT_DODGE) 
  {
	do_attack_result = 1;  // 1 表示躲闪了
    learn_from_combat(me,victim,"dodge",ap,dp,my,your,attack_skill);
  }
  else
	{
		//
		//	(4) Check if the victim can parry this attack.
		//
		//特殊攻击模式，可以直接传入ap、dp、pp作为攻击的命中算法，也可以传入ap_factor, dp_factor, pp_factor适当调整命中百分比
		if ( mapp(attval) &&
	       atype==TYPE_SPECIAL &&
	       attval["ap"] && 
	       attval["dp"] &&
	       attval["pp"] )
	    pp=attval["pp"];
	  else 
	  {
		  pp = skill_power(victim, "parry", SKILL_USAGE_DEFENSE,me);
		  pp = pp_factor(pp,me,victim,weapon);
      if ( mapp(attval) &&
	         atype==TYPE_SPECIAL &&
	         floatp(attval["pp_factor"]) &&
	         attval["pp_factor"]>=0.01 &&
	         attval["pp_factor"]<=10.0 )
	    {
	      pp=to_int(ceil(pp*attval["pp_factor"]));
	      if ( !pp )
	        pp=1;
	    }
		}

    if(pp<0) 
    {
  	  log_file( "wiz/combatd", sprintf("\n%s\n异常数据（招架命中率溢出）：计算目标：%s(%s)，对方：%s(%s), 类型：parry，攻击者持有武器：%s，防御者持有武器：%s，命中：%d\n", 
  	    ctime(time()), me->query("name"), me->query("id"), victim->query("name"), victim->query("id"), (weapon?"是":"否"), (victim->query_temp("weapon")?"是":"否"), pp ) );
  	  pp=2100000000;
    }
	ret = find_skill(parry_skill)->parry(ap,pp,me,victim);//试着用武功自己的特殊parry去招架。
    if(stringp(ret) || ret > 0)
    {
        if(!stringp(ret))
        {
            ret = find_skill(parry_skill)->query_parry_msg(victim->query_temp("weapon"));	
            if(!stringp(ret)) 
              ret = SKILL_D("parry")->query_parry_msg(victim->query_temp("weapon"));
        }
        
        result += ret;         
        damage = RESULT_PARRY;
    }
    else if( ret == 0 && random(ap/2 + pp/2)< pp/2 )
    {
        foo = find_skill(parry_skill)->query_parry_msg(victim->query_temp("weapon"));
        if(!stringp(foo))
            foo = SKILL_D("parry")->query_parry_msg(victim->query_temp("weapon"));
        result += foo;
        damage = RESULT_PARRY;
    }

    /* 分段显示战斗信息 */
    result = replace_string( result, "$l", limb );
    if( victim->query_temp("weapon")) result = replace_string( result, "$v", victim->query_temp("weapon")->name() );
    if( objectp(weapon)) result = replace_string( result, "$w", weapon->name() );
    else if( stringp(action["weapon"]) ) result = replace_string( result, "$w", action["weapon"] );
    else if( attack_skill == "finger" ) result = replace_string( result, "$w", "手指" );
    else if( attack_skill == "strike" ) result = replace_string( result, "$w", "手掌" );
    else result = replace_string( result, "$w", "拳头" );
    combat_msg(result, 0, me, victim);
    report_status(victim);
    result = "";

    if(damage == RESULT_PARRY)
    {
		do_attack_result = 2;  // 2 表示招架了
        weapon_clash(weapon,me,victim);//武器磨损
        learn_from_combat(me,victim,"parry",ap,dp,my,your,attack_skill);//战斗中获取经验，潜能和技能
    }
    else 
    {
    //
    //	(5) We hit the victim and the victim failed to parry
    //

    foo = calc_damage(me,victim,weapon,my,your,action);
    if(arrayp(foo))
    {
        damage = foo[0];
        result += foo[1];
    }
    if (strwidth(result))
    {
        /* 分段显示战斗信息 */
        combat_msg(result, 0, me, victim);
        report_status(victim);
        result = "";
    }

    //伤害已经计算完毕，接下来分为三步：伤害前，伤害，伤害后
    //乾坤大挪移，铁布衫，目前都属于伤害前生效的功夫，可以反弹，可以吸收伤害。要求都必须是招架。
    //伤害后的功夫，意思就是反击。

        //
        //	(5.5) Check if victim can absorb the damage
        //

    //absorb函数的返回值：整数：大于零表示吸收掉的伤害，等于小于零表示吸收失败
    //字符串，输出信息
    //数组({吸收的伤害,输出信息})
	if (!me->query_temp("apply/cannot_be_absorbed")
		&& !me->query_temp("apply/invalid_target_special")) // 添加参数：某些攻击使对手的大挪移失效 by lordstar 20180108
	{
    ret = find_skill(parry_skill)->absorb(ap,pp,me,victim,damage,weapon);//试着用武功自己的特殊parry去吸收伤害
    if(intp(ret) && ret > 0)
    {
        damage -= ret;
    } 
    else if(stringp(ret))
    {
        result += ret;
    }
    else if(arrayp(ret) && sizeof(ret) == 2 && intp(ret[0]) && stringp(ret[1]))
    {
        damage -= ret[0];
        result += ret[1];
    }
	}
    else ret=0;
    //如果不存在大挪移效果，则触发铁布衫效果
    if ( ret==0 && 
	   !me->query_temp("apply/cannot_be_absorbed") && 
	   !me->query_temp("apply/invalid_target_special") &&
       victim->query_skill("iron-cloth") && 
       !me->query("no_use/iron-cloth") && 
       living(me) && 
       living(victim) )
    {
        iron_skill=victim->query_skill_mapped("iron-cloth");
        if ( !iron_skill )
            iron_skill="iron-cloth";

        ret = find_skill(iron_skill)->absorb(ap,pp,me,victim,damage,weapon);//试着用硬功自己的特殊效果去吸收伤害
        if(intp(ret) && ret > 0)
        {
            damage -= ret;
        } 
        else if(stringp(ret))
        {
            result += ret;
        }
        else if(arrayp(ret) && sizeof(ret) == 2 && intp(ret[0]) && stringp(ret[1]))
        {
            damage -= ret[0];
            result += ret[1];
        }
    }

    /* 显示反弹伤害效果数值 */
    if( stringp(result) && strwidth(result)>0 )
    {
        /* 分段显示战斗信息 */
        combat_msg(result, 2, me, victim);
        report_status(me);
        result = "";
    }
      
    if ( damage<0 ) damage = 0 - damage;	
    if ( damage>0 )
    {
        //
        //	(6) Inflict the damage.
        //
		if (me->query_temp("apply/PoisonAttack")&&mapp(me->query_temp("apply/PoisonAttack")))
		if (weapon&&me->query_temp("apply/PoisonAttack")["type"]=="weapon"||
			!weapon&&me->query_temp("apply/PoisonAttack")["type"]=="unarmed"||
			me->query_temp("apply/PoisonAttack")["type"]=="all")
			{
				if (wizardp(me)) tell_object(me,"普通带毒攻击。\n");
				F_POISON->poison_attack(me,victim,me->query_temp("apply/PoisonAttack")["id"],me->query_temp("apply/PoisonAttack")["dur"]);
			}
		
		// 增加内功吸收物理伤害检查接口
		if (force_skill = victim->query_skill_mapped("force"))
		{
			if (mapp(force_effect = SKILL_D(force_skill)->absorb(victim, me, "qi", damage, 0, "Attack") ))
			{
				if (force_effect["damage"]>0)
				{
					if (damage>force_effect["damage"])
						damage -= force_effect["damage"];
					else 
						damage = 0;
				}
				if (force_effect["eff_msg"])
					message_vision( force_effect["eff_msg"], victim, me);
			}
		}
		
		if (damage>0)
		{
			damage = victim->receive_damage("qi", damage, me );

			if( random(damage) > (int)victim->query_temp("apply/armor")
            && ( (me->is_killing(victim->query("id")))
            && ((!weapon) && !random(4) || weapon && !random(2) )
            || ( (!weapon) && !random(7) || weapon && !random(4) ) )  )
			{
            // We are sure that damage is greater than victim's armor here.
				victim->receive_wound("qi",damage - (int)victim->query_temp("apply/armor"), me);
				wounded = 1;
			}
		
			result += damage_msg(damage, action["damage_type"]);
		}
    }
			
      //victim反击的机会，乾坤大挪移，铁布衫不属于此类。这里是专指挨打以后的反击。
      //挪移和铁布衫自己不挨打。类似的，可以在这里增加调用武器的反击接口，不过
      //对武侠类的mud，武器自己反击有点说不过去，还是技能反击比较合理。当然，
      //技能的retort函数里，可以配合武器来做些事。
      //retort_skill = choose_attack_skill(victim,victim->query_temp("weapon"));
      //应该是取defender的反击技能，而不是attacker的反击技能，而且应该造成伤害以后才能反击，否则
      //反击没有任何意义了，并在retort接口中增加damage输入，目前retort接口定义如下：
      //mixed retort(int ap, int pp, object attacker, object defender, int damage, object weapon)
      //理论上来说某些特殊的硬功应该是具有防御反击功能，也就是说不仅仅调用防御者攻击技能的防御反击，
      //目前暂时先设置成调用攻击技能的防御反击功能，以后有实际需求再调整。
      // by seagate@pkuxkx 2012/12/31
  /*先注释掉此功能，以后再测试
      if( martial_skill = victim->query_skill_mapped(retort_skill) &&
      	  damage>0 && 
      	  objectp(find_skill(martial_skill)) )
      {
          ret = find_skill(martial_skill)->retort(ap,pp,me,victim,damage,weapon);
          if(stringp(ret)) 
          	result += ret;
      }*/
      			
			//
			//	(7) Give experience
			//
			//Give exp and pot
      learn_from_combat(me,victim,"hit", dp,ap,my,your,attack_skill);
		}
	}
	
    /* 分段显示战斗信息,damage_msg中有$l需要转换,大挪移中含有$v $w需要转换 */
    result = replace_string( result, "$l", limb );
    if( victim->query_temp("weapon")) result = replace_string( result, "$v", victim->query_temp("weapon")->name() );
    if( objectp(weapon)) result = replace_string( result, "$w", weapon->name() );
    else if( stringp(action["weapon"]) ) result = replace_string( result, "$w", action["weapon"] );
    else if( attack_skill == "finger" ) result = replace_string( result, "$w", "手指" );
    else if( attack_skill == "strike" ) result = replace_string( result, "$w", "手掌" );
    else result = replace_string( result, "$w", "拳头" );
    combat_msg(result, 0, me, victim);
    report_status(victim);

	if (victim->query_temp("反震成功"))
	{
		victim->set_temp("反震成功", 0);
	}
	if( (wizardp(victim) || wizardp(me)) && ( (string)me->query("env/combat")=="verbose"  ||(string)victim->query("env/combat")=="verbose" )) {
		wizardp(victim)?report_ob=victim:report_ob=me;
		if( damage > 0 )
			tell_object(report_ob, sprintf( GRN "AP：%d，DP：%d，PP：%d，伤害力：%d\n" NOR,
			ap/100, dp/100, pp/100, damage));
		else
			tell_object(report_ob, sprintf( GRN "AP：%d，DP：%d，PP：%d\n" NOR,
			ap/100, dp/100, pp/100));
	}

	if( damage > 0 )
	{
		if( victim->is_busy() ) victim->interrupt_me(me);
		if( (!me->is_killing(your["id"])) &&
			(!victim->is_killing(my["id"])) &&
			victim->query("qi")*2 <= victim->query("max_qi"))
		{
			me->remove_enemy(victim);
			victim->remove_enemy(me);
			message_vision( winner_msg[random(sizeof(winner_msg))], me, victim);
//门忠战胜任务完成标志
			if(me->query("quest/type") == "win"
				&& me->query("quest/name") == victim->name(1)
				&& !userp(victim))
				me->set("quest/finish",1);
			winner_reward(me, victim);
		}
	}
	
	if( functionp(action["post_action"]) )
		evaluate( action["post_action"], me, victim, weapon, damage);

// 添加成功躲闪和成功招架之后的函数调用，可以在这里增加一些额外的玩法。by lordstar 20171102
  if (do_attack_result == 1)  // 成功躲闪，且攻击者没有携带“无法反击”标记
  {
	// 纯门派且使用本门轻功成功躲闪后有概率反击，导致攻击者busy。 by lordstar 20171102
	if ( !me->query_temp("apply/invalid_dodge_counter")
	    && !me->query_temp("apply/invalid_target_special")
  	    && !victim->query("env/no_dodge_strike")
        && (int)victim->query("purefamily/level") >= 2 
		&& victim->query("family/family_name") == victim->query("purefamily/family_name")
		&& family_dodgeskill[dodge_skill] 
		&& victim->query("purefamily/family_name") == family_dodgeskill[dodge_skill] ) 
	{
		dgap = (int)SKILL_D(dodge_skill)->query_counter_rate(victim, me, attack_skill);
		if (dgap<=0) dgap= 10;// 最大不要超过 A+，默认概率 D+
		if (victim->is_busy()) dgap += 2;
		if (F_KUNGFU->hit_rate(victim->query_skill("dodge"), me->query_skill("dodge"), dgap, victim, me))
		{
			ret = SKILL_D(dodge_skill)->query_counter_msg(victim, me, attack_skill);
			if (stringp(ret) && strwidth(ret)>0)
				result = ret;
			else 
				result = HIW"$n躲闪成功，趁势发动反击，$N一时之间被攻了个措手不及！\n"NOR;
			message_vision( result, me , victim );
			dgap = (int)SKILL_D(dodge_skill)->query_counter_duration(victim, me);
			if (dgap<=0) dgap= 3; // 默认值 busy 3 秒
			me->start_busy(dgap);
		}
	}
  // 如果技能定义了该函数，在成功躲闪之后可以提供额外效果。
	SKILL_D(dodge_skill)->after_dodge(victim, me, attack_skill);
  // 如果攻击技能定义了该函数，在被对手成功躲闪之后可以提供额外效果。
	if (stringp(martial_skill))
		SKILL_D(martial_skill)->after_victim_dodge(me, victim, attack_skill);	  
  }
  else if (do_attack_result == 2)  
  {
  // 成功招架，且攻击者没有携带“无法反击”标记
  // 如果技能定义了该函数，在成功招架之后可以提供额外效果。
	if( !me->query_temp("apply/invalid_parry_counter") 
		&& !me->query_temp("apply/invalid_target_special") )
		SKILL_D(parry_skill)->after_parry(victim, me, attack_skill);	  
  // 如果攻击技能定义了该函数，在被对手成功招架之后可以提供额外效果。
	if (stringp(martial_skill))
		SKILL_D(martial_skill)->after_victim_parry(me, victim, attack_skill);
  }
  else // 命中了对手
  {
	  if (stringp(martial_skill))
		SKILL_D(martial_skill)->after_hit(me, victim, attack_skill, damage);	  
  }

  //战斗结束后对于YPE_SPECIAL模式战斗，清除本次战斗的临时输入参数
  if ( attack_type==TYPE_SPECIAL )
	  me->delete_temp("attack_val");
	
	// See if the victim can make a riposte.
	if( atype==TYPE_REGULAR
		&&	damage < 1
		&&	victim->query_temp("guarding") )
	{
		victim->set_temp("guarding", 0);
		if( random(my["dex"]) < 5 ) {
			combat_msg("$N一击不中，露出了破绽！\n",1, me);
			do_attack(victim, me, victim->query_temp("weapon"), TYPE_QUICK);
		} else {
			combat_msg("$N见$n攻击失误，趁机发动攻击！\n",1, victim, me);
			do_attack(victim, me, victim->query_temp("weapon"), TYPE_RIPOSTE);
		}
	}
	
	return damage;
}

//	fight()
//
//	This is called in the attack() defined in F_ATTACK, which handles fighting
//	in the heart_beat() of all livings. Be sure to optimize it carefully.
//
void fight(object me, object victim)
{
	object weapon, focus, room;
	int n,i;
	int spd, hubo, hubei, pspd, turn;
	
	if( !living(me) || me->query_temp("combat_yield"))
		return;
	
// 让NPC可以通过定义 choose_offensive_target() 函数来自主确定他的攻击目标  lordstar 20180511
	if (!userp(me) && objectp(focus = me->choose_offensive_target()))
		victim = focus;
	else {
// 增加设置焦点目标的功能，有焦点目标时，只攻击焦点目标。by lordstar 20171108
		focus = me->query_temp("focus_target");
		if ( objectp(focus) && environment(focus)==environment(me) && me->visible(focus) && me->is_fighting(focus) )
			victim = focus;
	}
	//iszt@pkuxkx, 2007-03-14, what is "perception"? changed to huyou-wiz
	if( !me->visible(victim) )
		return;
	
	hubo=is_hubo(me);
	hubei=is_hubei(me);
	weapon=me->query_temp("weapon");
	spd=attack_speed(me,weapon,hubo,hubei);	
	
	pspd=me->query_temp("fight/speed");
	pspd+=spd;
	n=pspd/100;
	me->set_temp("fight/speed", pspd-n*100);
	if ( wizardp(me) && me->query("env/combat")=="verbose")
	{
		tell_object(me, sprintf("攻击速度：%d, 残留攻击速度：%d, 攻击次数：%d\n", spd, me->query_temp("fight/speed"), n));
		tell_object(me, sprintf(GRN"本人出招命中信息：对方身法值[%d], 本方臂力值[%d]\n"NOR,
			      victim->combat_dex(), me->combat_str() ) );
  }
	
	if ( wizardp(victim) && me->query("env/combat")=="verbose")
	{
		tell_object(victim, sprintf("对方攻击速度：%d, 残留攻击速度：%d, 攻击次数：%d\n", spd, me->query_temp("fight/speed"), n));
		tell_object(victim, sprintf(GRN"对方出招命中信息：本方身法值[%d], 对方臂力值[%d]\n"NOR,
			      victim->combat_dex(), me->combat_str() ) );
	}
  
	room = environment(me);
	turn = time();
	for (i=0;i<n;i++)
	{
		// 增加一个功能接口：某些房间如果定义了 prevent_combat_attack() 函数并且返回非零值，就抵消一轮攻击。
		// 这可用于某些特殊的用途，比如圣火令法提供了大量攻速，使得一个回合可以出很多招，可以通过定义房间的 p_c_a() 来限制
		// 在这个房间里的战斗每个回合最多出招数（其中参数 i 表示当前是第几轮攻击，可在 p_c_a() 中判断 i 大于某个值就返回1）
		// turn 参数通过系统时间作为当前战斗所发生的回合标记。同一个 turn 的 p_c_a() 调用可视为同一个回合的战斗
		// lordstar 20180522
		if (objectp(room) && room->prevent_combat_attack(me, victim, i, turn))
			continue;
		// If victim is busy or unconcious, always take the chance to make an attack.
		if( victim->is_busy() || !living(victim) ) {
			me->set_temp("guarding", 0);
			//		if( !victim->is_fighting(me) ) victim->fight_ob(me);
			//Pal修改，可能有bug，请大家注意^_^
			if( !victim->is_fighting(me) && i==n-1 ) 
			{
				victim->fight_ob(me);
			}
			
			if ( i%2 == 1 &&
				   ( hubo || hubei==1 ) )
			{
			  hubo_attack(me,victim);
			}
			else if ( i%2 == 1 && 
				 !hubo && hubei==2  )
			{
        me->set_temp("action_flag",1);
        do_attack(me, victim, me->query_temp("weapon"), TYPE_QUICK);
        me->set_temp("action_flag",0);
			}
			else
				do_attack(me, victim, me->query_temp("weapon"), TYPE_QUICK);
// Else, see if we are brave enough to make an aggressive action.
//		} else if( random( (int)victim->combat_dex() * 3 ) > (int)me->combat_str()) {
// 按原设计（上一行备注），攻击比自己弱小得多的对手反而无法出招了，不合理，改掉！by lordstar 20171108
		} else if( random( (int)victim->combat_dex() * 2 ) < (int)me->combat_str()) {
			me->set_temp("guarding", 0);
			if( !victim->is_fighting(me) && i==n-1 ) victim->fight_ob(me);
				
			if ( i%2 == 1 &&
				   ( hubo || hubei==1 ) )
			{
			  hubo_attack(me,victim);
			}
			else if ( i%2 == 1 && 
				 !hubo && hubei==2  )
			{
        me->set_temp("action_flag",1);
        do_attack(me, victim, me->query_temp("weapon"), TYPE_QUICK);
        me->set_temp("action_flag",0);
			}
			else
				do_attack(me, victim, me->query_temp("weapon"), TYPE_REGULAR);
				// Else, we just start guarding.
		} else if( !me->query_temp("guarding") ) {
			me->set_temp("guarding", 1);
			combat_msg( guard_msg[random(sizeof(guard_msg))],1, me, victim);
			return;
		} else return;
	} // enclose of hubo
}