// abandon.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	if( !arg || arg=="" ) 
		return notify_fail("你要放弃哪一项技能？\n");

	if( !me->delete_skill(arg) )
		return notify_fail("你并没有学过这项技能。\n");

	write("你决定放弃继续学习" + to_chinese(arg) + "。\n");
	return 1;
}

int help()
{
	write(@TEXT
指令格式：abandon|fangqi <技能名称>

放弃一项你所学过的技能，注意这里所说的「放弃」是指将这项技能从你人物
的资料中删除，如果你以后还要练，必须从０开始重练，请务必考虑清楚。

这个指令使用的场合通常是用来删除一些「不小心」练出来的技能，由于每个
人有着不同的天赋，所修习的武功也不会相同。如果样样都学，到头来只会样
样不精。
TEXT
	);
	return 1;
}
