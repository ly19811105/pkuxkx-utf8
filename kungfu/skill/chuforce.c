// chuforce.c 楚氏气功
// By Jason

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int i = (int)me->query_skill("chuforce", 1);
	int t = 1, j;

	if(i <= 100)
		for (j = 1; j < i / 10; j++)
			t *= 2;

	if ( me->query("gender") == "无性" && i > 49)
		return notify_fail("你无根无性，阴阳不调，难以领会高深的楚氏气功。\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的基本内功火候还不够，还不能学习楚家内功。\n");

	

	if ( me->query_skill("bihai-shengong",1)
	|| me->query_skill("beiming-shengong",1)
	|| me->query_skill("bahuang-gong",1)
	|| me->query_skill("hamagong",1)
	|| me->query_skill("huagong-dafa",1)
	|| me->query_skill("huntian-qigong",1)
	|| me->query_skill("hunyuan-yiqi",1)
	|| me->query_skill("longxiang",1)
	|| me->query_skill("jiuyang-shengong",1)
	|| me->query_skill("taiji-shengong",1)
	|| me->query_skill("xiaowuxiang",1)
//	|| me->query_skill("zixia-shengong",1) 
	|| me->query_skill("yunlong-shengong",1)
	|| me->query_skill("cangming-gong",1) )
		return notify_fail("你不先散了别派内功，怎能学楚氏气功？！\n");

	return 1;
}

int practice_skill(object me)
{
	return notify_fail("楚氏气功只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"chuforce/" + func;
}
