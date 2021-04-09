// Rewrote by iszt@pkuxkx, 2007-02-12

inherit NPC;

void create()
{
	set_name("王裴氏", ({ "wang peishi", "wang" }));
	set("gender", "女性");
	set("age", 41);
	set("long", "她是王员外的夫人，小王贵的母亲。\n");

	set("combat_exp", 1000);
	set("shen_type", 1);

	set("attitude", "peaceful");

	set_skill("unarmed", 20);
	set_skill("dodge", 20);
	set_temp("apply/attack", 10);
	set_temp("apply/defense", 10);

	setup();
	carry_object("/clone/misc/cloth")->wear();
}