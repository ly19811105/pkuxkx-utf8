// shenghuolin.c
// Writed by yuer
//大挪移的反弹伤害算法调整by yhzzyahoo
#include <ansi.h>
inherit SKILL;

int valid_enable(string usage)
{
	return usage == "parry";
} 
string perform_action_file(string action)
{
        return __DIR__"qiankun-danuoyi/" + action;
}

int valid_learn(object me)
{
	int i, nb, nf, nh, ns, ts;
	nb = (int)me->query_skill("guangming-shenghuogong", 1);
	nf = (int)me->query_skill("force", 1);
	nh = (int)me->query_skill("qiankun-danuoyi", 1);

     if ( nb < 100 || nb <= (nh-20) )
		return notify_fail("你的光明圣火功修为不够，无法领会更高深的乾坤大挪移心法。\n");

	if ( nf < 80)
		return notify_fail("你的基本内功火候还不够，无法领会乾坤大挪移心法。\n");
	if (me->query("family/family_name") != "明教")
			return notify_fail("乾坤大挪移是明教的看家功夫，只有明教弟子才能学习。\n");

	return 1;
}

int valid_study(object me)
{
	if (me->query("family/family_name") != "明教")
			return notify_fail("乾坤大挪移是明教的看家功夫，只有明教弟子才能学习。\n");

	return 1;

}


int practice_skill(object me)
{
	return notify_fail("乾坤大挪移心法只能用学习(learn)或读书(study)来增加熟练度。\n");
}
string *parry_msg = ({
       GRN"只见$n将手中$v左一带，右一带，轻轻的将$N的$w各了开去。\n",
       GRN"$n用手中$v在$N的$w上轻轻一搭，\n$N的$w就如着了魔法一般，荡了开去。\n"NOR,
});

string *unarmed_parry_msg = ({
       GRN"但是$n用左手轻轻一推$N的$w，\n$N的$w就如着了魔法一般，荡了开去。\n",
       GRN"$n左手轻轻推出，拍向$N的$w，$N的攻击被移的无影无踪。\n"NOR,
});

string query_parry_msg(object weapon)
{
        if( weapon )
                return parry_msg[random(sizeof(parry_msg))];
        else
                return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}

//吸收attacker的伤害
//absorb函数的返回值：整数：大于零表示吸收掉的伤害，等于小于零表示吸收失败
//字符串，输出信息
//数组({吸收的伤害,输出信息})

