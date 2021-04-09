// su.c 苏荃

#include <ansi.h>
inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;

int ask_tuijiao();
void create()
{
	set_name("苏荃", ({ "su quan", "su" }));
	set("title",  HIY"神龙教"NOR"教主夫人" );
	set("long", "她就是神龙教教主洪安通的夫人。\n");
	set("gender", "女性");
	set("age", 23);
	set("attitude", "friendly");
	set("shen_type", -1);
	set("str", 35);
	set("int", 30);
	set("con", 30);
	set("dex", 38);
	
	set("max_qi", 4000);
	set("max_jing", 3000);
	set("neili", 4000);
	set("max_neili", 4000);
	set("jiali", 100);
	set("combat_exp", 1000000);
	set("score", 400000);

        set_skill("force", 150);
	set_skill("shenlong-xinfa", 190);
	set_skill("shedao-xinfa", 150);
        set_skill("dodge", 180);
	set_skill("yixingbu", 160);
        set_skill("hand", 150);
        set_skill("strike", 180);
	set_skill("shenlong-bashi", 150);
	set_skill("huagu-mianzhang", 120);
        set_skill("parry", 150);
        set_skill("staff", 150);
	set_skill("shedao-qigong", 120);
	set_skill("literate", 100);
//	set_skill("meiren-sanshi", 180);

	map_skill("force", "shenlong-xinfa");
	map_skill("dodge", "yixingbu");
	map_skill("strike", "huagu-mianzhang");
	map_skill("hand", "shenlong-bashi");
	map_skill("parry", "shedao-qigong");
        map_skill("staff", "shedao-qigong");
	prepare_skill("strike", "huagu-mianzhang");
	prepare_skill("hand", "shenlong-bashi");

	create_family("神龙教",2,"弟子");

        set("inquiry", ([
		"神龙教" :  "\n一般人是入不了我神龙教的(join shenlongjiao).\n",
		"入教"   :  "\n一般人是入不了我神龙教的(join shenlongjiao).\n",
		"退教"   :    (: ask_tuijiao :),
		"口号"   : "\n万年不老!永享仙福!寿与天齐!文武仁圣!\n",
		"rujiao" :  "\n一般人是入不了我神龙教的(join shenlongjiao).\n",
		"tuijiao": (: ask_tuijiao :),
        ]));
	set("chat_chance_combat", 50);  
	set("chat_msg_combat", ({
		(: command("smile") :),
		(: command("haha") :),
		(: command("chat 凭你这" + RANK_D->query_rude(this_player())+",也敢在太岁爷头上动土?\n") :),
		(: command("say 你活得不耐烦了找死啊？\n") :),
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chang2" :),
                (: perform_action, "staff.chang2" :),
                (: perform_action, "staff.chang2" :),
                (: perform_action, "staff.chang3" :),
                (: perform_action, "staff.chang3" :),
                (: perform_action, "staff.chang3" :),
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
        }) );
	setup();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver", 50);
}

void init()
{
	object ob;

	::init();

	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 50, ob);
	}
}

void greeting(object ob)
{
	object obj;
        if (interactive(ob))
        {
	if (obj = present("usedgao", ob))          
	   set("combat_exp",500000);
	   set("qi",10);
	   set("jing",10);
	}
	return;
}

void attempt_apprentice(object ob)
{
	if (ob->query("party/party_name") != HIY "神龙教" NOR ) {
		command("say 你不是本教教众, 想来找死啊!");
		return;
	}
	if ((int)ob->query_skill("shenlong-xinfa",1) < 60 ) {
		command("say 你的本门内功心法太低了，还是努努力先提高一下吧!");
		return;
	}
	if ((int)ob->query_skill("shedao-qigong",1) < 60 ) {
		command("say 你的本门杖法太低了，还是努努力先提高一下吧!");
		return;
	}
	if ((int)ob->query("shen") > -10000  ) {
	command("say 我神龙教与世隔绝，向来不与您这种白道人物打交道，您请回吧！");
		return;
	}
	command("say 很好，很好。");
	command("recruit " + ob->query("id"));
}

int ask_tuijiao()
{
        object ob;
        ob=this_player();

        if(ob->query("party/party_name") != HIY "神龙教" NOR )
        {
        message_vision("苏荃莞尔一笑，对$N说道：你还没加入我神龙教呢，就想退教？\n",ob);
                return 1;
        }
        if(ob->query("family/family_name") == "神龙教" )
        {
message_vision("苏荃板起俏脸对$N说道：你已经是我神龙弟子，如何能退教？\n", ob);
                return 1;
        }
        command("look "+ob->query("id"));
        command("sigh ");
        command("nod ");
        command("say 异日你不要撞在我手上! ");
        ob->delete("party");
        ob->delete("rank");
        ob->delete("level");
        return 1;
}

