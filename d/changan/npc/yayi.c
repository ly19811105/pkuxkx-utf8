// yayi.c  官府衙役
inherit NPC;
inherit F_MAILQUEST;

void create()
{
	set_name("衙役", ({ "ya yi", "ya" }));
	set("gender", "男性");
	set("age", 25);

	set("long", "一个高大威猛的汉子，因为久在官府做事，脸上已经磨炼得毫无表情。\n");
	set("combat_exp", 7500);
   set("start_room","/d/city/yamen");
	set("shen_type", 1);
        set_skill("unarmed", 30);
        set_skill("dodge", 30);
	setup();
	carry_object("/d/city/npc/obj/yayifu")->wear();
}
	
