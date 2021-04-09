// luoying-shenfa.c 落英身法

inherit SKILL;

string *dodge_msg = ({
"$n一式「海燕掠波」，身子如飞燕掠波，往上空跃过，头一低，轻飘飘地落在地面上。\n",
"$n一式「退步收势」，一个筋斗，又一个筋斗，顿时闪过了$N的凌厉攻势。\n",
"$n一式「燕子入巢」，纵身上来，忽地腾空跃起，在半空犹如腾云驾雾一般，已落在$N的身后。\n",
"$n一式「雁落平沙」，左肋在地下一搭，身子已然弹起，在空中转了半个圈子，潇洒地落在了地上。\n",
"$n一式「移形换位」，拔起身子，忽左忽右，后退前趋，身法变幻，数跃之后，又落在$N的身后。\n",
"$n一式「燕双飞」，提气拔身，腾空而起，向后跃开。\n",
"$n一式「飞絮劲」，人已跃起，东纵西跃，一个左起，一个右始，回旋往复，真似一只玉燕，身法轻灵之极。\n",
"$n一式「四海遨游」，身子一幌，忽地跃起，左伸右收，右伸左收，左足探出，脚下纵眺如飞，已落在地面上。\n",
});




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
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	if( (int)me->query("qi") < 30 )
		return notify_fail("你的体力太差了，不能练落英身法。\n");
	me->receive_damage("qi", 20);
	return 1;
}

string query_yinyang()
{
	return "少阴";
}