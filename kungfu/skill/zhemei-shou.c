// SKILL zhemei-shou.c
//天山折梅手书上说只有6招，3招掌法，3招擒拿
//根据书的原意，只保留原来的6招

inherit SKILL;

mapping *action = ({
([	"action" : "$N一招「黄昏独自愁」，身子跃然而起，抓向$n的头部",
	"force" : 120,
	"dodge" : 240,
	"damage" : 20,
	"lvl" : 0,
	"skill_name" : "黄昏独自愁",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N一招「梅花雪落覆白苹」，双手合击，$n只觉无处可避",
	"force" : 150,
	"dodge" : 270,
	"damage" : 45,
	"lvl" : 30,
	"skill_name" : "梅花雪落覆白苹",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N一招「砌下落梅如雪乱」，双手飘然抓向$n",
	"force" : 190,
	"dodge" : 300,
	"damage" : 50,
	"lvl" : 70,
	"skill_name" : "砌下落梅如雪乱",
	"damage_type" : "瘀伤"
]),

([	"action" : "$N双手平举，一招「云破月来花弄影」击向$n",
	"force" : 240,
	"dodge" : 330,
	"damage" : 80,
	"lvl" : 90,
	"skill_name" : "云破月来花弄影",
            "damage_type" : "瘀伤"
]),
([	"action" : "$N一招「花开堪折直须折」，拿向$n，似乎$n的全身都被笼罩",
	"force" : 270,
	"dodge" : 360,
	"damage" : 100,
	"lvl" : 110,
	"skill_name" : "花开堪折直须折",
	"damage_type" : "内伤"
]),

([	"action" : "$N左手虚晃，右手一记「红颜未老恩先绝」击向$n的头部",
	"force" : 310,
	"dodge" : 390,
	"damage" : 150,
	"lvl" : 140,
	"skill_name" : "红颜未老恩先绝",
           "damage_type" : "瘀伤"
]),

});

int valid_enable(string usage) { return usage=="parry"|| usage=="hand"; }

int valid_combine(string combo) { return combo=="liuyang-zhang"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练天山折梅手必须空手。\n");
	if ((int)me->query("max_neili") < 20)
		return notify_fail("你的内力太弱，无法练天山折梅手。\n");
	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("zhemei-shou",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 30)
		return notify_fail("你的体力太低了。\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("你的内力不够练天山折梅手。\n");
	me->receive_damage("qi", 25);
	me->add("neili", -10);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"zhemei-shou/" + action;
}
