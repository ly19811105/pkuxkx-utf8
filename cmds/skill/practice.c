// practice.c
// Modified by iszt@pkuxkx, 2007-03-11

#include <ansi.h>
#include <weapon.h>;

inherit F_CLEAN_UP;
#include "/cmds/skill/study_class_benefit.h"
int main(object me, string arg)
{
	object where = environment(me);
	object weapon,weapon2;
	string skillname, sname;
	int skill, skill_basic,times,i,realtimes;
	//空手功夫
        string *kongshou_skill = ({"claw","finger","strike","cuff","unarmed","hand","leg","array"});

	seteuid(getuid());
	weapon = me->query_temp("weapon");
	weapon2 = me->query_temp("secondary_weapon");

	if(me->is_busy()) return notify_fail("你现在正忙着呢。\n");
	if(me->is_fighting() ) return notify_fail("临阵磨枪？来不及啦。\n");
	if(me->query("lingjiu/last_xiulian_time"))
		return notify_fail("你现在正在恢复武功，没有精力研究武功。\n");

	if(!arg || (sscanf(arg, "%s %d", arg, times)< 2 ))
		return notify_fail("指令格式：practice|lian <技能> <次数>\n");
	if(times <1 || times>50) return notify_fail("练习次数应该在 1-50 次！\n");

	if( !stringp(skillname = me->query_skill_mapped(arg)) )
		return notify_fail("你只能练习用 enable 指定的特殊技能。\n");
/*
//这个设定除了让full更有难度之外无任何实际意义
	if (arg == "parry" && me->query_skill(skillname, 1) > me->query_skill(arg, 1) / 5 * 4
		&& skillname != "flatter" )
		return notify_fail("你的基本招架已经对练习"+to_chinese(skillname)+"无所助益了。\n");
*/

	if (member_array(arg, kongshou_skill) != -1) 
	{
		if ((weapon || weapon2)) 
			return notify_fail("你必须空手才能练习"+to_chinese(skillname)+"。\n");
	}
	else if ( arg == "force" )
		return notify_fail("特殊内功无法练习，你可以通过(learn)或者(xiulian)来提高。\n");
        else if ( arg == "iron-cloth" )
                return notify_fail("特殊硬功无法练习，你可以通过(learn)来提高。\n");
	//暂时不限制dodge 和parry
        else if ( arg != "dodge" && arg != "parry" && arg != "throwing")
	{
		if (!weapon || ((string)weapon->query("skill_type") != arg)) 
			if (!weapon2 || ((string)weapon2->query("skill_type") != arg)) 
				return notify_fail("你要装备 "+arg+" 类武器才能练习"+to_chinese(skillname)+"。\n");
	}
	skill_basic = me->query_skill(arg, 1);
	skill = me->query_skill(skillname, 1);

	if( skill < 1 )
		return notify_fail("你好像还没有学过这项技能吧？最好先去请教别人。\n");
	if( skill_basic < 1 )
		return notify_fail("你对这方面的技能还是一窍不通，最好从先从基本学起。\n");

        if( skill_basic == skill )
                return notify_fail("你需要提高基本功，不然练得再多也没有用。\n");
        if( skill_basic <= skill )
		return notify_fail(sprintf("你的%s的级别还没有%s的级别高，不能通过练习来提高了。\n",
			to_chinese(arg), to_chinese(skillname)));
		//判断是否是自创武功
	if( !find_object(SKILL_D(skillname)) && file_size(SKILL_D(skillname)+".c") < 0)
		return notify_fail("自创武功必须到闭关室用selfpractice和selfthinking练习。\n");
	if( !SKILL_D(skillname)->valid_learn(me) ) return 0;

	realtimes=0;
	for(i=0;i<times;i++)
	{
		if( SKILL_D(skillname)->practice_skill(me) )
		{
			me->improve_skill(skillname, benefit(me,skill_basic/5 +1), skill_basic > skill? 0: 1);
			realtimes++;
		}
		else break;
	}
	if (realtimes)
	{
		if (!environment(me)->query("least_msg"))
		if (!random(10)) tell_room(environment(me),
			me->name() +
			"正在专心练习" +
			to_chinese(skillname) + "。\n", ({ me }));
		write ("你" + ((realtimes == 1)?"试着":"反复") + "练习" + to_chinese(skillname));
		if (stringp(sname = SKILL_D(skillname)->query_skill_name(random(me->query_skill(skillname,1)))))
			write ("中「" + sname + "」这一招");
		write( "，获得了" + ((realtimes == 1)?"少许":"不少") + "进步！\n");
	}
	else
	{
		if (SKILL_D(skillname)->practice_skill(me))
		{
			write( HIR "你太累了，没有办法练习"+ to_chinese(skillname) +"。\n" NOR);
		}
		else return 0;
	}
	return 1;  
}                          


int help(object me)
{
	write(@TEXT
指令格式：practice|lian <技能种类> <次数>

这个指令让你练习某个种类的技能，这个技能必须是经过 enable 的专业技能。
如果你对这方面的基本技能够高，可以经由练习直接升级，而且升级的上限只跟
你基本技能的等级有关，换句话说，勤加练习是使你的所学「青出于蓝胜于蓝」
的唯一途径，当然，在这之前你必须从实际运用中获得足够的经验以提升你的基
本技能。
TEXT
		 );
	return 1;
}
