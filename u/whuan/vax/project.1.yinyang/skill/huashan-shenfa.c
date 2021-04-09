// xiaoyaoyou.c
// written by www

inherit SKILL;

string *dodge_msg = ({
        "$n一个「玉女梳妆」，身形飘飘躲过了$N这一招。\n",
        "$n身形凌空拔起，使出一招「朝阳初升」，避过了$N的攻击。\n",
        "$n使出「莲花怒放」，身形急晃，恰好躲过了$N的攻势。\n"
//        "但是$n身形飘忽，轻轻一纵，早已避开。\n",
//        "$n身随意转，倏地往一旁挪开了三尺，避过了这一招。\n",
//        "可是$n侧身一让，$N这一招扑了个空。\n",
//        "却见$n足不点地，往旁窜开数尺，躲了开去。\n",
//        "$n身形微晃，有惊无险地避开了$N这一招。\n"
});

int valid_enable(string usage)
{
        return (usage == "dodge") || (usage == "move");
}

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( (int)me->query("qi") < 40 )
                return notify_fail("你的体力太差了，不能练华山身法。\n");
        me->receive_damage("qi", 30);
        return 1;
}

string query_yinyang()
{
	return "太阳";
}
