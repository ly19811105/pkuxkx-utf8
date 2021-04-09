// zhu.c 朱熹
// CLEANSWORD 1996/2/2

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("孙悟空", ({ "sun wukong", "wukong", "sun" }));
        set("long", "花果山美猴王。\n");
	set("gender", "男性");
	set("age", 65);
     set("start_room","/d/city/shuyuan");

	set_skill("literate", 300);

	set_skill("unarmed", 80);
	set_skill("dodge", 80);
	set_skill("parry", 80);
	set_temp("apply/attack", 80);
	set_temp("apply/defense", 80);
	set_temp("apply/damage", 20);

	set("combat_exp", 400000);
	set("shen_type", 1);
set("vendor_goods",({
__DIR__"obj/shu2",
"/d/city/obj/baodian",
}));
	setup();

	set("chat_chance", 3);
		carry_object("/d/riyuejiao/npc/obj/shuaiyitie");
}

void init()
{
    add_action("do_list","list");
    add_action("do_buy","buy");
}

int recognize_apprentice(object ob)
{
	if (!(int)ob->query_temp("mark/朱"))
		return 0; 
	ob->add_temp("mark/朱", -1);
	return 1;
}

int accept_object(object who, object ob)
{
	if (!(int)who->query_temp("mark/朱"))
		who->set_temp("mark/朱", 0);
	if (ob->query("money_id") && ob->value() >= 1000) {
		message_vision("朱熹同意指点$N一些读书写字的问题。\n", who);
		who->add_temp("mark/朱", ob->value() / 50);
		return 1;
	}
	return 0;
}
