// lieyan-dao.c 烈焰刀

inherit SKILL;

mapping *action = ({
([      "action" : "$N一招「黑龙现身」，$w有如一条黑龙在$n的周身旋游，勿快勿慢，变化若神",
        "force" : 80,
        "dodge" : -10,
        "damage" : 20,
        "lvl" : 0,
        "skill_name" : "黑龙现身",
        "damage_type" : "割伤"
]),
([      "action" : "$N一招「万水千山」，左右腿一前一后，$w乱披风势向$n的$l斩去",
        "force" : 90,
        "dodge" : -10,
        "damage" : 30,
        "lvl" : 8,
        "skill_name" : "万水千山",
        "damage_type" : "割伤"
]),
([      "action" : "$N纵身跃落，一招「横扫千里」，$w带着疾风呼的一声便向$n横扫过去",
        "force" : 110,
        "dodge" : -5,
        "damage" : 40,
        "lvl" : 16,
        "skill_name" : "横扫千里",
        "damage_type" : "割伤"
]),
([      "action" : "$N一招「左右开弓」，$w大开大阖，左右并进，左一刀，右一刀向$n的两肩砍落",
        "force" : 130,
        "dodge" : 5,
        "damage" : 50,
        "lvl" : 24,
        "skill_name" : "左右开弓",
        "damage_type" : "割伤"
]),
([      "action" : "$N手中$w自上而下，一招「百丈飞瀑」，刀光流泻，如一片雪白瀑布砍向$n的头部",
        "force" : 150,
        "dodge" : -10,
        "damage" : 60,
        "lvl" : 33,
        "skill_name" : "百丈飞瀑",
        "damage_type" : "割伤"
]),
([      "action" : "$N挥舞$w，使出一招「直摧万马」，上劈下撩，左挡右开，如千军万马般罩向$n",
        "force" : 170,
        "dodge" : 5,
        "damage" : 70,
        "lvl" : 42,
        "skill_name" : "直摧万马",
        "damage_type" : "割伤"
]),
([      "action" : "$N带得刀风劲疾，一招「怪蟒翻身」，一个猛转身，连刀带人往$n的$l的劈去",
        "force" : 190,
        "dodge" : 5,
        "damage" : 80,
        "lvl" : 51,
        "skill_name" : "怪蟒翻身",
        "damage_type" : "割伤"
]),
([      "action" : "$N向前一个弓步，一招「上步劈山」，$w直直的劈出，一片流光般的刀影向$n的全身罩去",
        "force" : 220,
        "dodge" : -5,
        "damage" : 100,
        "lvl" : 60,
        "skill_name" : "上步劈山",
        "damage_type" : "割伤"
]),
});


int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_combine(string combo) { return combo=="shenghuo-lingfa"; }
int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 100)
                return notify_fail("你的内力不够。\n");
        if ((int)me->query_skill("guangming-shenghuogong", 1) < 20)
                return notify_fail("你的光明圣火功火候太浅。\n");
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
        level   = (int) me->query_skill("lieyan-dao",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;
        int lvl = me->query_skill("lieyan-dao", 1);
        int i = sizeof(action);
        while (i--) if (lvl == action[i]["lvl"]) return notify_fail("师父教过你的都练熟了，再去继续学习吧！\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不对。\n");
        if ((int)me->query("jingli") < 50)
                  return notify_fail("你的精力不够练烈焰刀。\n");
        if ((int)me->query("qi") < 50)
                  return notify_fail("你的气不够练烈焰刀。\n");
        me->receive_damage("qi", 35);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"lieyan-dao/" + action;
}
