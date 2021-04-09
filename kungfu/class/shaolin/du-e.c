// due.c

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

string ask_me();

void create()
{
	set_name("渡厄", ({ "du e", "e" }) );
	set("title", HIR "少林" NOR + CYN "长老" NOR);
	set("gender", "男性");
	set("age", 90);
	set("long",
		"这是一个面颊深陷，瘦骨零丁的老僧，他脸色枯黄，如同一段枯木。\n");

	set("attitude", "peaceful");
	set("combat_exp", 2000000);
	set("score", 200000);

	set("str", 30);
	set("int", 30);
	set("cor", 30);
	set("cps", 30);
	set("con", 30);

	set("qi", 4000);
	set("max_qi", 2000);
     set("no_get",1);
	set("neili", 4000);
	set("max_neili", 2000);
	set("jiali", 90);

	create_family("少林派", 35, "弟子");
	assign_apprentice("弟子", 0);

	set_skill("force", 200);
	set_skill("whip", 200);
	set_skill("parry", 200);
	set_skill("dodge", 200);

	set_skill("hunyuan-yiqi", 190);
	set_skill("buddhism", 200);
	set_skill("riyue-bian", 200);
	set_skill("shaolin-shenfa", 200);

	map_skill("force", "hunyuan-yiqi");
	map_skill("whip",  "riyue-bian");
	map_skill("parry", "riyue-bian");
	map_skill("dodge", "shaolin-shenfa");

	set("inquiry", ([
		"伏魔刀"     : (: ask_me :),
	]));

        set("count", random(5)-2);

	set("shen_type",1);set("score",10000);setup();

	carry_object("/d/shaolin/obj/changbian")->wield();
}

void init()
{
	object me, ob;
	mapping fam;

	me = this_player();
	ob = this_object();

	::init();
	if( interactive(me) ) 
	{
		if ( mapp(fam = me->query("family")) && fam["family_name"] == "少林派" 
                && fam["generation"] == 36 ) 
		{
	                me->set_temp("fighter", 1);
			return;
		}

		if ( mapp(fam = me->query("family")) && fam["family_name"] == "少林派" 
		&& fam["generation"] > 36 		
                && me->query("qi") < 50&&userp(me) ) 
		{
			me->move("/d/shaolin/qyping");
			me->unconcious();
			return;
		}

		COMBAT_D->do_attack(ob, me, query_temp("weapon") );
		
		me->set_temp("fighter", 1);

		ob->fight_ob(me);
		me->fight_ob(ob);

		call_out("halt", 10);

		return;
	}

	return;
}

void halt()
{
	command("say 好吧，大家住手！ 看这家伙有什么话要说！");
	command("halt");
}

string ask_me()
{
	mapping fam; 
	object ob;
	
	if ( !this_player()->query_temp("fighter") 
	||    this_player()->query("combat_exp") < 5000 )
	{
		this_object()->kill_ob(this_player());
		this_player()->kill_ob(this_object());
return "大胆鼠辈，乳臭未干，竟敢偷入金刚伏魔圈，且让老衲来超度与你！";
	}

	if ( present("fumo dao", this_player()) )
		return RANK_D->query_respect(this_player()) + 
		"宝刀只有一把，而且就在你身上，真是贪得无餍！";

	if ( present("fumo dao", environment()) )
		return RANK_D->query_respect(this_player()) + 
		"宝刀只有一把，而且就在这里任你取走，真是贪得无餍！";

	if ( present("jingang zhao", this_player()) || present("jingang zhao", environment()) )
		return RANK_D->query_respect(this_player()) + 
		"取了金刚罩，就不能再拿伏魔刀，莫要贪得无餍！";

	if (query("count") < 1)
		return "抱歉，你来晚了，伏魔刀已经给人取走了。";

	ob = new("/d/shaolin/obj/fumo-dao");
	ob->move(this_player());

	add("count", -1);

	message_vision("\n渡厄长笑一声，点点头，从身后的树洞里取出伏魔刀交给$N。\n\n", this_player());

	return "你既然能闯进金刚伏魔圈来，必然是当今武林中的非凡人物，这把刀是适逢其主了！";
}
#include "/kungfu/class/shaolin/du.h"
