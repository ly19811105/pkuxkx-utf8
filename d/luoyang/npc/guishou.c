// guishou.c 鬼手
// 2002 12 9 mudy
#include <ansi.h>
inherit NPC;
inherit F_DEALER;

void create()
{
	set_name(HIR"鬼手"NOR, ({ "gui shou", "shou","guishou" }));
	set("title",HIB"暗器门弃徒"NOR);
	set("long", "暗器门的头号暗器高手，一手鬼手射飞扬跋扈。\n");
	set("gender", "男性");
	set("age", 40);
    set_skill("throwing", 200);

	set_skill("guishoushe", 200);
	set_skill("dodge", 80);
	set_skill("parry", 80);
	map_skill("throwing","guishoushe");
	prepare_wskill("throwing","guishoushe");
	set("jiali",300);
        set("max_neili",30000);
        set("neili",30000);
	set("max_qi",10000);
	set_temp("apply/attack", 80);
	set_temp("apply/defense", 80);
	set_temp("apply/damage", 20);

	set("combat_exp", 8000000);
	set("shen_type", -1);
set("vendor_goods",({
__DIR__"obj/guishousherumen",
}));
	setup();

	set("chat_chance", 3);
	set("chat_msg", ({
		"暗器是天下最厉害的兵器，嘿嘿。\n",
		"武功再高强，碰到暗器，嘿嘿，也不成！\n",
		"嘿嘿，鬼手暗器秘籍上册，１０两金子一本，要不要？\n",
		"嘘，嘿嘿...\n",
	}) );
		carry_object("/clone/weapon/wuyingzhen.c")->wield();
		for(int i=0;i<50;i++)
		{
			carry_object("/clone/weapon/wuyingzhen.c");
		}
}

void init()
{
    add_action("do_list","list");
    add_action("do_buy","buy");
}
int do_list()
{
	tell_object(this_player(),"据说鬼手欠了一屁股债，为了赚钱，就把鬼手门的武功秘籍拿出来卖.\n你也许可以在他那里买到暗器秘籍呢。\n");
	return 1;
}

int recognize_apprentice(object ob)
{
	if (!(int)ob->query_temp("mark/鬼手"))
	{
		return 0; 
	}
	ob->add_temp("mark/鬼手", -1);
	if (!(int)ob->query_temp("mark/鬼手"))
	{
		remove_call_out("over");
		call_out("over",1,ob);
	}	
	return 1;
}
int over(object ob)
{	
		tell_object(ob,HIY"鬼手贪婪的对你说道：你刚才给我的钱，我已经花完了，你是不是应该...\n"+HIW"说完，鬼手嘿嘿嘿奸笑了几声\n"NOR);
		return 1;
}

int accept_object(object who, object ob)
{
	if (!(int)who->query_temp("mark/鬼手"))
		who->set_temp("mark/鬼手", 0);
	if (ob->query("money_id") && ob->value() >= 100000&&who->query_skill("guishoushe",1)>=100) {
		message_vision("鬼手掂了掂手中的金子神秘一笑：好罢，我就教你个一招半式罢！\n", who);
		who->add_temp("mark/鬼手", ob->value() / 20000);
		return 1;
	}
	return 0;
}
