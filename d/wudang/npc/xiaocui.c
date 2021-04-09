// d/wudang/npc/xiaocui.c
// By Marz 04/01/96

inherit NPC;

void greeting(object);
void init();
int accept_object(object,object);
void serve_tea(object);
void delete_served();

void create()
{
	set_name("小翠", ({"cui", "xiao cui"}) );
	set("nickname", "伺茶道童");
	set("gender", "女性" );
	set("age", 12+random(6));
	set("long",
	  "这是个年年龄不大的小姑娘，但宽松的道袍也遮不住她过早发育的身体。\n"
	  "一脸聪明乖巧，满口伶牙俐齿。见有人稍微示意，便过去加茶倒水。\n");
	set("attitude", "friendly");
    set("shen_type", 1);

        set("str", 20);
        set("int", 28);
        set("con", 24);
        set("dex", 20);

        set("max_qi", 150);
        set("max_jing", 100);
        set("neili", 150);
        set("max_neili", 150);

		set("combat_exp", 1000+random(800));
        set("score", 1000);

        set_skill("force", 30);
        set_skill("dodge", 20);
        set_skill("unarmed", 15+random(10));
        set_skill("parry", 20);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 15);
        set_temp("apply/damage", 3);

        create_family("武当派", 5, "弟子");

        set("inquiry", ([
            "女儿香" : "这「女儿香」珍贵得很，连宋大侠的儿子也不能随便喝着．\n"
            	+ "不过如果你要是能送我一件紫罗裙，我倒是可以为你沏一壶。\n",
        ]));

        setup();
        
		carry_object("/d/wudang/obj/greenrobe")->wear();
		carry_object("/d/city/obj/necklace");
}

void init()
{	
	object ob;

	::init();

	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;

	say("小翠笑吟吟地说道：这位" + RANK_D->query_respect(ob)
	     + "请先入座，" + "我这就给您上茶。\n");
}

void destroying(object ob)
{
	destruct(ob);
}
int accept_object(object who, object ob)
{
	object obn;
	
	if( !who || environment(who) != environment() ) return 0;
	if ( !objectp(ob) ) return 0; 
	if ( !present(ob, who) ) return notify_fail("你没有这件东西。");

	if (  (string)ob->query("name") == "茶叶"
		|| (string)ob->query("name") == "金项链"  ) 
	{
		call_out("destroying",1,ob);
		if ( (string)ob->query("name") == "金项链" ) 
		{
			command("kiss " + (string)who->query("id")); 
			command("wear lace");
//			carry_object("/d/city/obj/necklace")->wear();
		}
		
		if ( who->query_temp("marks/sit") )
		{
			if ((int)who->query_temp("tea_cup") > 0)	
	   		{
				command("smile " + who->query("id"));
            } else 
			{
	    		say("小翠作了个揖道：" + RANK_D->query_respect(who)
	       		+ "请稍候，小女子这就给您换香茶。\n");
			}

			who->set_temp("tea_cup", 5);
			remove_call_out("serve_tea");
			call_out("serve_tea", 1, who);

		} else 
		{
			who->set_temp("tea_cup", 5);
	    	say("小翠道了个万福：" + RANK_D->query_respect(who)
	       	+ "请先入上座，小女子这就给您去泡香茶。\n");
		}

		return 1;
	}

	if ((string)ob->query("id") == "ziluo qun") 
	{
		if ( who->query_temp("marks/sit") )
		{
			command("dance " + who->query("id"));
		} else 
		{
			message_vision("小翠引$N到窗边风景最好的桌边坐下．\n", who);
		}
		
		who->set_temp("tea_cup", 10);
		who->set_temp("marks/sit", 1);
                 obn = new("/d/wudang/obj/nuerxiang");
		obn->move(who);
		call_out("destroying",1,ob);
		return 1;
	}


	command("? " + who->query("id"));
//	command("smile cui");
	return 1;
}


void serve_tea(object who)
{
	object obt, obc, obn;
	object room;

	if( !who || environment(who) != environment() ) return;

	if( !who->query_temp("marks/sit") ) return;
	
	if( !objectp(room = environment()) ) return;

	 if(who->is_busy()) return notify_fail("你正忙着呢，等一下再要吧。\n");
         if (present("mi tao", environment(who))||present("wan", environment(who)))
                  return notify_fail("小翠对$N说道：这还没吃完呢。\n");
	if ( (int)who->query_temp("tea_cup") <= 0 )
	{
	 	obn = new("d/wudang/obj/dawancha");
		obn->move(room);
		message_vision("小翠搬出个大茶壶来，将桌上的大碗茶倒满．\n",
			who);
	} else 
	{
		who->add_temp("tea_cup", -1);
	 	obn = new("d/wudang/obj/xiangcha");
		obn->move(room);
		message_vision("小翠拿出个绍兴小茶壶，沏了杯香茶，放在桌上．\n",
			who);
	}

 	obn = new("d/wudang/obj/mitao2");
	obn->move(room);
	message_vision("小翠拿出一碟新鲜的水蜜桃，放在桌上．\n", who);
	
	return;
}
