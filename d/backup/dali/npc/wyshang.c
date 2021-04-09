//Cracked by Roath
// wyshang.c 乌夷商贩

inherit NPC;

void create()
{
	set_name("乌夷商贩", ({ "shang fan", "shang", "fan" }) );
	set("long", "一位乌夷族的商贩，挑着一担皮毛野味在贩卖。\n");

	set("age", 25);
	set("gender", "男性");
	set("dalivictim",1);

	set("str", 20);
	set("cor", 20);

    set("combat_exp", 1000);
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
	carry_object("/d/dali/npc/obj/wyhui.c")->wear();
}
