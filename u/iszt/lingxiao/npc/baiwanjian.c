// File		: baiwanjian.c
// Created By	: iszt@pkuxkx, 2006-08-16

#include "setdizi.h"

void create()
{
        setcreate(270);

	set_name("白万剑", ({ "bai wanjian", "bai", "wanjian", "jian" }));
	set("long",WHT
"这就是威震西陲、剑法无双，武林中大大有名的"HIW"「气寒西北」"NOR+WHT"白万剑。\n"
"白万剑是雪山派掌门人"HIC"「威德先生」白自在"NOR+WHT"的长子，同辈师兄弟均以万字排行，\n"
"他名字居然叫到「白万剑」，足见其剑法之高，而白自在对儿子的武功也\n"
"确是着实得意，才以此命名。他与风火神龙封万里合称「雪山双杰」。\n"NOR);
	set("age", 41);
	set("nickname", HIW"气寒西北"NOR);
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
		command("say "+ (ob->query("gender")=="男性" ? "师弟" : "师妹") +
			"说笑了，有什么疑难之处可以和师兄切磋切磋，拜师哪谈得上！");
		command("smile");
		return;
	}
	if(ob->query_skill("xueshan-neigong", 1) < 120)
	{
		command("say 剑法若要精进，内功实是一大制约。你还是先去练练雪山内功罢。");
		return;
	}

	command("nod "+ ob->query("id"));
	command("chat "+ob->query("name")+"从今日起，投入我雪山派白万剑门下，还请各方江湖朋友多加照顾。\n");
	command("recruit "+ ob->query("id"));
	ob->set("title", "雪山派第七代长门弟子");
	command("trip "+ ob->query("id"));
}