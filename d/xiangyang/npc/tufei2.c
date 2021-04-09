// Modified by iszt@pkuxkx, 2007-05-21

#include <ansi.h>

inherit NPC;

void create()
{
	set_name(BLK"土匪"NOR, ({ "tu fei", "fei" }));
	set("long", 
		"他就是在黑松岭上占山为王的土匪。\n"
	);
	set("gender", "男性");
	set("age", 25);
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("str", 30);
	set("int", 15);
	set("con", 28);
	set("dex", 28);
	set("max_qi", 300);
	set("max_jing", 300);
	set("neili", 800);
	set("max_neili", 800);
	set("jiali", 15);
	set("combat_exp", 20000);
	set("score", 20000);

	set_skill("force", 60);
	set_skill("dodge", 60);
	set_skill("strike", 50);
	set_skill("parry", 50);
	set_skill("blade", 70);
	set_skill("staff", 80);
	set_skill("tianshan-zhang", 80);
	map_skill("force", "huagong-dafa");
	map_skill("dodge", "zhaixinggong");
	setup();
	carry_object("/clone/weapon/gangdao")->wield();
}

void init()
{
	::init();       

	if(userp(this_player()))
		call_out("kill_ob", 1, this_player());

	remove_call_out("do_dest");
	call_out("do_dest", 14, this_object());
}

void do_dest(object ob)
{
	if (!ob || environment(ob) != environment())
	return;
	message_vision("$N和同伴使了个眼色，一转身，钻进了茂密的松林。\n", ob);
	destruct(ob);
}