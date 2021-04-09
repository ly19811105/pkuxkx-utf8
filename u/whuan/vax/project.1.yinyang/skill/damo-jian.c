// damo-jian.c 达摩剑

inherit SKILL;

mapping *action = ({
([	"action":"$N使一式「万事随缘往」，手中$w嗡嗡微振，幻成一条疾光刺向$n的$l",
	"force" : 220,
        "dodge" : -10,
	"damage": 15,
	"lvl" : 0,
	"skill_name" : "万事随缘往",
	"damage_type":	"刺伤"
]),
([	"action":"$N错步上前，使出「来去若梦行」，剑意若有若无，$w淡淡地向$n的$l挥去",
	"force" : 240,
        "dodge" : -10,
	"damage": 20,
	"lvl" : 19,
	"skill_name" : "来去若梦行",
	"damage_type":	"割伤"
]),
([	"action":"$N一式「浮世沧桑远」，纵身飘开数尺，运发剑气，手中$w遥摇指向$n的$l",
	"force" : 260,
        "dodge" : 5,
	"damage": 30,
	"lvl" : 39,
	"skill_name" : "浮世沧桑远",
	"damage_type":	"割伤"
]),
([	"action":"$N纵身轻轻跃起，一式「轮回法舟轻」，剑光如轮疾转，霍霍斩向$n的$l",
	"force" : 280,
        "dodge" : 10,
	"damage": 35,
	"lvl" : 59,
	"skill_name" : "轮回法舟轻",
	"damage_type":	"割伤"
]),
([	"action":"$N手中$w中宫直进，一式「水月通禅寂」，无声无息地对准$n的$l刺出一剑",
	"force" : 320,
        "dodge" : 15,
	"damage": 40,
	"lvl" : 79,
	"skill_name" : "水月通禅寂",
	"damage_type":	"刺伤"
]),
([	"action":"$N手中$w斜指苍天，剑芒吞吐，一式「鱼龙听梵音」，对准$n的$l斜斜击出",
	"force" : 360,
        "dodge" : 5,
	"damage": 45,
	"lvl" : 99,
	"skill_name" : "鱼龙听梵音",
	"damage_type":	"刺伤"
]),
([	"action":"$N左指凌空虚点，右手$w逼出丈许雪亮剑芒，一式「千里一苇去」刺向$n的$l",
	"force" : 380,
        "dodge" : 5,
	"damage": 55,
	"lvl" : 109,
	"skill_name" : "千里一苇去",
	"damage_type":	"刺伤"
]),
([	"action":"$N合掌跌坐，一式「禅心顿自明」，$w自怀中跃出，如疾电般射向$n的胸口",
	"force" : 400,
        "dodge" : 5,
	"damage": 60,
	"lvl" : 119,
	"skill_name" : "禅心顿自明",
	"damage_type":	"刺伤"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_combine(string combo) { return combo=="xiuluo-dao"; }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 100)
		return notify_fail("你的内力不够。\n");
	if ((int)me->query_skill("hunyuan-yiqi", 1) < 20)
		return notify_fail("你的混元一气功火候太浅。\n");
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
	level   = (int) me->query_skill("damo-jian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");
	if ((int)me->query("qi") < 50)
		return notify_fail("你的体力不够练达摩剑。\n");
	me->receive_damage("qi", 25);
	return 1;
}
string perform_action_file(string action)
{
	return __DIR__"damo-jian/" + action;
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
	return "纯阳";
}