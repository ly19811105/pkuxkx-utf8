// Npc: /kungfu/class/shaolin/hui-ming.c
// Date: YZC 96/01/19

#include <ansi.h>

inherit NPC;
inherit F_MASTER;


void create()
{
	set_name("慧名尊者", ({
		"huiming zunzhe",
		"huiming",
		"zunzhe",
	}));
	set("long",
		"他是一位两鬓斑白的老僧，身穿一袭青布镶边袈裟。他身材略高，\n"
		"太阳穴微凸，双目炯炯有神。\n"
	);


	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 50);
	set("shen_type", 1);
	set("str", 30);
	set("int", 20);
	set("con", 27);
	set("dex", 22);
	set("max_qi", 600);
	set("max_jing", 300);
	set("neili", 600);
	set("max_neili", 600);
	set("jiali", 70);
	set("combat_exp", 200000);
	set("score", 200);

	set_skill("force", 80);
	set_skill("hunyuan-yiqi", 80);
	set_skill("dodge", 80);
	set_skill("shaolin-shenfa", 80);
	set_skill("strike", 80);     
	set_skill("banruo-zhang", 80);
	set_skill("claw", 80);
	set_skill("yingzhua-gong", 80);
	set_skill("parry", 80);
	set_skill("buddhism", 80);
	set_skill("literate", 80);

	map_skill("force", "hunyuan-yiqi");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("strike", "banruo-zhang");
	map_skill("claw", "yingzhua-gong");
	map_skill("parry", "yingzhua-gong");

	prepare_skill("claw", "yingzhua-gong");

	create_family("少林派", 38, "弟子");

	setup();

        carry_object("/d/shaolin/obj/hui-cloth")->wear();
}


#include "/kungfu/class/shaolin/hui.h"

