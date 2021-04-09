// pudu-zhang.c 普渡杖法

inherit SKILL;

mapping *action = ({
([	"action":"$N使一招「黄牛转角」，手中$w自下而上，沉猛无比地向$n的小腹挑去。",
	"force" : 180,
        "dodge" : -10,
	"damage": 15,
	"lvl" : 0,
	"skill_name" : "黄牛转角",
	"damage_type":"挫伤"
]),
([	"action":"$N快步跨出，一招「野马追风」，左手平托$w，右掌猛推杖端，顶向$n的胸口。",
	"force" : 200,
        "dodge" : -10,
	"damage": 20,
	"lvl" : 9,
	"skill_name" : "野马追风",
	"damage_type":"挫伤"
]),
([	"action":"$N高举$w，一招「猛虎跳涧」，全身跃起，手中$w搂头盖顶地向$n击去。",
	"force" : 230,
        "dodge" : -5,
	"damage": 30,
	"lvl" : 18,
	"skill_name" : "猛虎跳涧",
	"damage_type":"挫伤"
]),
([	"action":"$N一招「狮子摇头」，双手持杖如橹，对准$n猛地一搅，如同平地刮起一阵旋风。",
	"force" : 270,
        "dodge" : -10,
	"damage": 35,
	"lvl" : 27,
	"skill_name" : "狮子摇头",
	"damage_type":"挫伤"
]),
([	"action":"$N横持$w，一招「苍龙摆尾」，杖端化出无数个圆圈，凝滞沉重，把$n缠在其中。",
	"force" : 320,
        "dodge" : -15,
	"damage": 40,
	"lvl" : 36,
	"skill_name" : "苍龙摆尾",
	"damage_type":"挫伤"
]),
([	"action":"$N全身滚倒，$w盘地横飞，突出一招「大蟒翻身」，杖影把$n裹了起来",
	"force" : 380,
        "dodge" : 5,
	"damage": 55,
	"lvl" : 45,
	"skill_name" : "大蟒翻身",
	"damage_type":"挫伤"
]),
([	"action":"$N双手和十，躬身一招「胡僧托钵」，$w自肘弯飞出，拦腰向$n撞去。",
	"force" : 450,
        "dodge" : -5,
	"damage": 55,
	"lvl" : 53,
	"skill_name" : "胡僧托钵",
	"damage_type":"挫伤"
]),
([	"action":"$N一招「慈航普渡」，$w如飞龙般自掌中跃出，直向$n的胸口穿入。",
	"force" : 530,
        "dodge" : -5,
	"damage": 60,
	"lvl" : 60,
	"skill_name" : "慈航普渡",
	"damage_type":"挫伤"
]),
});

int valid_enable(string usage) { return (usage == "staff") || (usage == "parry"); }

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
	level   = (int) me->query_skill("pudu-zhang",1);
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[random(i+1)];
	return action[0];
}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "staff")
		return notify_fail("你使用的武器不对。\n");
	if ((int)me->query("qi") < 50)
		return notify_fail("你的体力不够练普渡杖法。\n");
	me->receive_damage("qi", 30);
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

string query_yinyang()
{
	return "少阳";
}