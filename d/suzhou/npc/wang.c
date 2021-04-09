// wang.c

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("王合计", ({ "wang heji", "heji", "wang" }));
	set("title", "当铺老板");
	set("shen_type", 0);

	set("gender", "男性");
	set_max_encumbrance(100000000);
	set("age", 35);
	set("long", "他带着一脸诡秘、奸诈的笑容。\n");
	set("no_get_from", 1);

	set_skill("unarmed", 60);
	set_skill("dodge", 60);
	set_temp("apply/attack", 30);
	set_temp("apply/attack", 30);
	set_temp("apply/damage", 15);

	set("combat_exp", 50000);
	set("attitude", "friendly");
	
	set("shen_type",1);set("score",200);setup();
//	carry_object("/clone/misc/cloth")->wear();
}


void die()
{
	message_vision("\n$N死了。\n", this_object());
	destruct(this_object());
}
