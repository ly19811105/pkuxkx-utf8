// xiejian.c 邪剑李四

#include <ansi.h>

inherit NPC;

int waiting(object me);
int checking(object me);
int do_chase(object me);
int do_kill(object me, object dest);
string ask_me();

void create()
{
	set_name("浪回头", ({ "lang huitou", "lang" }) );
	set("title", RED "金牌杀手"NOR);
        set("nick","回首黄昏空见雨");
	set("gender", "男性" );
	set("shen_type", -1);
        set("shen",-10000);
	set("age", 40);
	set("str", 30);
	set("con", 30);
	set("int", 30);
	set("dex", 30);

	set("no_clean_up",1);

	set("long",
		"杀手帮唯一的金牌杀手，是楚帮主最为信任的帮众之一\n" );

        set("combat_exp", 500000);
	set("attitude", "peaceful");
        set("chat_chance", 1);
	set("chat_msg", ({
		"浪回头凄然言道:梨花带血天下闻，伊人何处谁人知.....\n",
	}) );

	set("inquiry", ([
	        "杀人"   : (: ask_me :),
	]) );

	set("max_qi", 3000);
	set("max_jing", 3000);
	set("neili", 3000);
	set("max_neili", 3000);
	set("jiali", 200);
	set("env/wimpy", 60);

	set_skill("force", 260); 
	set_skill("unarmed", 280);
	set_skill("sword", 270);
	set_skill("dodge", 270);
	set_skill("parry", 270);
	
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
         if(ob->query_temp("killer")) 
         {
             me->kill_ob(ob);
             message_vision(RED"得罪了帮主,"+RANK_D->query_rude(ob)+"以为你还跑得掉吗?看招!\n" NOR,me);
         }

        add_action("do_name","杀");
	
}

string ask_me()
{
	return "我就是浪回头，又要我杀人吗？\n";
}

int do_name(string target)
{
	object me,who,dest, *all;
	int i;
        who=this_player();
	me = this_object();
	all = users();

        if(who->query("pker"))
        {
           return notify_fail("浪回头嘿嘿一笑，你自己身为杀手，却让我帮你杀人?....\n");
        }
	if(me->query("waiting_target"))
		return notify_fail("浪回头言道：本座现在没空!!\n");
	
	if( !this_player()->query_temp("fee_paid") ) 
		return notify_fail("浪回头冷笑一声:你想让我饿着肚子给你杀人吗!?\n");

	if( !target || target==" ") 
		return notify_fail("有话快说，我可没工夫在这陪你!\n");

	for(i=0; i<sizeof(all); i++) 
	{
		if( target == all[i]->name() || target == all[i]->id() )
			dest = all[i];
	}
	
	if( !dest )
		return notify_fail("浪回头说道:他现在不在游戏中\n");
		
	if (dest->is_ghost())
		return notify_fail("他不是已经死了吗\n");

	me->set("waiting_target", dest->query("id"));
		
	me->set_temp("apply/attack",  200);
	me->set_temp("apply/defense", 200);
	me->set_temp("apply/damage",  200);

	
	me->delete("chat_chance");
	me->delete("chat_msg");

	message("vision",
		HIY "浪回头面无表情地说道：稍侯片刻!\n"NOR,
		environment(), me );

	me->set("pursuer", 1);
	me->set("vendetta/authority", 1);
	me->set("bellicosity", 10000);
	message_vision("$N走了出去。\n" NOR, me);
	CHANNEL_D->do_channel(me,"sys",sprintf("%s雇佣浪回头杀%s",this_player()->query("name"),dest->query("name")));
                log_file("static/langhuitou",sprintf("%s于%s雇佣浪回头杀%s\n",this_player()->query("name"),ctime(time()),dest->query("name")));
	call_out("do_chase", 1, me);
	
	return 1;
}

int accept_object(object who, object ob)
{
        if(who->query("pker"))
        {
               tell_object(who,"浪回头嘿嘿一笑，你自己身为杀手，却让我帮你杀人?....\n");
               return 0;
        }	
        if (ob->query("money_id") && ob->value() >= 5000000
		&& !this_object()->query("waiting_target")) 
	{
		tell_object(who, "浪回头说道：好，他到底是谁？\n");
		tell_object(who, "请键入：杀 目标中文名字\n");
		who->set_temp("fee_paid",1);
		return 1;
	}
	else if (ob->query("money_id") && ob->value() < 100) 
	{
		tell_object(who, "哼，难道我浪回头就值这点!?\n");
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
		message_vision(HIR "$N对$n说道：人生不如意者十之八九，"
			+RANK_D->query_respect(dest)+"，你不要怪我！\n" NOR, me, dest);
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

	if (me->is_fighting()) 
	{
		call_out("checking", 1, me);
        return 1;
	}

	if( present("corpse", environment(me)) )	
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

	me->move("/d/village/shop");
	message("vision", "浪回头慢慢地走了过来，冷冷地说道，活干完了，你可以放心了\n",
		environment(), me );
        me->set_leader(0);
	
	return 1;
}

	
