// File		: fengwanli.c
// Created By	: iszt@pkuxkx, 2007-03-07

#include "setdizi.h"
#include <title.h>
void create()
{
        setcreate(240);

	set_name("封万里", ({ "feng wanli", "feng", "wanli", }));
	set("long",WHT
"这就是封万里。"NOR);
	set("age", 41);
	set("title","雪山派第六代弟子");
	set("nickname", HIR"风火神龙"NOR);
	set("gender","男性");
	set("str", 24);
	set("dex", 20);
	set("con", 21);
	set("int", 25);
	set("per", 27);

	add("inquiry", ([
		"name" : "在下白万剑，乃是父亲白自在所起的名字。",
		"here" : "这里就是雪山派凌霄城了。雪山派在此创派一百七十余年来，侠义之气代代相传，专门锄强扶弱。",
		"rumors" : "十年一度的腊八之祸还有一年就要重现江湖，在下担忧的很哪。",
	]));

	set("chat_chance_combat", 100);
	set("chat_msg_combat", ({
		(: perform_action, "liuchu" :),
		(: perform_action, "fengjian" :),
	}));
	create_family("雪山派",6,"长门弟子");

	setup();
	carry_object(__DIR__"obj/sword.c")->wield();
	carry_object(__DIR__"obj/changpao.c")->wear();

}

void attempt_apprentice(object ob)
{
	object me  = this_object();
	mapping fam = ob->query("family");

	if( me->query("betrayer") || (fam && fam["family_name"] != "雪山派"))
	{
		command("say 我不收带艺投师的弟子。" + RANK_D->query_respect(ob) +
				"若想投入我雪山派门下，可去找我的师弟师妹。\n");
		return;
	}
	if(fam && fam["generation"] == me->query("family/generation"))
	{
		command("say " + (ob->query("gender")=="男性" ? "师弟" : "师妹") +
			"说笑了，有什么疑难之处可以和师兄切磋切磋，拜师哪谈得上！");
		return;
	}
	if(ob->query_skill("xueshan-neigong", 1) < 120)
	{
		command("say 剑法若要精进，内功实是一大制约。你还是先去练练雪山内功罢。");
		return;
	}

	command("nod "+ ob->query("id"));
	CHANNEL_D->do_channel(me, "jh", ob->query("name")+"从今日起，投入我雪山派封万里门下，还请各方江湖朋友多加照顾。");
	command("recruit "+ ob->query("id"));
	ob->set("title", "雪山派第七代长门弟子");
//title系统记录玩家title by seagate@pkuxkx
	ob->set_title(TITLE_RANK, "雪山派第七代长门弟子");
	command("trip "+ ob->query("id"));
}