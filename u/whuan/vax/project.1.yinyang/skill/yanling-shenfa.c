// yanling-shenfa.c 燕灵身法
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : HIB "$n一式「单燕南飞」，左脚脚尖垫起，右脚凌空发力，身体如行云流水般滑出丈余。\n" NOR,
        "dodge"  : 15
]),
([      "action" : HIC "$n一式「一叶障目」，身行旋转，双脚跋地而起，顿时闪过了$N的凌厉攻势。\n" NOR,
        "dodge"  : 25
]),
([      "action" : HIG "$n一式「双燕分飞」，左右双足凌空踢出数脚，顿时落到$N的上空。\n" NOR,
        "dodge"  : 35
]),
([  "action" : HIR "$n一式「燕子出巢」，突然间身行前扑，象利箭般的冲向$N，令$N手无足措。\n" NOR,
        "dodge"  : 45
]),
([  "action" : HIW "$n一式「余音绕梁」，真气布满全身，围着$N急速旋转，令$N手忙脚乱，$n已落到几丈远的地方。\n" NOR,
        "dodge"  : 60
]),
([      "action" : MAG "$n一式「走马看花」，双足凌空点地，在剌剌风声中，从$N头顶横跃而过。\n" NOR,
        "dodge"  : 75
]),
([      "action" : HIR "$n一式「燕子回头」，双手力发劈空掌，借力身行上飘，霎时间躲过$N的凌厉攻势。\n" NOR,
        "dodge"  : 90
]),
([ "action" : HIM "$n一式「燕南归巢」，身体如陀螺般急转，气流形成一个个漩涡，令$N陷身其间。\n" NOR,
        "dodge"  : 100
])
});

mapping query_action(object me, object weapon)
{
        int zhaoshu, level;

        zhaoshu = sizeof(action);
        level   = (int) me->query_skill("yanling-shenfa");

        if (level < 60 )
                zhaoshu--;

        if (level < 50 )
                zhaoshu--;

        if (level < 40 )
                zhaoshu--;

        return action[random(zhaoshu)];
}

int valid_enable(string usage)
{
        return usage == "dodge" || usage == "move";
}

int valid_learn(object me)
{
        return 1;
}

string query_dodge_msg(string limb)
{
        object me, ob;
        mapping action;

        me = this_player();
        action = query_action(me, ob);

        return action["action"];
}
int practice_skill(object me)
{
        if( (int)me->query("qi") < 40 )
                return notify_fail("你的体力太差了，不能练燕灵身法。\n");
        me->receive_damage("qi", 20);
        return 1;
}

string query_yinyang()
{
	return "太阴";
}