mixed absorb(int ap,int pp,object attacker,object defender,int damage,object weapon)
{
    int jibie,randnum,qdamage,sdamage,rand=random(100);
    float ratio,fix_data; 
    string result = "";

    if(!objectp(attacker) || !objectp(defender)) return 0;
	if (userp(defender)) return -1;//玩家版大挪移和npc版分离了。Zine
    //发动乾坤大挪移
    if(!attacker->query("no_use/qiankun-danuoyi") && living(attacker) && living(defender))
    {
        jibie =(int)defender->query_skill("qiankun-danuoyi",1);
        jibie = jibie * 4 /5;
        randnum = (int)random(ap/2 + pp/2);
        if ( jibie<=400 )
        {
			fix_data=1.2;
          ratio=ap*1.0/pp/800*jibie;
          if ( ratio>1.8 )
          	ratio=1.8;
        }
        else if ( jibie<=800 )
        {
			fix_data=1.4;
        	ratio=ap*0.5/pp+ap*0.5/pp/1300*jibie;
        	if ( ratio>2.7 )
        		ratio=2.7;
        }
        else 
        {	
        	ratio=ap*0.8/pp+ap*0.5/pp/4000*jibie;
			if (jibie<1200)
			{
			fix_data=1.7;
        	if ( ratio>3.5 )
        		ratio=3.5;
			}
			else
			{
				if (jibie<1600)
				{
			  	if ( ratio>4.0 )
        			ratio=4.0;
					fix_data=2.0;
				}
				else
				{
			  	if ( ratio>4.4 )
        			ratio=4.4;
					fix_data=2.4;
				}
  
			}
        }
//当攻击方命中率大幅高于防守方招架率的时候强制性的随机几率下降
        if ( ap/pp>8 )
		{
        	rand=rand*2;
		}
/*		if (defender->is_busy())
		{
			pp*=3/2;
		}
*/
        qdamage = damage*(100+jibie/3)/100;
//重新更改下，对高攻的进行一些针对性压制by yhzzyahoo@pkuxkx
		if (damage > 15000)
		{
       if ( qdamage > 2000+jibie*5/2 )
        	qdamage=2000+jibie*5/2;		
		}
		else
		{
			if (damage < 3000)
			{
				 if ( qdamage > 2000+jibie*4/3 )
        			qdamage=2000+jibie*4/3;
			}
			else
			{
				if (damage < 5000)
				{
				 if ( qdamage > 2000+jibie*3/2 )
        			qdamage=2000+jibie*3/2;
				}
				else
				{
			    if ( qdamage > 2000+jibie*2 )
					qdamage=2000+jibie*2;
				}
			}
		}
//假设攻击方的ap和防守方的pp非常接近来设计几率，
//jibie=400时75%几率反弹，80%几率完全吸收伤害，90%几率吸收一半伤害
//jibie=800时90%几率反弹，95%几率完全吸收伤害，100%几率吸伤一半伤害
//jibie>800时几率的意义就不大了，完全靠10%随机失败几率来控制几率
//设置10%的随机意外，这时候肯定不会出现反弹几率
//by seagate@pkuxkx

        if( randnum < to_int(ceil(pp/2*(fix_data+ratio))) &&
        	  rand>=8 && 
        	  defender->query("neili") > qdamage/15 )
        {
            attacker->receive_damage("qi", qdamage,defender);
            attacker->receive_wound("qi", qdamage/3,defender);
            defender->add("neili", -qdamage/10);
            result += HIR "$n的乾坤大挪移自然激发而出，将$N的攻势反击了回去。\n" NOR;
            result += COMBAT_D->damage_msg(qdamage, "反弹伤");
           if ( objectp(attacker) && objectp(defender) )
              log_file( "static/danuoyi", sprintf("%s:挪移效果：反弹，%s(%s)的ap=%.2fM, %s(%s)的pp=%.2fM, jibie=%d, ratio=%.2f, damage=%d, 反弹伤害=%d\n", 
                 ctime(time()), attacker->query("name"), attacker->query("id"), ap*1.0/1000000, defender->query("name"), defender->query("id"), 
                 pp*1.0/1000000, jibie, ratio, damage, qdamage ) );
            qdamage=0;
            sdamage = damage*9/10;
            defender->set_temp("反震成功",1);
        }
        else if( randnum < to_int(ceil(pp/2*(fix_data+0.8+ratio))) &&
        	       rand>=6 &&
        	       defender->query("neili") > qdamage/20 )
        {
            defender->add("neili", -qdamage/15);
            result += HIC "$n的乾坤大挪移自然激发而出，将$N的攻势移了开去。\n" NOR;
            sdamage = damage*8/10;
            if ( objectp(attacker) && objectp(defender) )
              log_file( "static/danuoyi", sprintf("%s:挪移效果：全吸收，%s(%s)的ap=%.2fM, %s(%s)的pp=%.2fM, jibie=%d, ratio=%.2f, damage=%d, 反弹伤害=%d\n", 
                 ctime(time()), attacker->query("name"), attacker->query("id"), ap*1.0/1000000, defender->query("name"), defender->query("id"), 
                 pp*1.0/1000000, jibie, ratio, damage, qdamage ) );
        }
        else if( randnum < to_int(ceil(pp/2*(fix_data+1.6+ratio))) &&
        	       rand>=4 &&
        	       defender->query("neili") > qdamage/25 )
        {
            defender->add("neili", -qdamage/25);
            sdamage = damage/2;
            result += GRN "$n的乾坤大挪移自然激发而出，将$N的攻势大半移了开去。\n" NOR;
            if ( objectp(attacker) && objectp(defender) )
              log_file( "static/danuoyi", sprintf("%s:挪移效果：半吸收，%s(%s)的ap=%.2fM, %s(%s)的pp=%.2fM, jibie=%d, ratio=%.2f, damage=%d, 反弹伤害=%d\n", 
                 ctime(time()), attacker->query("name"), attacker->query("id"), ap*1.0/1000000, defender->query("name"), defender->query("id"), 
                 pp*1.0/1000000, jibie, ratio, damage, qdamage ) );
        }
        else
        {
         if ( objectp(attacker) && objectp(defender) )
            log_file( "static/danuoyi", sprintf("%s:挪移效果：失败，%s(%s)的ap=%.2fM, %s(%s)的pp=%.2fM, jibie=%d, ratio=%.2f, damage=%d, 反弹伤害=%d\n", 
               ctime(time()), attacker->query("name"), attacker->query("id"), ap*1.0/1000000, defender->query("name"), defender->query("id"), 
               pp*1.0/1000000, jibie, ratio, damage, qdamage ) );	
        	return -1;
        }
        return ({sdamage,result});
    }  
    //未发动挪移
    return -1;
}
int draw_attack(object victim,object attacker,object weapon,int attack_type,string attack_msg)
{
	object the_enemy,*enemy;
	int num,skill,dny,dny_lv;
	if (victim->query("family/family_name") != "明教" && random(3)==0)
	{
		return 0;
	}
	if (userp(victim)&&(victim->query("mingjiao/skill/danuoyi/level")>3||(victim->query("mingjiao/skill/danuoyi/level")>2&&"/kungfu/skill/shenghuo-lingfa.c"->pure_degree(victim)>100)))
	{
		if (victim->is_busy()&&!random(3))
		return 0;
		dny=victim->query_skill("qiankun-danuoyi",1);
		dny_lv=victim->query("mingjiao/skill/danuoyi/level");
		skill=dny/100+dny_lv*dny_lv;
		//3层350级大挪移，指数12，7层2000级大挪移69
		num=random(88+skill);
		if ((num<(75+skill/4)&&"/kungfu/skill/shenghuo-lingfa.c"->pure_degree(victim)<=100)||num<(60+skill/4))
		return 0;
		enemy = victim->query_enemy();
		if (sizeof(enemy)<2)
		{
			if (dny_lv<7)
			return 0;
			else
			{
				message_vision(HIR"$N受$n乾坤大挪移武功影响，进攻全被牵引到别处。\n"NOR,attacker,victim);
				victim->add("neili",-50-random(dny_lv*50));
				return 1;
			}
		}
		enemy-=({attacker});
		the_enemy=enemy[random(sizeof(enemy))];
        if (living(the_enemy))
		{	
			message_vision(HIR"$N受$n乾坤大挪移武功影响，进攻全被牵引到"+the_enemy->query("name")+"身上。\n"NOR,attacker,victim);
            the_enemy->set_temp("do_attack_from", victim);
			COMBAT_D->do_attack(attacker,the_enemy,weapon,attack_type,attack_msg);
            the_enemy->delete_temp("do_attack_from");
			victim->add("neili",-100-random(dny_lv*50));
			return 1;
			
		}
		return 0;
	}
	return 0;
}
