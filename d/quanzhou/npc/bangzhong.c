// biaotou.c 财主管家

inherit NPC;

void create()
{
	set_name("巨鲸帮帮众" , ({"bang zhong" , "bang"}));
	set("gender", "男性");
	set("age", 35);

	set("combat_exp", 5000);
	set("shen_type", 1);

	set_skill("unarmed", 30);
	set_skill("blade", 40);
	set_skill("parry", 30);
	set_skill("dodge", 30);
	
	set_temp("apply/attack", 15);
	set_temp("apply/defense", 15);
	set_temp("apply/damage", 20);

	setup();
	carry_object("/d/city/npc/obj/gangdao")->wield();
	carry_object(__DIR__"obj/cloth")->wear();
}
	
