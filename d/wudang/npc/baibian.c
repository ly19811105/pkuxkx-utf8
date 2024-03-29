// baibian.c

#include <ansi.h>

inherit NPC;

void create()
{
	seteuid(getuid());
	set_name("张三", ({ "zhang san", "zhang", "san", "bai bian" }) );
	set("title", HIY "百变道人" NOR);
	set("gender", "男性" );
	set("age", 50);
	set("long", "一位邋邋遢遢的道士。\n");
	set("attitude", "heroism");
	set("class", "taoist");

	set("str", 21);
	set("con", 30);
	set("int", 27);
	set("dex", 23);

	set("max_qi", 1200);
	set("max_jing", 500);
	set("neili", 4000);
	set("max_neili", 2000);
	set("jiali", 60);
	set("shen_type", -1);
	set("env/wimpy", 70);

	set_temp("apply/attack",  10);
	set_temp("apply/defense", 20);

	set("combat_exp", 200000);

	set_skill("force", 80); 
	set_skill("unarmed", 90);
	set_skill("sword", 90);
	set_skill("dodge", 100);
	set_skill("parry", 100);
	set_skill("taiji-quan", 90); 
	set_skill("taiji-jian", 90); 
	set_skill("taiji-shengong", 80); 
	set_skill("tiyunzong", 90);

	map_skill("force", "taiji-shengong");
	map_skill("unarmed","taiji-quan");
	map_skill("parry", "taiji-quan");
	map_skill("sword", "taiji-jian");
	map_skill("dodge", "tiyunzong");

	create_family("武当派", 3, "弟子");

	set("chat_chance", 8);
	set("chat_msg", ({
		(: random_move :)
	}) );

	setup();

	carry_object("/d/city/obj/gangjian")->wield();
	carry_object("/clone/misc/cloth")->wear();
	carry_object("/clone/misc/mask");
	add_money("silver",20);
        
}

void init()
{	
	object ob, me;
	mapping skill_status, map_status, hp_status;
	string *sname, *mname;
	int i;

	me = this_object();
	ob = this_player();

	::init();
/*
	if (me->is_fighting() || wizardp(ob)) return;

	remove_call_out("pretending");
	call_out("pretending", 10, ob);
	
	me->map_skill("unarmed");
	me->map_skill("dodge");
	me->map_skill("parry");

	if ( !(skill_status = ob->query_skills()) ) return;
	sname  = keys(skill_status);

	for(i=0; i<sizeof(skill_status); i++) {
		me->set_skill(sname[i], skill_status[sname[i]]);
	}

	if ( !(map_status = ob->query_skill_map()) ) return;
	mname  = keys(map_status);

	for(i=0; i<sizeof(map_status); i++) {
		me->map_skill(mname[i], map_status[mname[i]]);
	}
// Added by Hop, 1996.12.27
	hp_status = ob->query_entire_dbase();

	me->set("str", hp_status["str"]);
	me->set("int", hp_status["int"]);
	me->set("con", hp_status["con"]);
	me->set("dex", hp_status["dex"]);

	me->set("max_qi",    hp_status["max_qi"] * 2);
	me->set("eff_qi",    hp_status["eff_qi"] * 2);
	me->set("qi",        hp_status["eff_qi"] * 2);
	me->set("max_jing",  hp_status["max_jing"]);
	me->set("eff_jing",  hp_status["eff_jing"]);
	me->set("jing",      hp_status["eff_jing"]);
	me->set("max_neili", hp_status["max_neili"] * 2);
	me->set("neili",     hp_status["max_neili"] * 2);
	me->set("jiali",     hp_status["jiali"]);
	me->set("combat_exp",hp_status["combat_exp"] * 13 / 10);
*/
}

void pretending(object ob)
{

	object me = this_object();
 
	if(!ob || !userp(ob) || environment(ob) != environment()) return;

	switch( random(3) ) {
		case 0:
                       command("grin " + ob->query("id"));
                       command("pretend " + ob->query("id"));
                       command("exert recover");
		       break;
		case 1:
                       command("hi " + ob->query("id"));
                       command("exert heal");
                       command("exert recover");
		       break; 
		case 2:
                       command("stare " + ob->query("id"));
		       me->fight_ob(ob);
		       ob->fight_ob(me);
		       break;
	}
}
