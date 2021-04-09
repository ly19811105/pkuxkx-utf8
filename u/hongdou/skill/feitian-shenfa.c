// feitian-shenfa 飞天身法

inherit SKILL;

string *dodge_msg = ({
	"$n一个「气冲牛斗」，跃起数尺，躲过了$N这一招。\n",
	"$n身形向后一纵，使出一招「纵横九霄」，避过了$N的攻击。\n",
	"$n身形一矮，使出「天狼涉水」，恰好躲过了$N的攻势。\n",
        "$n一招「天女散花」，身子向侧平飞，姿态美妙地躲了开去。\n"
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
                return notify_fail("你的体力太差了，不能练飞天身法。\n");
	if (me->query_skill("feitian-shenfa", 1) < 30)
	        me->receive_damage("qi", 10);
	else if (me->query_skill("feitian-shenfa", 1) < 60)
		me->receive_damage("qi", 20);
	else 
		me->receive_damage("qi", 30);
        return 1;
}

