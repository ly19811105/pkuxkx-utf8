// meng-zhu.c 武林盟主

#ifndef NPCDATA
#define NPCDATA "/data/npc/"
#endif
#define MENGZHU NPCDATA + "meng-zhu"

inherit NPC;
inherit F_MASTER;
// inherit F_CLEAN_UP;
inherit F_UNIQUE;
inherit F_SAVE;

string query_save_file()
{
	return MENGZHU;
}

void create()
{
	seteuid(getuid());

	if (!restore()) {
	set_name("魏无双", ({ "wulin mengzhu", "mengzhu", "zhu" }) );
	set("title", "武林盟主" );
	set("gender", "男性" );
        set("no_get",1);
	set("age", 40);
	set("long","他就是雄踞武林，号召天下，威风赫赫的当今武林盟主。\n");
	set("attitude", "heroism");
	set("generation",0);
	set("winner","none");

	set("str", 25);
	set("con", 25);
	set("int", 25);
	set("dex", 25);

	set("max_qi", 500);
	set("eff_qi", 500);
	set("qi", 500);
	set("max_jing", 300);
	set("jing", 300);
	set("neili", 500);
	set("max_neili", 500);
	set("jiali", 40);
	set("shen_type", 0);

	set("no_clean_up",1);
	set("combat_exp", 500000);

	set_skill("force",  100); 
	set_skill("unarmed",100);
	set_skill("sword",  100);
	set_skill("dodge",  100);
	set_skill("parry",  100);

	set("weapon", "/d/shaolin/obj/changjian");
	set("armor", "/d/city/obj/cloth");

	setup();

	carry_object("/d/shaolin/obj/changjian")->wield();
	carry_object("/d/city/obj/cloth")->wear();        
	}
	else {
                set("id", ({ "wulin mengzhu", "mengzhu", "zhu" }));
                set_name(query("name"), ({ "wulin mengzhu", "mengzhu", "zhu"  }));
		setup();
		if( this_object()->query("weapon") ) carry_object(this_object()->query("weapon"))->wield();
                else carry_object("/d/shaolin/obj/changjian")->wield();
                if( this_object()->query("armor") ) carry_object(this_object()->query("armor"))->wear();
                else carry_object("/d/city/obj/cloth")->wear();
                if ( query("jingli")<0 )
                	set("jingli",0);
                if ( query("neili")<0 )
                	set("neili",0);
	}
}

void init()
{
	object me = this_object();

	add_action("do_recopy",  "recopy");
//	add_action("do_recover", "recover");
	add_action("do_kill", "kill");

}

int do_kill()
{
	object ob;
	int i;

	command("say 你想谋害本盟主，当真是吃了熊心豹子胆了！！");
	command("say 座下白衣武士何在！");
	
	message_vision("四周的白衣武士群起对$N发动攻击！\n", this_player());

	for(i=0; i<4; i++) {
		if( objectp( ob = present("wei shi " + (i+1), environment(this_object())) ) )
				 ob->kill_ob(this_player());    
		else    this_object()->kill_ob(this_player());          
	}

	return 1;
}

int accept_fight(object ob)
{
	object me  = this_object();
        if (file_name(environment())!="/d/taishan/fengchan")
		return notify_fail("武林盟主现在身有要事，等他回了泰山再说吧。\n");

		
	if ( me->query("winner") == ob->query("id") ) 
		return notify_fail("你跟你自己打什么架？！\n");

	if (SECURITY_D->get_status(this_player()) != "(player)" )
		return notify_fail("巫师和超级玩家不能抢使者之位！\n");

	if ( me->is_fighting() ) 
		return notify_fail("已经有人正在挑战武林盟主！\n");
	if (this_player()->query("tqt/free_trial"))
		return notify_fail("你在试用铜雀台武功期间，不能做此挑战！\n");
	me->set("eff_qi", me->query("max_qi"));
	me->set("qi",     me->query("max_qi"));
	me->set("jing",   me->query("max_jing"));
	me->set("neili",  me->query("max_neili"));

	remove_call_out("checking");
	call_out("checking", 1, me, ob);
	
	return 1;
}

int checking(object me, object ob)
{

	object obj;
	int my_max_qi, his_max_qi;

	my_max_qi  = me->query("max_qi");
	his_max_qi = ob->query("max_qi");

	if (me->is_fighting()) {
		if ( (me->query("qi")*100 / my_max_qi) <= 80 )
			command("exert recover");

		call_out("checking", 1, me, ob);
		return 1;
	}

	if ( !present(ob, environment()) ) return 1; 

	if (( (int)me->query("qi")*100 / my_max_qi) <= 50 ) {
		command("say 果然厉害，恭喜你成为当今武林盟主！\n");
		CHANNEL_D->do_channel(this_object(), "jh", "哈哈哈，到底是长江後浪推前浪，一代新人换旧人！");
		CHANNEL_D->do_channel(this_object(), "jh", "恭喜" + ob->query("name") + "被推举为当今武林盟主！");
		remove_call_out("do_copy");
		call_out("do_copy", 1, me, ob);
		return 1;
	}

	if (( (int)ob->query("qi")*100 / his_max_qi) < 50 ) {
		command("say 看来" + RANK_D->query_respect(ob) + 
			"还得多加练习，方能在当今武林中出人头地 !\n");
		return 1;
	}

	return 1;  
}

