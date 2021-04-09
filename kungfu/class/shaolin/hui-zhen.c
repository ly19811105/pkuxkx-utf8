// Npc: /kungfu/class/shaolin/hui-zhen.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;


void create()
{
	set_name("慧真尊者", ({
		"huizhen zunzhe",
		"huizhen",
		"zunzhe",
	}));
	set("long",
		"他是一位两鬓斑白的老僧，身穿一袭青布镶边袈裟。他身材略高，\n"
		"太阳穴微凸，双目炯炯有神。\n"
	);


	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 50);
	set("shen_type", 1);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	set("max_qi", 600);
	set("max_jing", 500);
	set("neili", 1000);
	set("max_neili", 1000);
	set("jiali", 100);
	set("combat_exp", 200000);
	set("score", 200);

	set_skill("force", 100);
	set_skill("hunyuan-yiqi", 80);
	set_skill("dodge", 80);
	set_skill("shaolin-shenfa", 80);
	set_skill("finger", 90);
	set_skill("yizhi-chan", 90);
	set_skill("strike", 70);
	set_skill("banruo-zhang", 70);
	set_skill("sword", 80);
	set_skill("damo-jian", 80);
	set_skill("parry", 80);
	set_skill("buddhism", 100);
	set_skill("literate", 100);

	map_skill("force", "hunyuan-yiqi");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("finger", "yizhi-chan");
	map_skill("strike", "banruo-zhang");
	map_skill("sword", "damo-jian");
	map_skill("parry", "damo-jian");

	prepare_skill("finger", "yizhi-chan");
	prepare_skill("strike", "banruo-zhang");

	create_family("少林派", 38, "弟子");

	setup();

        carry_object("/d/shaolin/obj/changjian")->wield();
        carry_object("/d/shaolin/obj/hui-cloth")->wear();
}

void init()
{
	mapping mine;
	object me, room;

	me = this_player();

	if (!mapp(mine = me->query("family"))) 
		return;

	if(!( room = find_object("/d/shaolin/cjlou")) )
	room = load_object("/d/shaolin/cjlou");

        if( ((mapp(mine = me->query("family")) && mine["family_name"] != "少林派")
        || ((!present("daoyi chanshi", room)) && (!present("letter", me))))
        && environment(this_object())->query("short")=="藏经阁二楼")
	{
		  command("say 大胆狂徒，竟敢杀人闯入藏经阁，看招!\n");
		  call_out("kill_ob", 0, this_player()); 

	 	  COMBAT_D->do_attack(this_object(), this_player(), query_temp("weapon"));		  
		  return;
	}

	return;
}


int move(object ob)
{
  if ( ob->is_character() )
  {
    this_object()->set_temp("porter",ob->query("id"));
  }
  ::move(ob);
  return 1;
}
