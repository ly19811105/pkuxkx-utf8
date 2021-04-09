// File		: feizei.c
// Created By	: iszt@pkuxkx, 2007-03-28
// Modified by	: kiden@pkuxkx

#include <ansi.h>

inherit FAMILY_NPC;

varargs void wield_weapon(string weapon);
void die();

void create()
{
	set_name("飞贼", ({ "fei zei", "zei"}) );
	set("gender", "男性" );
	set("age", 22+random(22));
	set("long", "这是一个武艺高强的飞贼，你还是离他远一点吧。\n"
		"他的背上有一个小小包裹，看样子是才偷了什么东西在手。\n");
	set("per",10+random(20));
	set("kar",30);
	set("str",30);
	set("con",30);
	set("dex",30);
	set("int",30);
	set("attitude", "heroism");
	set("rank_info/rude", "小毛贼");
	add("inquiry", ([
		"name" : "走开点，小心老子发飙！",
		"here" : "不知道！",
		"rumors" : "嘿嘿，想知道你的祭日么？",
	]));
	set("chat_chance", 5);
	set("chat_msg", ({
		(: random_move :),
	}) );
	set("chat_chance_combat", 100);
	family_skill(this_object(), "random", 300, 1);
	set("max_qi",  3000);
	set("eff_qi",  3000);
	set("qi",      3000);
	set("max_jing",3000);
	set("eff_jing",3000);
	set("jing",    3000);
	set("max_jingli",3000);
	set("jingli", 3000);
	set("max_neili", 3000);
	set("neili", 3000);
	set("jiali",300);
	set("combat_exp",5000000);
	setup();
	carry_object("/clone/armor/bianfuxuejia")->wear();
	switch(random(14))
	{
	case 0: carry_object("/clone/weapon/menpai/dagou-bang.c"); break;
	case 1: carry_object("/d/shaolin/obj/yijinjing.c"); break;//易筋经内功篇，读hunyuan-yiqi 101-301
	case 2: carry_object("/clone/weapon/menpai/hantie-zhang.c"); break;
	case 3: carry_object("/d/shaolin/obj/puti-zi"); break;
	case 4: carry_object("/clone/weapon/menpai/damo-zhang.c"); break;
	case 5: carry_object("/clone/weapon/menpai/lingshe-zhang.c"); break;
	case 6: carry_object("/clone/weapon/menpai/shenlong-bian.c"); break;
	case 7: carry_object("/d/qilincun/obj/liquan"); break;
	case 8: carry_object("/d/qilincun/obj/liquan"); break;
	case 9: carry_object("/d/lingxiao/obj/iceblade"); break;
	default : add_money("gold", 5+random(20)); break;
	}
	wield_weapon();
}

void init()
{
	command("wield all");
}

void start_busy(mixed new_busy, mixed new_interrupt)
{
	if(intp(new_busy) && new_busy > 5)
		::start_busy(4+random(3));
}

void unconcious()
{
	die();
}

void die()
{
	object me = query_temp("last_damage_from");
	if(!objectp(me) || !present(me, environment()))
	{
		::die();
		return;
	}
	message_vision("$N为民除害，感觉自己修为有所增进。\n", me);
	me->add("combat_exp",1000+random(1000));
	me->add("potential",500);
	me->add("repute",200);
	::die();
}

varargs void wield_weapon(string weapon)
{
	if(!weapon && query("use_weapon1"))
		wield_weapon(query("use_weapon1"));
	if(!weapon && query("use_weapon2"))
		wield_weapon(query("use_weapon2"));
	if(!weapon)
		return;
	switch(weapon)
	{
	case "sword":
		carry_object("/clone/weapon/changjian");
		break;
	case "blade":
		carry_object("/clone/weapon/gangdao");
		break;
	case "staff":
		carry_object("/clone/weapon/gangzhang");
		break;
	case "whip":
		carry_object("/clone/weapon/changbian");
		break;
	case "zhen":
		set("gender", "无性");
		carry_object("/d/city/obj/flower_shoe");
		carry_object("/d/city/obj/pink_cloth");
		carry_object("/d/city/obj/goldring");
		carry_object("/d/city/obj/necklace");
		carry_object("/d/quanzhou/obj/xiuhua");
		carry_object("/d/riyuejiao/obj/xiuhuajia");
		break;
	case "dagger":
		carry_object("/clone/weapon/bishou");
		break;
	case "hammer":
		carry_object("/d/dalunsi/npc/obj/iron-falun");
		break;
	default:
		break;
	}
	return;
}