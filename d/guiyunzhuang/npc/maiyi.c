//maiyi.c
//Made by:pingpang

inherit NPC;
void create()
{
	set_name("卖艺人",({"maiyi ren","ren","maiyi"}));
	set("long",@LONG
他是在太湖街上卖艺的兄弟俩中的老大。
LONG);
	set("gender","男性");
	set("shen_type",1);
	set("str",20);
	set("int",20);
	set("con",20);
	set("dex",20);
	set("combat_exp",20000);
	set_skill("unarmed",40);
	set_skill("force",40);
	set_skill("dodge",40);
	set_skill("parry",40);
	set_skill("cuff",50);
	set_skill("taiji-quan",50);
	map_skill("cuff","taiji-quan");
	map_skill("parry","taiji-quan");
	prepare_skill("cuff","taiji-quan");
	set("chat_chance_combat",20);
	set("chat_chance",3);
	setup();
	set("chat_msg",({"大家想看看武当山的太极拳吗?\n",
	"我给大伙儿练几招吧。\n",
	}));
	carry_object("/d/city/obj/cloth")->wear();
}
