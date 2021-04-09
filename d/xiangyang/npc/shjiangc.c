inherit NPC;
void create()  
{	set_name("巡城守将", ({ "shou jiang","jiang" }));
	set("gender", "男性");
	set("age", random(10) + 30);
	set("str", 45);
	set("dex", 26);
	set("long", "他站在那里，浑身杀气,让人心惊胆寒。\n");
	set("combat_exp", 100000);
	set("shen_type", 1);
	set("attitude", "peaceful");

	set_skill("unarmed", 90);
	set_skill("force", 80);
	set_skill("halberd", 90);
	set_skill("lujia-ji", 90);
	set_skill("dodge", 80);
	set_skill("parry", 80);

	map_skill("halberd", "lujia-ji");
	map_skill("parry", "lujia-ji");

	set_temp("apply/attack", 50);
	set_temp("apply/defense", 50);
	set_temp("apply/armor", 50);
	set_temp("apply/damage", 30);

	set("neili", 800); 
	set("max_neili", 800);
	set("jiali", 50);
       
        set("chat_chance", 8);
        set("chat_msg", ({   
    
       "近来城里常有鞑子兵混入,要是谁看到,速速报官.\n
        否则,以通敌论处!!!!\n",
     (: random_move :)    
    }) );

        setup();
	carry_object("/clone/weapon/fangtianji")->wield();
	carry_object(__DIR__"obj/tiejia")->wear();

}

void init()
{
	object ob=this_player();
	::init();
	if(ob->query_temp("killed")) call_out("kill_ob",1,ob);
	add_action("do_kill","kill");
}

int accept_fight(object me)
{
	command("say 大爷我正想找人杀呐，今天算你倒霉。\n");
	me->apply_condition("killer", 100);
	kill_ob(me);
	return 1;
}
int do_kill(string arg)
{
    object ob, me, obj,xytaskd;

    if (!arg) return 0;
    me = this_player(); 
    xytaskd=load_object("/adm/daemons/xytaskd.c");
    if (xytaskd->query("begin"))  return 0;
	ob=this_object();
	obj=present(arg,environment(me));
	me->set_temp("killed",1);
	ob->kill_ob(me);
	me->kill_ob(ob);
	return 1;
}
