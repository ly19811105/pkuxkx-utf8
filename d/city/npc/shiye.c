// shiye.c 知府师爷

inherit NPC;

void create()
{
	set_name("谭友纪", ({ "tan youji", "tan" }));
	set("title", "知府师爷");
	set("gender", "男性");
	set("age", 57);

	set("combat_exp", 30000);
        set_skill("unarmed", 50);
        set_skill("dodge", 60);
        set_temp("apply/attack",  20);
        set_temp("apply/defense", 20);
        set_temp("apply/damage",  20);
	set("shen_type", 0);
	set("shen_type",1);set("score",500);setup();
}
	
