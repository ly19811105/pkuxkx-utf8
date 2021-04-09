// yunlong-jian.c 云龙剑

#include <ansi.h>

inherit SKILL;
string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});

mapping *action = ({
([	"action":"\n$N使一式"+(order[random(13)])+"「悠悠顺自然」"NOR"，手中$w嗡嗡微振，幻成一条白光刺向$n的$l",
	"force" : 50,
        "dodge" : 10,
	"damage": 20,
	"lvl" : 0,
	"skill_name" : "悠悠顺自然",
	"damage_type":	"刺伤"
]),
([	"action":"\n$N错步上前，使出"+(order[random(13)])+"「来去若梦行」"NOR"，剑意若有若无，$w淡淡地向$n的$l挥去",
	"force" : 60,
        "dodge" : 10,
	"damage": 30,
	"lvl" : 8,
	"skill_name" : "来去若梦行",
	"damage_type":	"割伤"
]),
([	"action":"\n$N一式"+(order[random(13)])+"「志当存高远」"NOR"，纵身飘开数尺，运发剑气，手中$w遥摇指向$n的$l",
	"force" : 70,
        "dodge" : 15,
	"damage": 40,
	"lvl" : 15,
	"skill_name" : "志当存高远",
	"damage_type":	"刺伤"
]),
([	"action":"$N纵身轻轻跃起，一式"+(order[random(13)])+"「表里俱澄澈」"NOR"，剑光如水，一泻千里，洒向$n全身",
	"force" : 80,
        "dodge" : 20,
	"damage": 50,
	"lvl" : 20,
	"skill_name" : "表里俱澄澈",
	"damage_type":	"割伤"
]),
([	"action":"$N手中$w中宫直进，一式"+(order[random(13)])+"「随风潜入夜」"NOR"，无声无息地对准$n的$l刺出一剑",
	"force" : 90,
        "dodge" : 15,
	"damage": 60,
	"lvl" : 30,
	"skill_name" : "随风潜入夜",
	"damage_type":	"刺伤"
]),
([	"action":"$N手中$w一沉，一式"+(order[random(13)])+"「润物细无声」"NOR"，无声无息地滑向$n的$l",
	"force" : 100,
        "dodge" : 15,
	"damage": 70,
	"lvl" : 40,
	"skill_name" : "润物细无声",
	"damage_type":	"割伤"
]),
([	"action":"\n$N手中$w斜指苍天，剑芒吞吐，一式"+(order[random(13)])+"「云龙听梵音」"NOR"，对准$n的$l斜斜击出",
	"force" : 110,
        "dodge" : 25,
	"damage": 80,
	"lvl" : 50,
	"skill_name" : "云龙听梵音",
	"damage_type":	"刺伤"
]),
([	"action":"$N左指凌空虚点，右手$w逼出丈许雪亮剑芒，一式"+(order[random(13)])+"「万里一点红」"NOR"刺向$n的咽喉",
	"force" : 120,
        "dodge" : 15,
	"damage": 90,
	"lvl" : 60,
	"skill_name" : "万里一点红",
	"damage_type":	"刺伤"
]),
([	"action":"$N合掌跌坐，一式"+(order[random(13)])+"「我心化云龙」"NOR"，$w自怀中跃出，如疾电般射向$n的胸口",
	"force" : 130,
        "dodge" : 15,
	"damage": 100,
	"lvl" : 70,
	"skill_name" : "我心化云龙",
	"damage_type":	"刺伤"
]),
([	"action":"\n$N呼的一声拔地而起，一式"+(order[random(13)])+"「日月与同辉」"NOR"，$w幻出万道光影，将$n团团围住",
	"force" : 140,
        "dodge" : 15,
	"damage": 110,
	"lvl" : 80,
	"skill_name" : "日月与同辉",
	"damage_type":	"刺伤"
]),
([	"action":"$N随风轻轻飘落，一式"+(order[random(13)])+"「清风知我意」"NOR"，手中$w平指，缓缓拍向$n脸颊",
	"force" : 150,
        "dodge" : 15,
	"damage": 120,
	"lvl" : 90,
	"skill_name" : "清风知我意",
	"damage_type":	"刺伤"
]),
([	"action" : "$N剑尖微颤作龙吟，一招"+(order[random(13)])+"「高处不胜寒」"NOR"，切骨剑气如飓风般裹向$n全身",
	"force" : 160,
        "dodge" : 15,
	"damage": 130,
	"lvl" : 100,
	"skill_name" : "高处不胜寒",
	"damage_type":	"刺伤"
]),
([	"action" : "$N募的使一招"+(order[random(13)])+"「红叶舞秋山」"NOR"，顿时剑光中几朵血花洒向$n全身",
	"force" : 180,
        "dodge" : 25,
	"damage": 140,
	"lvl" : 110,
	"skill_name" : "红叶舞秋山",
	"damage_type":	"刺伤"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
int valid_combine(string combo) { return combo=="yunlong-bian"; }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 200)
		return notify_fail("你的内力不够。\n");
	if ((int)me->query_skill("yunlong-shengong", 1) < 20)
		return notify_fail("你的云龙神功火候太浅。\n");
//	if ((int)me->query_skill("yunlong-xinfa", 1) < 20)
//		return notify_fail("你的云龙心法火候太浅。\n");
	if ((int)me->query_skill("force", 1) < 40)
		return notify_fail("你的基本内功火候太浅。\n");
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
	level   = (int) me->query_skill("yunlong-jian",1);
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
	if ((int)me->query_skill("yunlong-shengong", 1) < 20)
		return notify_fail("你的云龙神功火候太浅。\n");
	if ((int)me->query("qi") < 50)
		return notify_fail("你的体力不够练云龙剑法。\n");
	me->receive_damage("qi", 25);
	return 1;
}
string perform_action_file(string action)
{
	return __DIR__"yunlong-jian/" + action;
}

string query_yinyang()
{
	return "少阳";
}