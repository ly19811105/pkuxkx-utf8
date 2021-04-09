

inherit NPC;

void create()
{
	set_name("襄阳守军", ({ "shou jun", "jun" }));
	set("age", 22);
	set("gender", "男性");
        set("long", "蒙古即将大襄阳之际，这些将士们也忙得不亦乐乎。\n");
	set("attitude", "peaceful");
	set("str", 47);
	set("dex", 18);
	set("combat_exp", 20000);
	set("shen_type", 1);
	set_skill("unarmed", 60);
	set_skill("dodge", 80);
	set_skill("parry", 60);
	set_skill("blade", 50);
	set_skill("force", 100);
	set_temp("apply/attack", 40);
	set_temp("apply/defense", 40);
	set_temp("apply/damage", 20);
	set_temp("apply/armor", 40);

//	if (random(2) == 1) {
              set("chat_chance", 8);
              set("chat_msg", ({
                      (: random_move :),
              }));
//	}
//        set("chat_chance_combat", 10);
//	set("chat_msg_combat", ({
//		"官兵喝道：大胆刁民，竟敢造反不成？\n",
//		"官兵喝道：跑得了和尚跑不了庙，你还是快快束手就擒！\n",
//	}));
	setup();
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/d/xiangyang/npc/obj/junfu")->wear();
}

void init()
{
	object ob=this_player();
if(ob->query("id")=="menggu bing"||ob->query("id")=="menggu qibing"||ob->query("id")=="qianhu zhang")
{
this_object()->kill_ob(ob);
ob->kill_ob(this_object());
}
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
        object ob, me, obj, xytaskd;
	me=this_player();
if(!arg) return 0;
xytaskd=load_object("/adm/daemons/xytaskd.c");
if (xytaskd->query("begin"))  return 0;
if(!arg) return 0;
	ob=this_object();
	obj=present(arg,environment(me));
	me->set_temp("killed",1);
	ob->kill_ob(me);
	me->kill_ob(ob);
	return 1;
}
