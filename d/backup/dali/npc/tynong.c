//Cracked by Roath
// tynong.c 台夷农妇

inherit NPC;

void create()
{
	set_name("台夷农妇", ({ "nong fu", "woman", "nong" }) );
	set("long", "一位年轻的台夷农妇，在田里辛勤地劳作着。\n");

	set("age", 25);
	set("gender", "女性");
	set("dalivictim",1);

	set("str", 20);
	set("cor", 20);

    set("combat_exp", 1500);
	set("max_qi", 200);
	set("qi", 200);
	set_skill("dodge", 10);
	set_skill("parry", 10);
	set_temp("apply/attack", 10);
	set_temp("apply/damage", 5);
	set_temp("apply/armor", 5);
	
	set("attitude", "peaceful");
	set("shen_type", 1);

	setup();
	carry_object("/d/dali/npc/obj/tytongqun.c")->wear();
}
