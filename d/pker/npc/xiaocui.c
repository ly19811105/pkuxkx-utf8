inherit NPC;
inherit F_DEALER;
#include <ansi.h>
void create()
{
	set_name("小翠", ({ "xiao cui","cui"}));
	set("shen_type", 0);

	set("per", 25);
	set("gender", "女性");
	set("age", 25);
	set("long",
		"一个年轻的妓女，还算有几分姿色，但是颦笑之间总是带着些倦意\n"
		);
	set("combat_exp", 500);
	set("attitude", "friendly");
	
	
	

	set("shen_type",1);set("score",200);setup();
	carry_object("/clone/misc/cloth")->wear();
}