int do_copy(object me, object ob)
{
	object ob1, ob2;
	string mengzhu, shangshan, fae, str;

	seteuid(getuid());

	me->set("winner", ob->query("id"));
	me->add("generation", 1);       

	me->set("name",  ob->query("name") );
	me->set("title", "第" + chinese_number(me->query("generation")) + "代武林盟主");
       str = me->query("title") + "----" + me->query("name")  + "(" + ob->query("id") + ")"+ ctime(time())+ "  。\n";
       write_file("/log/static/MENGZHU", str);
	me->set("short", me->query("title") + " " + me->query("name") + "(" + capitalize(ob->query("id")) + ")");
	me->delete("title");

	me->set("mud_age", ob->query("mud_age"));
	me->set("shen", ob->query("shen"));
	me->set("luohan_winner", ob->query("luohan_winner"));
	me->set("dai", ob->query("dai"));
	me->set("is_beggar", ob->query("is_beggar"));

        me->set("betrayer",ob->query("betrayer"));
        me->set("family",ob->query("family"));

	ob->delete_temp("apply/short");
//        ob->set_temp("apply/short", ({me->short()}));
	
	me->set("title", "第" + chinese_number(me->query("generation")) + "代武林盟主");
	me->set("short", me->query("title") + " " + me->query("name") + "(Wuling mengzhu)");
	me->delete("title");

	if(!( ob1 = find_living("shangshan")) )
	ob1 = load_object("/clone/npc/shang-shan");
	shangshan = ob1->query("winner");

	if(!( ob2 = find_living("fae")) )
	ob2 = load_object("/clone/npc/fa-e");
	fae = ob1->query("winner");

	if( ob->query("id") == shangshan ) {
                 rm( ob1->query_save_file() + ".o" );
		destruct(ob1);
	}
	else  if( ob->query("id") == fae ) {
                  rm( ob2->query_save_file() + ".o" );
		destruct(ob2);
	}

	remove_call_out("do_clone");
	call_out("do_clone", 0, me, ob);

	return 1;
}

int do_recopy(object me, object ob)
{
	me = this_object();
	ob = this_player();

	if ( me->query("winner") != ob->query("id") ) 
		return notify_fail("你不是现任武林盟主！\n");;

	if ( me->query("mud_age") > ob->query("mud_age"))
				return notify_fail("你想用 bug 谋利，呵呵！\n");

        if (ob->query("pked/be_pked") == "none" )
        {}
        else  ob->set("pked/be_pked","mengzhu");
	me->set("name",  ob->query("name") );
	me->set("title", "第" + chinese_number(me->query("generation")) + "代武林盟主");
	me->set("short", me->query("title") + " " + me->query("name") + "(" + capitalize(ob->query("id")) + ")");
	me->delete("title");
	
	me->set("mud_age", ob->query("mud_age"));
	me->set("shen", ob->query("shen"));
	me->set("luohan_winner", ob->query("luohan_winner"));
	me->set("dai", ob->query("dai"));
	me->set("is_beggar", ob->query("is_beggar"));

	me->set("betrayer",ob->query("betrayer"));
        me->set("family",ob->query("family"));
	
	ob->delete_temp("apply/short");
	ob->set_temp("apply/short", ({me->short()}));

	me->set("title", "第" + chinese_number(me->query("generation")) + "代武林盟主");
	me->set("short", me->query("title") + " " + me->query("name") + "(Wuling mengzhu)");
	me->delete("title");

	remove_call_out("do_clone");
	call_out("do_clone", 0, me, ob);

	return 1;
}

