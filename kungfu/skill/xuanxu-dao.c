// 玄虚刀 By Zine 出自倚天屠龙记代替杜撰的太极刀法
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([ "action" : "$N手中$w斜劈，一招「披风展翅」，反身一顿，一刀向$n的$l撩去",
	"force" : 120,
	"dodge" : -10,
	"parry" : 5,
	"damage" : 25,
        "lvl" : 0,
        "skill_name" : "披风展翅",
	"damage_type" : "割伤"
]),
([ "action" : "$N一招「抽刀断水」，双手执刀，$w一提一收，数次斩向$n的颈部",
	"force" : 130,
	"dodge" : -10,
	"parry" : 10,
	"damage" : 35,
        "lvl" : 0,
	"skill_name" : "抽刀断水",
	"damage_type" : "割伤"
]),
([ "action" : "$N展身虚步，提腰跃落，一招「风拂山岗」，刀柄温柔地递向$n的四肢",
	"force" : 140,
	"dodge" : -5,
	"parry" : 5,
	"damage" : 45,
        "lvl" : 10,
	"skill_name" : "风拂山岗",
	"damage_type" : "割伤"
]),
([ "action" : "$N一招「拨云见日」，$w大开大阖，看似全无章法，却砍向$n",
	"force" : 180,
	"dodge" : 5,
	"parry" : 5,
	"damage" : 60,
        "lvl" : 20,
	"skill_name" : "拨云见日",
	"damage_type" : "割伤"
]),
([ "action" : "$N手中$w一沉，一招「苍鹰望月」，反手又是一刀，砍向$n的胸口",
	"force" : 230,
	"dodge" : 10,
	"parry" : 5,
	"damage" : 75,
        "lvl" : 40,
	"skill_name" : "苍鹰望月",
	"damage_type" : "割伤"
]),
([ "action" : HIW+"$N"+HIW+"挥舞$w，使出一招「漫天飞雪」，刹那间天地只剩下刀影，齐齐罩向$n"+NOR,
	"force" : 400,
	"dodge" : 100,
	"parry" : 15,
	"damage" : 180,
        "lvl" : 200,
	"skill_name" : "漫天飞雪",
	"damage_type" : "割伤"
]),
([ "action" : "$N一招「太虚揽月」，一步跨前，$w顺势往前，挟风声劈向$n的$l",
	"force" : 310,
	"dodge" : 5,
	"parry" : 15,
	"damage" : 105,
        "lvl" : 100,
	"skill_name" : "太虚揽月",
	"damage_type" : "割伤"
]),
([ "action" : "$N盘身驻地，一招「虚实莫辩」，攻中又守，难辨方向",
	"force" : 350,
	"dodge" : 80,
	"parry" : 80,
	"damage" : 125,
        "lvl" : 120,
	"skill_name" : "虚实莫辩",
	"damage_type" : "割伤"
]),
});


int valid_enable(string usage) { return (usage == "blade") || (usage == "parry"); }

int valid_combine(string combo) { return combo=="taiji-jian"; }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 100)
		return notify_fail("你的内力不够。\n");
	if ((int)me->query_skill("taiji-shengong", 1) < 20)
		return notify_fail("你的太极神功火候太浅。\n");
	if ((int)me->query_skill("xuanxu-dao", 1) >= (int)me->query_skill("taiji-quan", 1))
		return notify_fail("你的太极拳火候太浅。\n");
	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level   = (int) me->query_skill("xuanxu-dao",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];

}

int practice_skill(object me)
{
	object weapon;

	if ((int)me->query_skill("xuanxu-dao", 1) >= (int)me->query_skill("taiji-quan", 1))
		return notify_fail("你的太极拳火候太浅。\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("你使用的武器不对。\n");
	if ((int)me->query("qi") < 50)
		return notify_fail("你的体力不够练玄虚刀法。\n");
	me->receive_damage("qi", 30);
	return 1;
}

string *parry_msg = ({
        "只见$n将手中$v舞成一片，顿时格开了$N的$w。\n",
        "$n使出太极刀法「卸」字诀，$v轻轻一点，$N的$w好象打在棉絮中，对$n毫无伤害。\n",
        "$n身子一侧，用手中$v轻轻一推$N的$w，$N的$w一下就偏了出去。\n",
        "但是被$n用手中$v架开。\n",
        "但是$n身子一侧，用手中$v格开。\n",
});

string *unarmed_parry_msg = ({
        "但是$n身子一侧，用左手轻轻一推$N的$w，$N的$w一下就偏了出去。\n",
        "$n左手轻轻推出，拍向$N的$w，然后身体向右一侧，顺势后拉，$N就象打在一团棉絮中，对$n毫无伤害。\n",
});

string query_parry_msg(object weapon)
{
        if( weapon )
                return parry_msg[random(sizeof(parry_msg))];
        else
                return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}

