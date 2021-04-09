//NPC /d/baituo/npc/xiaoqing.c
//modified by vast 2003.3
//modified by iszt, 2006-08-15
//fixed some descriptions, changed the id and added void destroy()
#include <ansi.h>
inherit NPC;
void greeting(object);
void init();
string inquiry_gao();
void create()
{
	set_name("小青", ( { "xiao qing", "qing"}) );
	set("title", "药剂师");
	set("gender", "女性" );
	set("age", 16);
	set("long",
		"这是个聪明乖巧的小姑娘，打扮的很朴素，一袭青衣，却也显得落落有致。\n"
		"小青对人非常热情。你要是跟她打过交道就会理解这一点！\n"
		);
	set("attitude", "friendly");
	set("shen_type", -1);
	set("str", 20);
	set("int", 29);
	set("con", 23);
	set("dex", 22);
	set("max_qi", 130);
	set("max_jing", 120);
	set("neili", 120);
	set("max_neili", 120);
	set("combat_exp", 60000);
	set("score", 1000);
	set_skill("force", 26);
	set_skill("dodge", 23);
	set_skill("unarmed", 24);
	set_skill("parry", 22);
	set_temp("apply/attack", 10);
	set_temp("apply/defense", 15);
	set_temp("apply/damage", 17);
	set_temp("apply/armor", 10);
	set_temp("dan",0);
	set_temp("times",5);
	create_family("白驼山", 5, "弟子");
	set("inquiry", ([
		"海口大碗" : "这『海口大碗』你可以拿到顶东头小院儿去，灌水喝。\n",
		"药罐" : "药罐在那儿，你自己看吧！\n",
		"蛇胆膏" : (: inquiry_gao :),
	]));
	setup();
	carry_object("/d/baituo/obj/qingpao")->wear();
}
void init()
{
	object ob;
	::init();
	if( interactive(ob = this_player()) && !is_fighting() )
	{
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}
void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	if(random(2)==1)
			{say("小青笑吟吟地说道：这位" + RANK_D->query_respect(ob)
		+ "请进，见到你真高兴。\n");
			 return;
			}
		else
		{say("小青笑了笑说道：这位" + RANK_D->query_respect(ob)
		+ "快请进吧。 \n");
			 return;
			}
}
string inquiry_gao()
{
	object ob=this_player();
	if(query_temp("dan")==7) return "你没见我已经作好了嘛！\n";
	if(query_temp("times")==0) return "师傅现在已经不叫我做『蛇胆膏』了！\n";
	say("这位" + RANK_D->query_respect(ob)+
		"不瞒您说。师傅让我作『蛇胆膏』，\n可我",ob);
	switch (query_temp("dan"))
	{
	 case 0: write(HIY "差一只青蛇胆，一只金蛇胆,一只菩斯曲蛇胆。\n" NOR);
		 break;
	 case 1: write(HIY "还差一只青蛇胆，一只菩斯曲蛇胆。\n" NOR);
		 break;
	 case 2: write(HIY "还差一只金蛇胆，一只菩斯曲蛇胆。\n" NOR);
		 break;
	 case 3: write(HIY "还差一只菩斯曲蛇胆。\n" NOR);
		 break;
	 case 4: write(HIY "还差一只青蛇胆，一只金蛇胆。\n" NOR);
		 break;
	 case 5: write(HIY "还差一只青蛇胆。\n" NOR);
		 break;
	 case 6: write(HIY "还差一只金蛇胆。\n" NOR);
		 break;	
}
	return "不知哪位好心人能帮帮我呢？\n";
}
int accept_object(object who, object ob)
{
	object obn;
	if( !who || environment(who) != environment() ) return 0;
	if ( !objectp(ob) ) return 0;
	if ( !present(ob, who) ) return notify_fail("你没有这件东西。\n");
	if ( (string)ob->query("name") != "青蛇胆"
		&& (string)ob->query("name") != "金蛇胆"
		&& (string)ob->query("name") != "菩斯曲蛇胆"	)
			return notify_fail("小青不需要这件东西。\n");
	if ( query_temp("times")==0 )
			return notify_fail("小青现在已经不做『蛇胆膏』了。\n");
	if ( (string)ob->query("name") == "金蛇胆" && ob->query("id") == "jin dan")
	{
		if (query_temp("dan")==1 || query_temp("dan")==3 || query_temp("dan")==5)
		{
			message_vision("小青一看是金蛇胆，满脸遗憾的对$N说：我不缺金蛇胆。\n",who);
			return 0;
		}
		call_out("destroy",1,ob); //added by iszt

		add_temp("dan",1);
		if (query_temp("dan")==1)
		{
			message_vision("小青看到金蛇胆，高兴得跳了起来。\n"
					"搂着$N的脖子说：还差青蛇胆和菩斯曲蛇胆就大功告成了！\n",who);
			return 1;
		}
		if (query_temp("dan")==3)
		{
			message_vision("小青看到金蛇胆，高兴得跳了起来。\n"
					"搂着$N的脖子说：还差菩斯曲蛇胆就大功告成了！\n",who);
			return 1;
		}
		if (query_temp("dan")==5)
		{
			message_vision("小青看到金蛇胆，高兴得跳了起来。\n"
					"搂着$N的脖子说：还差青蛇胆就大功告成了！\n",who);
			return 1;
		}
	}
	 if ( (string)ob->query("name") == "青蛇胆" && ob->query("id") == "qing dan")
	{
		if (query_temp("dan")==2 || query_temp("dan")==3 || query_temp("dan")==6)
		{
			message_vision("小青一看是青蛇胆，满脸遗憾地对$N说：我不缺青蛇胆。\n",who);
			return 0;
		}
		
		call_out("destroy",1,ob); //added by iszt
		add_temp("dan",2);
		if (query_temp("dan")==2)
		{
			message_vision("小青看到青蛇胆，高兴得跳了起来。\n"
					"搂着$N的脖子说：还差金蛇胆和菩斯曲蛇胆就大功告成了！\n",who);
			return 1;
		}
		if (query_temp("dan")==3)
		{
			message_vision("小青看到青蛇胆，高兴得跳了起来。\n"
					"搂着$N的脖子说：还差菩斯曲蛇胆就大功告成了！\n",who);
			return 1;
		}
		if (query_temp("dan")==6)
		{
			message_vision("小青看到青蛇胆，高兴得跳了起来。\n"
					"搂着$N的脖子说：还差金蛇胆就大功告成了！\n",who);
			return 1;
		}
	}
	 if ( (string)ob->query("name") == "菩斯曲蛇胆" && ob->query("id") == "pusiqushe dan" )
	{
		if (query_temp("dan")==4 || query_temp("dan")==5 || query_temp("dan")==6)
		{
			message_vision("小青一看是菩斯曲蛇胆，满脸遗憾地对$N说：我不缺菩斯曲蛇胆。\n",who);
			return 0;
		}
		call_out("destroy",1,ob); //added by iszt
		add_temp("dan",4);
		if (query_temp("dan")==4)
		{
			message_vision("小青看到菩斯曲蛇胆，高兴得跳了起来。\n"
				"搂着$N的脖子说：还差青蛇胆和金蛇胆就大功告成了！\n",who);
			return 1;
		}
		if (query_temp("dan")==5)
		{
			message_vision("小青看到菩斯曲蛇胆，高兴得跳了起来。\n"
				"搂着$N的脖子说：还差青蛇胆就大功告成了！\n",who);
			return 1;
		}
		if (query_temp("dan")==6)
		{
			message_vision("小青看到菩斯曲蛇胆，高兴得跳了起来。\n"
				"搂着$N的脖子说：还差金蛇胆就大功告成了！\n",who);
			return 1;
		}
	}
	command("kiss "+(string)who->query("id"));
	write( HIY "只见小青手脚麻利地把三只蛇胆投入药罐中，又加入一些\n"
		"不知是什么的药粉，然后把稀里哗啦一摇，嘿！『蛇胆膏』做\n"
		"成了。\n" NOR );
	message_vision("小青很神秘地凑近$N悄悄说了些什么。\n", who);
	tell_object(who,"我偷偷拿了一点『蛇胆膏』送给你，师傅不会发现的。\n");
	message_vision("小青深情地望了$N一眼，脸红了。\n",who);
	obn = new("/d/baituo/obj/shedangao");
	obn->move(who);
	set_temp("dan",0);
	add_temp("times",-1);
	return 1;
}

void destroy(object ob)
{
	destruct(ob);
	return;
}
