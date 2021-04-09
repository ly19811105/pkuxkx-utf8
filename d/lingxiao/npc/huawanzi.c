// File		: huawanzi.c
// Created By	: iszt@pkuxkx, 2007-03-07

#include "setdizi.h"
inherit "/inherit/char/silver.c";
#include "/new_quest/qzhengpai.h"
#include "/new_quest/quest.h"
#include <title.h>
void create()
{
        setcreate(240);

	set_name("花万紫", ({ "hua wanzi", "hua", "wanzi", }));
	set("long", "这就是花万紫。\n");
	set("age", 41);
	set("gender", "女性");
	set("nick_name",HIM"寒梅女侠"NOR);
	set("str", 15);
	set("dex", 30);
	set("con", 20);
	set("int", 25);
	set("per", 22);

	add("inquiry", ([
		    "name" : "在下花万紫。",
        "quest":   (: ask_quest() :),
        "cancelquest":   (: ask_cancel() :),
        "取消任务":   (: ask_cancel() :),                
        "生活费" : (: ask_silver :),			
	]));
  set("silver_name", "生活费"); //例银的名称，默认为“例银”
  set("silver_factor", 1); //例银的数量因子，默认为1
  set("silver_family_skill", "xueshan-neigong"); //门派武功，提升此武功时可以领取例银，默认为parry
  set("msg_silver_firsttime", "我们凌霄城远处西北，弟子没什么挣钱的手段，以后生活费不够了就找我来领罢。"); //第一次打听例银的时候说的话
  set("msg_silver_record", "$N沉吟着，记下了些什么。\n"); //作记录时的描述\n
  set("msg_silver_check", "$N翻了翻记录，抬起头来。\n"); //检查记录时的描述\n
  set("msg_silver_mudage", "上回给你的生活费这么快就花完了吗？"); //时间未到不能领取时说的话
  set("msg_silver_paid", "给，记着在外边可别乱花银子哟。"); //领取成功时说的话
  set("msg_silver_score", "$N笑着说：「为雪山做了这么多贡献，真是辛苦你了。」\n"); //由于提升师门忠诚而领取例银时的描述\n
  set("msg_silver_skill", "$N打量了你一番，笑着说：「你的雪山内功又有长进了。」\n"); //由于提升师门武功而领取例银时的描述\n
  set("msg_silver_exp", "$N顽皮的拍了拍你的头。\n"); //由于提升经验而领取例银时的描述\n
  set("msg_silver_none", "你还是在凌霄城专心练武罢，别出去跑了。"); //领取例银条件均不满足时说的话
	create_family("雪山派", 6, "长门弟子");

	setup();
	setequip();
}

void attempt_apprentice(object ob)
{
	object me  = this_object();
	mapping fam = ob->query("family");

	if(fam && ob->query("betrayer")>1 && fam["family_name"] != "雪山派")
	{
		command("say 你屡次叛师，将师门之义一手抹煞，在外早已是臭名昭著。"
			"本门信义为先，岂能容你！\n");
		return;
	}
	if(fam && fam["generation"] == me->query("family/generation"))
	{
		command("say " + (ob->query("gender")=="男性" ? "师弟" : "师妹") +
			"说笑了，有什么疑难之处可以和我切磋切磋，拜师哪谈得上！");
		return;
	}
	if(fam && fam["generation"] < me->query("family/generation"))
	{
		command("say 师叔说笑了，晚辈怎敢收您为徒？");
		return;
	}
	if(ob->query("gender") != "女性")
	{
		command("say " + RANK_D->query_respect(ob) + "去找我的师兄们拜师罢。");
		return;
	}

	command("nod "+ ob->query("id"));
	command("recruit "+ ob->query("id"));
	ob->set("title", "雪山派第七代长门弟子");
//title系统记录玩家title by seagate@pkuxkx
	ob->set_title(TITLE_RANK, "雪山派第七代长门弟子");
}
