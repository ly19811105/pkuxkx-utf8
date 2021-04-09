// xue-dao.c 血刀
// Designed by secret(秘密)
//

inherit SKILL;

mapping *action = ({
([      "action" : "$N高举手中$w,使出一招「磨牙吮血」，一刀斜劈$n的$l  ",
        "skill_name" : "磨牙吮血",
        "force" : 100,
        "dodge" : -5,
        "parry" : 5,
        "lvl" : 0,
        "damage" : 20,
        "damage_type" : "割伤",
]),
([      "action" : "$N就地一滚，使一招「刺血满地」，手中$w卷向$n的大腿  ",
        "skill_name" : "刺血满地",
        "force" : 140,
        "dodge" : 5,
        "parry" : 5,
        "lvl" : 8,
        "damage" : 25,
        "damage_type" : "割伤",
]),
([      "action" : "$N足尖一点，使出「血海茫茫」，刀锋自上而下直插$n的$l  ",
        "skill_name" : "血海茫茫",
        "force" : 180,
        "dodge" : 10,
        "parry" : 5,
        "lvl" : 16,
        "damage" : 30,
        "damage_type" : "割伤",
]),
([      "action" : "$N使出一招「呕心沥血」，将$w舞得如白雾一般压向$n  ",
        "skill_name" : "呕心沥血",
        "force" : 220,
        "dodge" : 5,
        "parry" : 5,
        "lvl" : 24,
        "damage" : 40,
        "damage_type" : "割伤",
]),
([      "action" : "$N低吼一声，使出「血口喷人」，举$w直劈$n的$l  ",
        "skill_name" : "血口喷人",
        "force" : 250,
        "dodge" : -5,
        "parry" : 5,
        "lvl" : 32,
        "damage" : 50,
        "damage_type" : "割伤",
]),
([      "action" : "$N使出「血迹斑斑」，飞身斜刺，忽然反手一刀横斩$n的腰部  ",
        "skill_name" : "血迹斑斑",
        "force" : 280,
        "dodge" : 10,
        "parry" : 5,
        "lvl" : 40,
        "damage" : 60,
        "damage_type" : "割伤",
]),
([      "action" : "$N使一式「以血还血」，挥刀直指$n的胸口  ",
        "skill_name" : "以血还血",
        "force" : 300,
        "dodge" : 5,
        "parry" : 10,
        "lvl" : 48,
        "damage" : 80,
        "damage_type" : "割伤",
]),
([      "action" : "$N刀锋虚点，使出一招「血流满面」，转身举$w横劈$n的面门  ",
        "skill_name" : "血流漫面",
        "force" : 320,
        "dodge" : 10,
        "parry" : 20,
        "lvl" : 56,
        "damage" : 100,
        "damage_type" : "割伤",
]),
});


int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_combine(string combo) { return combo=="mingwang-jian"; }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 50)
                return notify_fail("你的内力不够。\n");
        if ((int)me->query_skill("longxiang", 1) >= 20 ||
            (int)me->query_skill("xiaowuxiang", 1) >= 20)
		return 1;
	else
                return notify_fail("你的内功火候太浅。\n");
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
        level   = (int) me->query_skill("xue-dao",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if(!me->query_skill("longxiang",1)
                && !me->query_skill("xiaowuxiang",1))
                return notify_fail("练「血刀」必须要有雪山派的内功作为根基。\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query("qi") < 50)
                return notify_fail("你的体力不够，练不了「血刀」。\n");

        me->receive_damage("qi", 30);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"xue-dao/" + action;
}
