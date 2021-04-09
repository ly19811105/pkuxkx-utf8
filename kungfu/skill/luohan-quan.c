// luohan-quan.c 罗汉拳

inherit SKILL;

mapping *action = ({
([	"action" : "$N连续上步，一式「黄莺落架」，左右手分靠，变拳为掌，击向$n的$l",
	"force" : 180,
        "dodge" : 5,
	"lvl" : 0,
	"skill_name" : "黄莺落架",
        "damage_type" : "瘀伤"
]),
([	"action" : "$N左脚虚踏，全身右转，一招「丹凤朝阳」，右掌猛地插向$n的$l",
	"force" : 200,
        "dodge" : 10,
	"lvl" : 8,
	"skill_name" : "丹凤朝阳",
        "damage_type" : "瘀伤"
]),
([	"action" : "$N双手大开大阖，宽打高举，使一招「洛钟东应」，双拳向$n的$l打去",
	"force" : 220,
        "dodge" : 15,
	"lvl" : 15,
	"skill_name" : "洛钟东应",
        "damage_type" : "瘀伤"
]),
([	"action" : "$N左掌圈花扬起，屈肘当胸，虎口朝上，一招「偏花七星」打向$n的$l",
	"force" : 260,
        "dodge" : 20,
	"lvl" : 24,
	"skill_name" : "偏花七星",
        "damage_type" : "瘀伤"
]),
([	"action" : "$N使一招「苦海回头」，上身前探，双手划了个半圈，击向$n的$l",
	"force" : 300,
        "dodge" : 25,
	"lvl" : 33,
	"skill_name" : "苦海回头",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N双掌划弧，一记「挟山超海」，掌出如电，一下子切到$n的手上",
	"force" : 360,
        "dodge" : 30,
	"lvl" : 42,
	"skill_name" : "挟山超海",
        "damage_type" : "瘀伤"
]),
([	"action" : "$N施出「慑服外道」，双拳拳出如风，同时打向$n头，胸，腹三处要害",
	"force" : 420,
        "dodge" : 35,
	"lvl" : 50,
	"skill_name" : "慑服外道",
        "damage_type" : "瘀伤"
]),
([	"action" : "$N左脚内扣，右腿曲坐，一式「三入地狱」，双手齐齐按向$n的胸口",
	"force" : 480,
        "dodge" : 40,
	"lvl" : 58,
	"skill_name" : "三入地狱",
        "damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("luohan-quan", 1) >= (int)me->query_skill("buddhism", 1)+25)
                return notify_fail("你的禅宗心法等级不够，怎能静心。\n");
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练罗汉拳必须空手。\n");
	if ((int)me->query_skill("hunyuan-yiqi", 1) < 10)
		return notify_fail("你的混元一气功火候不够，无法学罗汉拳。\n");
	if ((int)me->query("max_neili") < 50)
		return notify_fail("你的内力太弱，无法练罗汉拳。\n");
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
	level   = (int) me->query_skill("luohan-quan");
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

string perform_action_file(string action)
{
        return __DIR__"luohan-quan/" + action;
}

int practice_skill(object me)
{
        if ((int)me->query_skill("luohan-quan", 1) >= (int)me->query_skill("buddhism", 1)+25)
                return notify_fail("你的禅宗心法等级不够，怎能静心。\n");
	if ((int)me->query("qi") < 30)
		return notify_fail("你的体力太低了。\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("你的内力不够练罗汉拳。\n");
	me->receive_damage("qi", 25);
	me->add("neili", -5);
	return 1;
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
