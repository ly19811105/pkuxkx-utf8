// File		: chengzixue.c
// Created By	: iszt@pkuxkx, 2007-03-06

#include "setdizi.h"

void create()
{
        setcreate(240);

	set_name("成自学", ({ "cheng zixue", "cheng", "zixue", }));
	set("long", "成自学。\n");

	set("age", 50);
	set("gender", "男性");
	set("str", 25);
	set("dex", 18);
	set("con", 21);
	set("int", 23);
	set("per", 20);

	add("inquiry", ([
		"name" : "我成自学的名字又岂是你等小辈问得的！",
	]));

	set("chat_chance_combat", 100);
	set("chat_msg_combat", ({
		(: perform_action, "liuchu" :),
		(: perform_action, "fengjian" :),
	}));
	create_family("雪山派", 5, "弟子");

	setup();
	carry_object(__DIR__"obj/sword.c")->wield();
	carry_object(__DIR__"obj/changpao.c")->wear();

}

void attempt_apprentice(object ob)
{
	object me  = this_object();
	mapping fam = ob->query("family");

	if ( !fam || fam["family_name"] != "雪山派")
	{
		command("haha");
		command("say 算你有眼光，知道老子天下第一。你先去找我的徒弟们或者孙女阿绣学两招吧。");
		return;
	}
	if(fam["master_name"] != "白万剑" || fam["master_id"] != "bai wanjian")
	{
		command("say 你先去找剑儿学两招吧。");
		return;
	}
	if(fam["generation"] <= me->query("family/generation"))
	{
		command("chat* bug");
		command("chat " + ob->name() + "你在利用bug！");
		return;
	}
	if(ob->query("betrayer"))
	{
		command("say 我平生最恨背信弃义之人，你屡次叛师，嘿嘿！");
		return;
	}
	if(ob->query_int() < 40)
	{
		command("say 就凭你的悟性？罢了，再去读几年书吧。");
		return;
	}
	if(ob->query_skill("xueshan-jianfa", 1) < 250)
	{
		command("say 剑儿这个小混蛋，把你的剑法教成这样就让你来找我？");
		return;
	}
	if(ob->query_skill("xueshan-neigong", 1) < 160)
	{
		command("say 你的本门内功功力未到，再去练练罢。");
		return;
	}
	if(pow(ob->query_skill("sword", 1)/8, 3)*100 < ob->query("combat_exp"))
	{
		command("say 你的剑法太过疏于练习，再去练练罢。");
		return;
	}
	if(ob->query("score") < 1500)
	{
		command("say 你为雪山派的贡献不够，再去锤炼几年罢。");
		return;
	}

	command("nod "+ ob->query("id"));
	command("chat* haha "+ob->query("id"));
	command("chat* nod1");
	command("recruit "+ ob->query("id"));
	ob->set("title", "雪山派第六代长门弟子");
}