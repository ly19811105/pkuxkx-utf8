// huagong-dafa.c 化功大法c
// by yucao
// modified by cleansword
inherit FORCE;
int valid_enable(string usage) { return usage == "force"; }
int valid_learn(object me)
{
        int i = (int)me->query_skill("huagong-dafa", 1);
        int t = 1, j;
        for (j = 1; j < i / 10; j++) t*= 2;
        if ((int)me->query_skill("force", 1) < 10)
                return notify_fail("你的基本内功火候不足，不能学化功大法。\n");
        if (i > 10 && (int)me->query("shen") > t * 100)
                return notify_fail("学化功大法，要心狠手辣，奸恶歹毒，你可做得不
够呀！\n");
        if ( me->query_skill("buddhism",1) || me->query_skill("taoism",1) )
                return notify_fail("你练了秃驴牛鼻子们的心法，还学化功大法做什麽
！\n");
	if ( ((int)me->query_skill("handu-xinfa", 1)) < 100 )
		return notify_fail("你的寒毒心法火候还不够，无法领会化功大法。\n");
		
        if ( me->query_skill("hunyuan-yiqi",1)
        || me->query_skill("huntian-qigong",1)
        || me->query_skill("beiming-shengong",1)
        || me->query_skill("xixing-dafa",1)
        || me->query_skill("jiuyang-shengong",1)
        || me->query_skill("taiji-shengong",1) )
                return notify_fail("你不先散了别派内功，怎能学化功大法？！\n");
        return 1;
}
int practice_skill(object me)
{
        return notify_fail("化功大法只能用学(learn)的来增加熟练度。\n");
}
string exert_function_file(string func)
{
        return __DIR__"huagong-dafa/" + func;
}

string query_yinyang()
{
	return "太阴";
}
