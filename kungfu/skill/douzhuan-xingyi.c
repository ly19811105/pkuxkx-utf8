// douzhuan-xingyi 斗转星移
#include <ansi.h>
inherit SKILL;

string *parry_msg = ({
YEL"蓦地里一股力道飞来，将$n"YEL"一引一带，$n"YEL"身子轻轻越起，身行落在一旁\n"NOR,
BLU"$n"BLU"当下一股内力冲向$l，$N"BLU"击向$n"BLU"的$l的招数莫名奇妙的溜滑向一旁\n"NOR,
HIW"$n"HIW"双手前探，左臂搭上$N"HIW"右臂，右臂使出$N"HIW"的招数将$N"HIW"此招化去\n"NOR,
HIY"$n"HIY"星移斗转，$N"HIY"这招莫名其妙的在中途转了方向，直奔自己袭来\n"NOR,
YEL"$n"YEL"作壁上观，双手与对方相交数掌，谈笑间竟使出$N"YEL"成名技艺，使得$N"YEL"不知如何是好\n"NOR,
BLU"$n"BLU"凝神运气向$N"BLU"猛攻快打，使出的招数好似$N"BLU"的成名绝技，把$N"BLU"的招数化于无形\n"NOR,
HIW"只见$n"HIW"身如飘风，恰似漫天星移，诡异地一式，双掌动向无定不可捉摸地拍向$N"HIW"的$l\n"NOR,
HIY"$n"HIY"身行飘忽不定，在星移斗转之间反用$N"HIY"的招数击向$N"HIY"，令$N"HIY"百思不得其解\n"NOR,
});

int valid_enable(string usage)
{
        return usage == "parry";
}

int valid_learn(object me)
{ 
        // 叛师无法学习改慕容绝学，jpei
        if (me->query("betrayer") > 0)
                return notify_fail("由于你背叛师门，无法领悟斗转星移精髓。\n");
        if (me->query_skill("douzhuan-xingyi",1) < 300)
                return notify_fail("斗转星移初期只能通过研读图谱学习。\n");
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("学习斗转星移必须空手。\n");
        if ((int)me->query_skill("shenyuan-gong", 1) < 80)
                return notify_fail("你的神元功火候不够，无法学斗转星移。\n");
        return 1;
}

int practice_skill(object me)
{
        return notify_fail("斗转星移只能通过学习来提高，无法通过练习来提高。\n");
}

string perform_action_file(string action)
{
        return __DIR__"douzhuan-xingyi/" + action;
}

string *unarmed_parry_msg = ({
        "但是被$p格开了。\n",
        "结果被$p挡开了。\n",
});

string query_parry_msg(object weapon)
{
        return parry_msg[random(sizeof(parry_msg))];
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
	if (!defender->query_temp("zhen-douzhuan")) return -1;//没有发动pfm，没有反弹
    //发动斗转反弹
    if(!attacker->query("no_use/zhen-douzhuan") && living(attacker) && living(defender))
    {
        jibie =(int)defender->query_skill("douzhuan-xingyi",1);
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
            defender->add("neili", -qdamage/15);
            result += HIR "$n已有准备，运起慕容家成名绝技--斗转星移，将$N的攻击反击了回来。\n" NOR;
            result += COMBAT_D->damage_msg(qdamage, "反弹伤");
           if ( objectp(attacker) && objectp(defender) )
              log_file( "static/douzhuan", sprintf("%s:斗转效果：反弹，%s(%s)的ap=%.2fM, %s(%s)的pp=%.2fM, jibie=%d, ratio=%.2f, damage=%d, 反弹伤害=%d\n", 
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
            defender->add("neili", -qdamage/20);
            result += HIC "$n闭目凝神，气走全身，身形飘逸，将$N的攻势移了开去。\n" NOR;
            sdamage = damage*8/10;
            if ( objectp(attacker) && objectp(defender) )
              log_file( "static/douzhuan", sprintf("%s:斗转效果：全吸收，%s(%s)的ap=%.2fM, %s(%s)的pp=%.2fM, jibie=%d, ratio=%.2f, damage=%d, 反弹伤害=%d\n", 
                 ctime(time()), attacker->query("name"), attacker->query("id"), ap*1.0/1000000, defender->query("name"), defender->query("id"), 
                 pp*1.0/1000000, jibie, ratio, damage, qdamage ) );
        }
        else if( randnum < to_int(ceil(pp/2*(fix_data+1.6+ratio))) &&
        	       rand>=4 &&
        	       defender->query("neili") > qdamage/25 )
        {
            defender->add("neili", -qdamage/25);
            sdamage = damage/2;
            result += GRN "$n的斗转星移自然激发而出，将$N的攻势大半移了开去。\n" NOR;
            if ( objectp(attacker) && objectp(defender) )
              log_file( "static/douzhuan", sprintf("%s:斗转效果：半吸收，%s(%s)的ap=%.2fM, %s(%s)的pp=%.2fM, jibie=%d, ratio=%.2f, damage=%d, 反弹伤害=%d\n", 
                 ctime(time()), attacker->query("name"), attacker->query("id"), ap*1.0/1000000, defender->query("name"), defender->query("id"), 
                 pp*1.0/1000000, jibie, ratio, damage, qdamage ) );
        }
        else
        {
         if ( objectp(attacker) && objectp(defender) )
            log_file( "static/douzhuan", sprintf("%s:斗转效果：失败，%s(%s)的ap=%.2fM, %s(%s)的pp=%.2fM, jibie=%d, ratio=%.2f, damage=%d, 反弹伤害=%d\n", 
               ctime(time()), attacker->query("name"), attacker->query("id"), ap*1.0/1000000, defender->query("name"), defender->query("id"), 
               pp*1.0/1000000, jibie, ratio, damage, qdamage ) );	
        	return -1;
        }
        return ({sdamage,result});
    }  
    //未发动斗转
    return -1;
}