int do_clone(object me, object ob)
{
        object *inv,newob;
	mapping hp_status, skill_status, map_status, prepare_status;
	string *sname, *mname, *pname;
	int i, temp;

	seteuid( geteuid(me) );

  /* unwield and remove weapon & armor */
  
      inv = all_inventory(me);
      for(i=0; i<sizeof(inv); i++) {
          destruct(inv[i]);
      }
      set("weapon", 0);
      set("armor", 0);

  /* wield and wear weapon & armor */
  
              carry_object("/clone/weapon/changjian")->wield();
              me->set("weapon", "/clone/weapon/changjian");
              carry_object("/clone/armor/tiejia")->wear();
              me->set("armor", "/clone/armor/tiejia");



/* delete and copy skills */

	if ( mapp(skill_status = me->query_skills()) ) {
		skill_status = me->query_skills();
		sname  = keys(skill_status);

		temp = sizeof(skill_status);
		for(i=0; i<temp; i++) {
			me->delete_skill(sname[i]);
		}
	}

	if ( mapp(skill_status = ob->query_skills()) ) {
		skill_status = ob->query_skills();
		sname  = keys(skill_status);

		for(i=0; i<sizeof(skill_status); i++) {
			me->set_skill(sname[i], skill_status[sname[i]]);
		}
	}
	
/* delete and copy skill maps */

	if ( mapp(map_status = me->query_skill_map()) ) {
		mname  = keys(map_status);

		temp = sizeof(map_status);
		for(i=0; i<temp; i++) {
			me->map_skill(mname[i]);
		}
	}

	if ( mapp(map_status = ob->query_skill_map()) ) {
		mname  = keys(map_status);

		for(i=0; i<sizeof(map_status); i++) {
			me->map_skill(mname[i], map_status[mname[i]]);
		}
	}
	
/* delete and copy skill prepares */

	if ( mapp(prepare_status = me->query_skill_prepare()) ) {
		pname  = keys(prepare_status);

		temp = sizeof(prepare_status);
		for(i=0; i<temp; i++) {
			me->prepare_skill(pname[i]);
		}
	}

	if ( mapp(prepare_status = ob->query_skill_prepare()) ) {
		pname  = keys(prepare_status);

		for(i=0; i<sizeof(prepare_status); i++) {
			me->prepare_skill(pname[i], prepare_status[pname[i]]);
		}
	}



/* copy entire dbase values */

	hp_status = ob->query_entire_dbase();

		me->set("str", hp_status["str"]);
		me->set("int", hp_status["int"]);
		me->set("con", hp_status["con"]);
		me->set("dex", hp_status["dex"]);
		me->set("age", hp_status["age"]);

		me->set("max_qi",    hp_status["max_qi"]);
		me->set("eff_qi",    hp_status["eff_qi"]);
		me->set("qi",        hp_status["qi"]);
		me->set("max_jing",  hp_status["max_jing"]);
		me->set("eff_jing",  hp_status["eff_jing"]);
		me->set("jing",      hp_status["jing"]);
		me->set("max_neili", hp_status["max_neili"]);
		me->set("neili",     hp_status["neili"]);
		me->set("jiali",     hp_status["jiali"]);
		me->set("gender",    hp_status["gender"]);
		me->set("combat_exp",hp_status["combat_exp"]);

	save();

	tell_object(ob, "状态储存完毕。\n");

         newob = new("/clone/npc/meng-zhu");
        newob->move("/d/taishan/fengchan");
	destruct(me);

	return 1;
}

int do_recover()
{
	object me, ob;
	mapping skill_status, map_status, prepare_status;
	string *sname, *mname, *pname;
	int i;

	me = this_object();
	ob = this_player();

	if ( me->query("winner") != ob->query("id") ) 
		return notify_fail("你不是现任武林盟主！\n");;
	
	if ( me->query("mud_age") > ob->query("mud_age"))
				return notify_fail("你想用 bug 谋利，呵呵！\n");

            if ( ob->query("pked/be_pked") == "mengzhu" || ob->query("pked/be_pked") == "none" )
             {
//                      ob->set("pker/be_pked","none");
             }
             else
               return notify_fail("请到最近一次recopy的帮主那里去recover。\n");


/* delete and copy skills */

	if ( mapp(skill_status = ob->query_skills()) ) {
		sname  = keys(skill_status);

		for(i=0; i<sizeof(skill_status); i++) {
			ob->delete_skill(sname[i]);
		}
	}

	if ( mapp(skill_status = me->query_skills()) ) {
		sname  = keys(skill_status);

		for(i=0; i<sizeof(skill_status); i++) {
			ob->set_skill(sname[i], skill_status[sname[i]]);
		}
	}
	
/* delete and copy skill maps */

	if ( mapp(map_status = ob->query_skill_map()) ) {
		mname  = keys(map_status);

		for(i=0; i<sizeof(map_status); i++) {
			ob->map_skill(mname[i]);
		}
	}

	if ( mapp(map_status = me->query_skill_map()) ) {
		mname  = keys(map_status);

		for(i=0; i<sizeof(map_status); i++) {
			ob->map_skill(mname[i], map_status[mname[i]]);
		}
	}
	
/* delete and copy skill prepares */

	if ( mapp(prepare_status = ob->query_skill_prepare()) ) {
		pname  = keys(prepare_status);

		for(i=0; i<sizeof(prepare_status); i++) {
			ob->prepare_skill(pname[i]);
		}
	}

	if ( mapp(prepare_status = me->query_skill_prepare()) ) {
		pname  = keys(prepare_status);

		for(i=0; i<sizeof(prepare_status); i++) {
			ob->prepare_skill(pname[i], prepare_status[pname[i]]);
		}
	}

/* copy combat exp values */

	ob->set("combat_exp", me->query("combat_exp"));
	ob->set("is_beggar", me->query("is_beggar"));
	ob->set("mud_age", me->query("mud_age"));
	ob->set("shen", me->query("shen"));
	ob->set("luohan_winner", me->query("luohan_winner"));
	ob->set("dai", me->query("dai"));
	
	if ((string)me->query("family/family_name")!=(string)ob->query("family/family_name"))
	{
	    ob->add("betrayer",1);
	    me->set("betrayer",ob->query("betrayer"));
	    me->set("family",ob->query("family"));
	    save();
	}

	write("状态复元完毕。\n");

	return 1;
}

