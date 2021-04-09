// xuanfeng-leg.c 旋风扫叶腿
// modified by Venus Oct.1997
inherit SKILL;

mapping *action = ({
([      "action" : "$N双手虚晃，左脚猛地飞起，一式「风起云涌」，脚尖晃动，踢
向$n的屁股",
        "damage" : 100,
        "dodge" : 15,
        "damage_type" : "瘀伤",
        "lvl" : 10,
        "skill_name" : "风起云涌"
]),
([      "action" : "$N左脚顿地，别转身来抽身欲走，只一刹那间一回身，右脚一式
「空谷足音」，猛踹$n的$l",
        "damage" : 120,
        "dodge" : 10,
        "damage_type" : "瘀伤",
        "lvl" : 0,
        "skill_name" : "空谷足音"
]),
([      "action" : "$N左手一挣，反手扭搭住$n的右手，右脚同时踹出，既猛且准，一
式「碧渊腾蛟」，踢中的$n的胸口",
        "damage" : 140,
        "dodge" : 15,
        "damage_type" : "瘀伤",
        "lvl" : 10,
        "skill_name" : "碧渊腾蛟"
]),
([      "action" : "$N突然跃起，双足连环圈转，一式「秋风落叶」，足带风尘，攻向
$n的全身",
        "damage" : 160,
        "dodge" : 15,
        "damage_type" : "瘀伤",
        "lvl" : 10,
        "skill_name" : "秋风落叶"
]),
([      "action" : "$N两手护胸，双脚交叉踢起，一式「风扫残云」，脚脚不离$n的面
门左右",
        "damage" : 180,
        "dodge" : 20,
        "damage_type" : "瘀伤",
        "lvl" : 20,
        "skill_name" : "风扫残云"
]),
([      "action" : "$N突然侧身，却步后退，一个前空翻，右脚自上而下一式「流星坠
地」，照$n的面门直劈下来",
        "damage" : 200,
        "dodge" : 35,
        "damage_type" : "瘀伤",
        "lvl" : 30,
        "skill_name" : "流星坠地"
]),
([      "action" : "$N使一式「朔风吹雪」，全身突然飞速旋转，双足忽前忽后，迅猛
无极踹向$n的胸口",
        "damage" : 220,
        "dodge" : 30,
        "damage_type" : "瘀伤",
        "lvl" : 40,
        "skill_name" : "朔风吹雪"
]),
([      "action" : "$N抽身跃起，开声吐气，大喝一声：嗨！一式「雷动九天」，双脚
如旋风般踢向$n的$l",
        "damage" : 250,
        "dodge" : 35,
        "damage_type" : "瘀伤",
        "lvl" : 30,
        "skill_name" : "雷动九天"
]),
});

int valid_enable(string usage) { return usage=="unarmed" ||  usage=="leg"; } 

int valid_combine(string combo) { return combo=="luoying-shenzhang"; }

int valid_learn(object me)
{
    if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
        return notify_fail("旋风扫叶腿必须空手。\n");
    if ((int)me->query_skill("bibo-shengong", 1) < 15)
        return notify_fail("你的碧波神功火候不够，无法学旋风扫叶腿。\n");
    if ((int)me->query("max_neili") < 100)
        return notify_fail("你的内力太弱，无法练旋风扫叶腿。\n");
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
    level = (int)me->query_skill("xuanfeng-leg", 1);
    for(i = sizeof(action); i > 0; i--)
    if(level > action[i-1]["lvl"])
      return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 30)
       return notify_fail("你的体力太低了。\n");
    if ((int)me->query("neili") < 20)
       return notify_fail("你的内力不够练旋风扫叶腿。\n");
    me->receive_damage("qi", 20);
    me->add("neili", -1);
    return 1;
}
string perform_action_file(string action)
{
    return __DIR__"xuanfeng-leg/" + action;
}

