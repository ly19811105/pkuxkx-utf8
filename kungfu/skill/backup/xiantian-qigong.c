// xiantian-qigong.c 先天气功
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("xiantian-qigong", 1);
        int t = 1, j;
        if (lvl<=100)
                for (j = 1; j < lvl / 10; j++)
                     t*=2;

        if ( me->query("gender") == "无性")
                return notify_fail("你无根无性，阴阳不调，难以修行玄门正宗的先天气功。\n");

        if ( me->query("class") == "bonze" )
                return notify_fail(RANK_D->query_respect(me)+"欲修我道家玄门气功，怎又去入了佛门？\n");

        if ((int)me->query_skill("force", 1) < 10)
                return notify_fail("你的基本内功火候还不够。\n");

        if(lvl<=100)
        {
                if (lvl > 10 && (int)me->query("shen") < t * 100)
                        return notify_fail("你的侠义正气太低了。\n");
        }
        else
        {
                if ((int)me->query("shen") < (51200 + (lvl - 100) * 1000))
                        return notify_fail("你的侠义正气太低了。\n");
        }
	if (
	me->query_skill("bahuang-gong",1)
	|| me->query_skill("beiming-shengong",1)
	|| me->query_skill("bibo-shengong",1)
	|| me->query_skill("hamagong",1)
	|| me->query_skill("huagong-dafa",1)
	|| me->query_skill("huntian-qigong",1)
	|| me->query_skill("hunyuan-yiqi",1)
	|| me->query_skill("jiuyang-shengong",1)
	|| me->query_skill("kuihua-xinfa",1)
	|| me->query_skill("kurong-changong",1)
	|| me->query_skill("linji-zhuang",1)
	|| me->query_skill("longxiang",1)
 	|| me->query_skill("shenlong-xinfa",1)
	|| me->query_skill("taiji-shengong",1)
	||  me->query_skill("xiaowuxiang",1)
	|| me->query_skill("yijinjing",1)
	|| me->query_skill("yunv-xinfa",1)
	|| me->query_skill("yunlong-shengong",1)   
	|| me->query_skill("cangming-gong",1) 
	|| me->query_skill("guangming-shenghuogong",1)    
	|| me->query_skill("shenyuan-gong",1)   
	|| me->query_skill("huashan-neigong",1)   
	|| me->query_skill("zixia-shengong",1) 
	|| me->query_skill("xuantian-wuji",1)  
	|| me->query_skill("guiyuan-tunafa",1) )
                return notify_fail("你不先散了别派内功，怎能学习先天气功？！\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("先天气功只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"xiantian-qigong/" + func;
}

