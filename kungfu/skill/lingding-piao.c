// yunlong-shenfa 云龙身法
// written by That

inherit SKILL;

string *dodge_msg = ({
        "$n一式「龙腾虎跃」，身行一转，猛的跳向一旁,躲过了$N的功势。\n",
        "$n一式「沙场点兵」，双臂置于身后，不急不缓，昂首从$N眼前跨过。\n",
        "$n一式「风雨同舟」，不退反进，一下子绕到了$N的身后。\n",
        "$n一式「养精蓄锐」，缓缓的向后一退，轻松让过了$N的凌厉攻势。\n",
        "$n一式「风檐展书」，左手一扬，身行一晃，便向右飘出丈远。\n",
        "$n一式「苍鹰搏兔」，身体如一只苍鹰，呼的一声从$N的眼前飞过。\n",
        "$n一式「九龙在天」，忽的拔地而起，在半空中一转，已落到几丈远的地方。\n",
        "$n一式「瀑落九天」，全身化为一道白影，忽的一个空翻，从左边飘到右边。\n",
        "$n一式「幻眼云烟」，身形陡地变得飘忽不定，令$N无法看清。\n",
        "$n一式「九天揽月」，宛若一条矫矢苍龙，倏的拔地而起，令$N不敢仰视。\n",
});

int valid_enable(string usage) { return (usage == "dodge") || (usage == "move");
 }

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
    return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if((int)me->query("qi") < 40 )
           return notify_fail("你的体力太差了，不能练零丁飘洋。\n");
        me->receive_damage("qi", 20);
        return 1;
}
