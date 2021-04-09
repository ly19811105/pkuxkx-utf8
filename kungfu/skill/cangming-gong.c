// 云龙神功

inherit FORCE;

int valid_enable(string usage)
{
	return usage == "force";
}

int valid_learn(object me)
{
	int i, nb, nf, nh, ns, ts;
//	nb = (int)me->query_skill("yunlong-xinfa", 1);
	nf = (int)me->query_skill("force", 1);
	nh = (int)me->query_skill("cangming-gong", 1);

	if ( me->query("gender") == "无性" && nh > 49)
		return notify_fail("你无根无性，阴阳不调，难以领会高深的浩气苍冥功。\n");

	if ( nf < 20)
		return notify_fail("你的基本内功火候还不够，无法领会浩气苍冥功。\n");


	return 1;
}


int practice_skill(object me)
{
	return notify_fail("浩气苍冥功只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
	return __DIR__"cangming-gong/" + func;
}
