// 清军细作

#include <ansi.h>

inherit __DIR__"qingbing_base-2.c";

void create()
{
	
	int i= random(2);

	set_name(surname[random(sizeof(surname))]+"."+givenname[random(sizeof(givenname))], ({ "xi zuo", "spy"}));
	set("title", title[random(sizeof(title))]+"细作");
	set("gender", i?"男性":"女性");
	set("age", 30+random(30));

	set("long","这是"+query("title")+query("name")+"。\n");
	set("attitude", "peaceful");
	set("combat_exp", 5000000);
	set("str", 20+random(5));
	set("int", 20+random(5));
	set("con", 20+random(5));
	set("dex", 20+random(5));
	set("max_qi", 20000);
	set("max_jing", 20000);
	set("max_neili", 5000);
	set("max_neili", 20000);
	set("neili", 5000);
	set("neili", 20000);
    set("qingqi",1);
	set_temp("apply/armor", 100);
	set("jingli", 20000);
	set("max_jingli", 20000);
	set("random_npc",1);
    if (random(300)>149)
	{
		set_skill("dodge",500);
		set_skill("parry",500);
		set_skill("force",500);
		set_skill("strike",500);
		set_skill("longfeng-xiang",500);
		set_skill("bixue-xinfa",500);
		set_skill("juehu-zhang",500);
		map_skill("force", "bixue-xinfa");
		map_skill("dodge", "longfeng-xiang");
		map_skill("strike", "juehu-zhang");
		map_skill("parry", "juehu-zhang");
		prepare_skill("strike", "juehu-zhang");
	}
	else 
	{
		set_skill("dodge",500);
		set_skill("parry",500);
		set_skill("force",500);
		set_skill("claw",500);
		set_skill("longfeng-xiang",500);
		set_skill("bixue-xinfa",500);
		set_skill("kuihua-zhua",500);
		map_skill("force", "bixue-xinfa");
		map_skill("dodge", "longfeng-xiang");
		map_skill("claw", "kuihua-zhua");
		map_skill("parry", "kuihua-zhua");
		prepare_skill("claw", "kuihua-zhua");
	}
	set("no_get", 1);
	setup();
	
	carry_object(__DIR__"items/cloth2")->wear();
	
	call_out("kill2", 1);
	call_out("selfcheck", 1);
}

int start_busy()
{
    return 1;
}
int add_busy()
{
    return 1;
}

int copy(object me)
{
	object ob=this_object();
	int i;
	int exp,qi,tempskill;
    mapping skills;
	if (me->query("max_qi")>=20000)
	{
		qi=20000;
	}
	if (me->query("max_qi")<20000)
	{
		qi=me->query("max_qi");
	}
	
	exp = me->query("combat_exp");
	
	if ( exp < 500000 )
		exp=500000;
	
	tempskill = to_int(pow(exp/100,0.333)*10);
    tempskill = tempskill/4*3;
    if (tempskill==0)
                 tempskill=10;
    skills = ob->query_skills();
    for (i=0;i<sizeof(skills);i++)
    {
        skills[keys(skills)[i]] = tempskill;
    }

	ob->set("max_qi", qi);
	ob->set("qi", qi);
	ob->set("max_jing", me->query("max_jing"));
	ob->set("jing", ob->query("max_jing"));
	ob->set("max_neili", me->query("max_neili"));
	ob->set("neili", ob->query("neili"));
	ob->set("combat_exp", exp);
	ob->set("max_jingli", me->query("max_jingli"));
	ob->set("jingli", ob->query("jingli"));
	return 1;
}

int gen(object me)
{
    object ob=this_object();
	
    if (!me||base_name(environment(me))!=base_name(environment(ob)))
    {
        message_vision("$N眼中一阵迷茫，转身回营了。\n",ob);
        destruct(ob);
        return 1;
    }
    else
    {
        message_vision(HIR"$N穿戴好盔甲，骑上战马，列队跟上"+me->query("name")+"。\n"NOR,ob);
        command("follow " + me->query("id"));
        return 1;
    }
}