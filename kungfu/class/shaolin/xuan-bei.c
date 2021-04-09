// Npc: /kungfu/class/shaolin/xuan-bei.c
// Date: YZC 96/01/19

#include <ansi.h>
#include <title.h>
inherit NPC;
inherit F_MASTER;


void create()
{
	set_name("玄悲大师", ({
		"xuanbei dashi",
		"xuanbei",
		"dashi",
	}));
	set("long",
		"他是一位白须白眉的老僧，身穿一袭银丝棕黄袈裟。他身材甚高，\n"
		"但骨瘦如柴，顶门高耸，双目湛然有神。\n"
	);


	set("nickname", "达摩院主持");
	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 70);
	set("shen_type", 1);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	set("max_qi", 2000);
	set("max_jing", 1000);
	set("neili", 2500);
	set("max_neili", 2500);
	set("jiali", 150);
	set("combat_exp", 1000000);
	set("score", 100000);

	set_skill("force", 180);
	set_skill("hunyuan-yiqi", 180);
	set_skill("dodge", 180);
	set_skill("shaolin-shenfa", 180);
	set_skill("hand", 180);
	set_skill("claw", 180);
	set_skill("blade", 180);
	set_skill("sword", 180);
	set_skill("parry", 180);
	set_skill("qianye-shou", 180);
	set_skill("longzhua-gong", 180);
	set_skill("cibei-dao", 180);
	set_skill("damo-jian", 180);
	set_skill("buddhism", 180);
	set_skill("literate", 180);

	map_skill("force", "hunyuan-yiqi");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("hand", "qianye-shou");
	map_skill("claw", "longzhua-gong");
	map_skill("blade", "cibei-dao");
	map_skill("sword", "damo-jian");
	map_skill("parry", "cibei-dao");

	prepare_skill("hand", "qianye-shou");
	prepare_skill("claw", "longzhua-gong");

	create_family("少林派", 36, "弟子");

	setup();

        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

void attempt_apprentice(object ob)
{
	object me; 
	mapping ob_fam, my_fam;
	string name, new_name;

	me = this_object();
	my_fam  = me->query("family");

	name = ob->query("name");

	if (!(ob_fam = ob->query("family")) || ob_fam["family_name"] != "少林派")
	{
		command("say " + RANK_D->query_respect(ob) + "与本派素无来往，不知此话从何谈起？");
		return;
	}

	if ( (string)ob->query("class")!="bonze" && ob_fam["family_name"] == "少林派") 
	{
		command("say " + RANK_D->query_respect(ob) + "是俗家弟子，不能在寺内学艺。");
		return;
	}

	if ( ob_fam["generation"] <= my_fam["generation"] )
	{
		command("say " + RANK_D->query_respect(ob) + "，贫僧哪里敢当 !");
		return;
	}

	if ( ob_fam["generation"] == (my_fam["generation"] + 1) && name[0..0] == "澄")
	{
		command("say " + ob_fam["master_name"] + "的徒弟怎麽跑到我这儿来了，哈哈哈 !");
		command("recruit " + ob->query("id"));
	}
	else
	{
		command("say " + RANK_D->query_respect(ob) + "，你辈份不合，不能越级拜师。");
		return;
	}

	return;
}


void recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
        {
          ob->set("title",HIR "少林" NOR + CYN "达摩院" NOR + RED "弟子" NOR);
//title系统记录玩家title by seagate@pkuxkx
	        ob->set_title(TITLE_RANK, ob->query("title"));
	      }
        return;
}

void re_rank(object student)
{
        student->set("title",HIR "少林" NOR + CYN "达摩院" NOR + RED "弟子" NOR);
//title系统记录玩家title by seagate@pkuxkx
	      student->set_title(TITLE_RANK, student->query("title"));
        return;
}
