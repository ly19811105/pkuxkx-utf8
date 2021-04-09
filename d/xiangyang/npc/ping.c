#include <ansi.h>
inherit NPC;
int waiting(object me);
int checking(object me);
int do_chase(object me);
int do_kill(object me, object dest);
string ask_me();
void create()
{
	set_name("一点红", ({ "yidian hong", "hong" }) );
	set("title", "药铺掌柜");
	set("gender", "男性" );
	set("shen_type", -1);
	set("age", 40);
	set("str", 30);
	set("con", 30);
	set("int", 30);
	set("dex", 30);

	set("no_clean_up",1);

	set("long",
		"这是一位高大的汉子，每天愁眉紧锁，没人知道他在干什么。\n" );

	set("combat_exp", 1000000);
	set("attitude", "peaceful");
	set("inquiry", ([
	        "杀人"   : (: ask_me :),
	]) );

	set("max_qi", 3700);
	set("max_jing", 3400);
	set("neili", 3700);
	set("max_neili", 3700);
	set("jiali", 250);
	set("shen_type", -1);
	set("env/wimpy", 60);

	set_skill("force", 180);
	set_skill("huashan-neigong", 140);
	set_skill("dodge", 190);
	set_skill("parry", 250);
	set_skill("sword", 160);
	set_skill("huashan-jianfa", 180);

	map_skill("force", "huashan-neigong");
	map_skill("parry", "huashan-jianfa");
	map_skill("sword", "huashan-jianfa");
	setup();
	carry_object("d/city/obj/gangjian")->wield();
	carry_object("d/city/obj/cloth")->wear();
}

void init()
{
	object me, ob;
	me = this_object();
	ob = this_player();
        ::init();
	if( !me->query("waiting_target") && ob->query_temp("fee_paid") ) 
		ob->delete_temp("fee_paid");
        add_action("do_name","杀");
	
}

string ask_me()
{
	return "嘿嘿，金子带够了吗？\n";
}

int do_name(string target)
{
	object me, dest, *all;
	int i;
 
	me = this_object();
	all = users();

	if(me->query("waiting_target"))
		return notify_fail("一点红嘿嘿一笑：我现在正忙着哪，您呆会儿在来吧！\n");
	
	if( !this_player()->query_temp("fee_paid") ) 
		return notify_fail("一点红说道：不管叫我做什麽，您可得先付钱哪！\n");

	if( !target || target==" ") 
		return notify_fail("一点红恶狠狠地说道：快告诉我那家伙的名字，我可没功夫听你闲聊！\n");

	for(i=0; i<sizeof(all); i++) 
	{
		if( target == all[i]->name() || target == all[i]->id() )
			dest = all[i];
	}
	
	if( !dest )
		return notify_fail("一点红一声冷笑：他现在不在游戏中，过会再来吧。\n");
		
	if (dest->is_ghost())
		return notify_fail("一点红很不高兴：他已经是个死鬼了，你还来找我干什么！\n");

	me->set("waiting_target", dest->query("id"));
	me->set("target_name", target);
		
	me->set_temp("apply/attack",  50);
	me->set_temp("apply/defense", 50);
	me->set_temp("apply/damage",  20);

	me->set("title", RED "冷面杀手" NOR);
	me->set("long",
		"一点红，杀手帮创始人.\n" );

	me->delete("chat_chance");
	me->delete("chat_msg");

	message("vision",
		HIY "一点红嘿嘿嘿地干笑了几声，说道：您就在这儿静侯好音吧!\n"NOR,
		environment(), me );

	me->set("pursuer", 1);
	me->set("vendetta/authority", 1);
	me->set("bellicosity", 10000);
	me->set("combat_exp", 50000);

	message_vision("$N走了出去。\n" NOR, me);

	call_out("do_chase", 1, me);
	
	return 1;
}

int accept_object(object who, object ob)
{
	
	if (ob->query("money_id") && ob->value() >= 10000000 
		&& !this_object()->query("waiting_target")) 
	{
		tell_object(who, "一点红沉下脸来：好，爽快说吧，你要我帮你杀谁？\n");
		tell_object(who, "请键入：杀 目标中文名字\n");
		who->set_temp("fee_paid",1);
		return 1;
	}
	else if (ob->query("money_id") && ob->value() < 1000000) 
	{
		tell_object(who, "一点红嘿嘿一笑，说道：给我这麽多钱？ 将来我可没法还你啊。\n");
		return 1;
	}

	return 0;
}

int do_chase(object me)
{
	
	object dest;
	dest = find_player(me->query("waiting_target"));
	
	if( !objectp(dest) || !environment(dest) )	
	{
		call_out("waiting", 0, me);
		return 1;
	}
	
	me->move(environment(dest));
	message_vision("$N走了过来。\n" NOR, me);
	me->set_leader(dest);
	command("look " + dest->query("id"));
	
	if ( !environment(me)->query("no_fight"))
	{
		call_out("do_kill", 1, me, dest);
		return 1;
	}
	else
	{
		call_out("waiting", 0, me);
		return 1;
	}

	return 1;
}

int do_kill(object me, object dest)
{

	if( objectp(dest) && present(dest, environment(me))
		 && !environment(me)->query("no_fight"))
	{
		message_vision(HIR "$N对$n说道：阴司鬼王差我来，请你去他那儿做客，"
			+RANK_D->query_rude(dest)+"，你认命吧！\n" NOR, me, dest);
		me->set_leader(dest);
		me->kill_ob(dest);
		dest->fight_ob(me);

		call_out("checking", 0,  me); 	
	}
	else  
		call_out("waiting", 1, me); 	
	
	return 1;
}

int waiting(object me)
{
	object dest;
	dest = find_player(me->query("waiting_target"));
	
	if ( objectp(dest) )
	{
		if (dest->is_ghost())
		{
			me->delete("waiting_target");
			call_out("do_back", 1, me);
			return 1;
		}else if (me->is_fighting() && present(dest, environment(me)))
		{
			call_out("checking", 0, me);
			return 1;
		}else if (living(me) && !environment(dest)->query("no_fight"))
		{
			call_out("do_chase", 0, me);
			return 1;
		}
	}		
	
	remove_call_out("waiting");
	call_out("waiting", 60, me);
    return 1;
}

int checking(object me)
{
	object ob;

	if (me->is_fighting()) 
	{
		call_out("checking", 1, me);
        return 1;
	}

	if( objectp(ob = present("corpse", environment(me)))
		 && ob->query("victim_name") ==	me->query("target_name") )
	{
		me->delete("waiting_target");
		call_out("do_back", 1, me);
        return 1;
	}
	
	call_out("waiting", 0, me);
	return 1;
}

int do_back(object me)
{

	me->move("/u/chenchen/work/yaopu");
	message("vision", "一点红走了进来，拍了拍身上的尘土，把剑上的血迹抹拭干净，\n"
		"他接着一笑说道：老天爷保佑，活儿干得干净利落，您老以後有什麽事还可以找我。\n", 
		environment(), me );

	me->set("title", "药铺掌柜");
	me->set("long",
		"这是一位高大的汉子，每天愁眉紧锁，没人知道他在干什么。\n" );
	
	me->set_leader(0);

	return 1;
}
