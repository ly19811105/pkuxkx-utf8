// zhaixinggong.c based on xiaoyaoyou.c
// by yucao
#include <ansi.h>

inherit SKILL;

string *dodge_msg = ({
	"$n一个「天外摘星」，跃起数尺，躲过了$N这一招。\n",
	"$n身形向后一纵，使出一招「飘然出尘」，避过了$N的攻击。\n",
	"$n使出「天狼涉水」，恰好躲过了$N的攻势。\n",
        "$n一招「织女穿梭」，姿态美妙地躲了开去。\n"
});

int valid_enable(string usage) 
{ 
	return (usage == "dodge") || (usage == "move"); 
}

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( (int)me->query("qi") < 40 )
                return notify_fail("你的体力太差了，不能练摘星功。\n");
	if (me->query_skill("zhaixinggong", 1) < 30)
	        me->receive_damage("qi", 10);
	else if (me->query_skill("zhaixinggong", 1) < 60)
		me->receive_damage("qi", 20);
	else 
		me->receive_damage("qi", 30);
        return 1;
}

string query_counter_msg(object me, object target)
{
	return HIW "$N瞧得仔细，趁机伸腿一绊，$n立脚不住，噗通一声扑地倒了！\n" NOR;
}