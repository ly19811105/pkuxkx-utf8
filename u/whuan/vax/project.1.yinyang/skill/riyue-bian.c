// riyue-bian.c 日月鞭法

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([	"action":		"$N端坐不动，一招「裂石式」，手中$w抖得笔直，对准$n的胸腹要害连刺数鞭",
	"dodge":		-10,
	"damage":		100,
	"lvl" : 0,
	"skill_name" : "裂石式",
	"damage_type":	"刺伤"
]),
([	"action":		"$N身形一转，一招「断川式」，手中$w如矫龙般腾空一卷，猛地向$n劈头打下",
	"dodge":		-20,
	"damage":		200,
	"lvl" : 60,
	"skill_name" : "断川式",
	"damage_type":	"刺伤"
]),
([	"action":		"$N力贯鞭梢，一招「破云式」，手中$w舞出满天鞭影，排山倒海般扫向$n全身",
	"dodge":		-40,
	"damage":		300,
	"lvl" : 120,
	"skill_name" : "破云式",
	"damage_type":	"刺伤"
])
});

int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
	object weapon;

	if( (int)me->query("max_neili") < 500 )
		return notify_fail("你的内力不足，没有办法练日月鞭法, 多练些内力再来吧。\n");

	if ((int)me->query_skill("hunyuan-yiqi", 1) < 50)
		return notify_fail("你的混元一气功火候太浅。\n");

	if ( !objectp(weapon = me->query_temp("weapon"))
	|| ( string)weapon->query("skill_type") != "whip" )
		return notify_fail("你必须先找一条鞭子才能练鞭法。\n");

	return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
	level   = (int) me->query_skill("riyue-bian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "whip")
		return notify_fail("你使用的武器不对。\n");
	if ((int)me->query("qi") < 50)
		return notify_fail("你的体力不够练日月鞭法。\n");
	me->receive_damage("qi", 40);
	return 1;
}

string perform_action_file(string action)
{
	if ( this_player()->query_skill("riyue-bian", 1) >= 50 )
		return __DIR__"riyue-bian/" + action;
}

string *parry_msg = ({
        "只听见「锵」一声，被$p格开了。\n",
        "结果「当」地一声被$p挡开了。\n",
        "但是被$n用手中$v架开。\n",
        "但是$n身子一侧，用手中$v格开。\n",
});

string *unarmed_parry_msg = ({
        "但是被$p格开了。\n",
        "结果被$p挡开了。\n",
});

string query_parry_msg(object weapon)
{
        if( weapon )
                return parry_msg[random(sizeof(parry_msg))];
        else
                return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}

string query_yinyang()
{
	return "太阳";
}