// cui.c 崔员外

inherit NPC;
inherit F_MAILQUEST;

void create()
{
	set_name("崔员外", ({ "cui yuanwai", "cui" }));
	set("gender", "男性");
	set("age", 55);

	set_skill("unarmed", 50);
   set("start_room","/d/city/houyuan");
	set_skill("dodge", 50);
	set_skill("parry", 50);
	set_temp("apply/attack", 40);
	set_temp("apply/defense", 40);
	set_temp("apply/damage", 10);

	set("combat_exp", 25000);
	set("shen_type", -1);
	setup();
	add_money("silver", 50);
	carry_object(__DIR__"obj/yaoshi");
}
	
