// Npc: /d/shaolin/npc/xiao-ci.c
// Date: YZC 96/01/19

#include <ansi.h>

inherit NPC;
inherit F_AQUESTMASTER;


void create()
{
	set("title", HIR "少林" NOR + RED "小沙弥" NOR);
	set_name("净慈", ({
		"xiao shami",
		"xiao",
		"shami",
	}));
	set("long",
		"他是一位未通世故的少年和尚，脸上挂着天真的稚笑。\n"
	);


	set("gender", "男性");
	set("attitude", "peaceful");
	set("class", "bonze");

	set("age", 15);
	set("shen_type", 1);
	set("str", 20);
	set("int", 20);
	set("con", 20);
	set("dex", 20);
	set("max_qi", 100);
	set("max_jing", 100);
	set("neili", 100);
	set("max_neili", 100);
	set("combat_exp", 500);
	set("score", 100);

        set("no_get", 1);
	set_skill("force", 15);
	set_skill("dodge", 15);
	set_skill("unarmed", 15);
	set_skill("parry", 15);


	setup();

}

void init()
{
add_action("give_wsquest","quest");
}

