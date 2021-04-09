// File         : dashi.c
// Created By   : iszt@pkuxkx, 2006-12-07
// modify by :yhzzyahoo@pkuxkx, 2017-4-28
inherit NPC;
#include <ansi.h>
#define FACTOR_HS 1

void auto_perform();
string ask_job();

string *name = ({
		"远",   "济",   "恒",   "妙",   "禅",   "证",
		"鸣",   "素",   "悟",   "谛",   "竹",   "性",   
		"奥","成","法","木","定","简",
		"云","舟","无","量","易","而",
		"未","思","清","明","山","水",
		"刚","柔","并","安","松","然",
});
string *id = ({
	"yuan", "ji",   "heng", "miao", "chan", "zheng",
		"ming", "su",   "wu",   "di",   "zhu",  "xing",
		"ao","cheng","fa","mu","ding","jian",
		"yun","zhou","wu","liang","yi","er",
		"wei","si","qing","ming","shan","shui",
		"gang","rou","bing","an","song","ran",
});
string *long = ({
	"他是一位身材矮小的老年僧人，容颜瘦削，神色慈和，也瞧不出有多少年纪。\n",
		"他白眉下垂，直覆到眼上，便似长眉罗汉一般。\n",
		"他身披一件护法袈裟，貌相威武。\n",
		"他一脸的苦相，嘴角下垂，仿佛遇到了什么难以处理的事情。\n",
});

void create()
{
	string weapon;
	int index = random(sizeof(name));

	set_name("玄" + name[index] + "大师", ({"xuan" + id[index] + " dashi", "dashi"}));
	set("number",index);
	set("gender", "男性");
	set("long", long[random(sizeof(long))]);

	set("attitude", "peaceful");
	set("class", "bonze");
    set("is_trainee",1);
	set("hide",1);
	set("dontseekme",1);
	set("age", 70);
	set("shen_type", 1);
	set("str", 18);
	set("int", 25);
	set("con", 21);
	set("dex", 16);
	set("max_qi", 2000);
	set("max_jing", 1000);
	set("neili", 2500);
	set("max_neili", 2500);
	set("jiali", 150);
	set("combat_exp", 1000000);
	set("score", 100000);

	set_skill("force", 140);
	set_skill("hunyuan-yiqi", 140);
	set_skill("dodge", 100);
	set_skill("shaolin-shenfa", 100);
	set_skill("strike", 140);
	set_skill("parry", 140);
	set_skill("sanhua-zhang", 140);
	set_skill("staff", 140);
	set_skill("pudu-zhang", 140);
	set_skill("buddhism", 150);
	set_skill("literate", 150);

	map_skill("force", "hunyuan-yiqi");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("strike", "sanhua-zhang");
	map_skill("parry", "sanhua-zhang");
	map_skill("staff", "pudu-zhang");

	prepare_skill("strike", "sanhua-zhang");

	set("inquiry", ([
		"武当" : "近日本寺接到飞鸽传书，说道武当有难，老衲正要前往共商对策。\n",
			"护送" : (: ask_job :),
	]));

	create_family("少林派", 36, "弟子");

	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
		(: auto_perform :),
	}));
	set("chat_chance", 20);
	set("chat_msg", ({
		(: random_move :)
	}) );

	weapon = random(2) ? "/clone/weapon/staff/budd_staff" : 0;
	setup();

	if(weapon)
		carry_object(weapon)->wield();
	carry_object("/d/shaolin/obj/xuan-cloth")->wear();
	if (clonep())
		call_out("leave",300);   
}

void leave()
{
	object ob = this_object();
	if(!ob)
		return;
	message_vision(HIY"$N长叹一声：罢了！罢了！老衲这就去了，阿弥陀佛！\n"NOR, ob);
	message_vision(HIC"$N一转身，远远离开了这是非之地。\n" NOR, ob);
	destruct(ob);
	return;
}

void init()
{
	object me = this_player();
	add_action("do_none", "guard");
	add_action("do_none", "follow");

	::init();

}

void init2(object me)
{
	mixed tm= localtime(time());
    string day=sprintf("%d-%d-%d", tm[5], tm[4]+1,tm[3]);

	object ob = this_object();
	object ob1, ob2;
	int i,teamsize;
	int temp1,temp2,temp3;
	int exp,pot,repute;
	int total, killed;
	mapping exits;
	string *dirs;
	object env;
	int j;
	int k,m,n,cost_time;
	object *envs;
	object *envs2;
	

	if(!me)
		return;
	teamsize = query_temp("teamsize");

	if(me==query("jobleader") && file_name(environment()) == "/d/wudang/zixiao" && !present("heiyi shashou"))
	{
		if( !me->query_temp("sljob") )
		{
			call_out("leave",1);
			return;
		}
		if (!me->query("biography/jobs/husong"))
		{
			me->set("biography/jobs/husong",time());//个人传记记录第一次完成任务时间ZINE
		}
		command("nod");
		command("buddhi zhike daozhang");
		command("say 回去告诉方丈，老衲已经平安到达武当。保重！");
		CHANNEL_D->do_channel(ob, "rumor",
			sprintf("%s护送"HIG"%s"HIM"到达武当！", me->query("name"), ob->query("name")));
		me->delete("shaolin/on_husong");
		for(i=0; i<teamsize; i++)
		{
			ob1 = query_temp("team"+i);
			if(ob1 && present(ob1))
			{
				total = query_temp("sljob/total");
				killed = ob1->query_temp("sljob/killed");
				//                              if (killed > 8)
				//                                      killed = 4 + killed/2;
				exp = total * 3000 / teamsize;
				exp += killed * 2000;
				exp += 6000 * teamsize * teamsize / 2 * killed / total;  //鼓励多组队
				if(i == 0)   //team leader 额外奖励
					exp = exp * 4 / 3;
                if(killed * teamsize > total * 3 / 2)               //如果超过平均水平的1.5倍，奖励打一定的折扣，鼓励平均发展
					exp = exp * 2 / 3;
				exp = exp *2/3 + random(exp*2/3);
				exp = exp * FACTOR_HS;
				if(ob1->query("combat_exp") < 30000000)
					exp = exp * 4 / 5;
                                // modify by jpei, 太多奖励30W左右的。
                 if(exp > 100000)
                 {
                    exp = 100000 + random((exp-90000)/2);
                 }
				pot = exp/6+random(exp/10);
				//kiden: 似乎leader的奖励过高，都有超过10w的，可能要调整一下
                repute = killed * 200 + random(200);

        //whuan 特殊周效果
			exp = exp*SPEWEEK_D->query_husong_bonus()/100;
			pot = pot*SPEWEEK_D->query_husong_bonus()/100;
			repute=repute*SPEWEEK_D->query_husong_bonus()/100;
			temp1 = exp;
			temp2 = ob1->query("combat_exp")/100000000+1;
			if (temp2 > 10)
			{
				temp2=10;
			}
			if (temp2 > 2)
			{
				temp3 = temp1>>1-temp1*(temp2-2)>>4;
				pot += exp-temp3;
				exp = temp3;
			}//高于200m，就开始exp向pot转化
			exp = REWARD_D->add_exp(ob1,exp);
			ob1->add("exp/husong", exp);
			pot = REWARD_D->add_pot(ob1,pot);
			ob1->add("pot/husong", pot);
			repute = REWARD_D->add_rep(ob1,repute);

			    //加入任务统计系统 by icer
			cost_time = time()-ob1->query_temp("task_stat/husong_starttime");
			COMBAT_D->add("task_stat/husong/complete_times",1);
			COMBAT_D->add("task_stat/husong/cost_time",cost_time);
			COMBAT_D->add("task_stat/husong/exp",exp);
			COMBAT_D->add("task_stat/husong/pot",pot);
			COMBAT_D->add("task_stat/husong/repute",repute);
			COMBAT_D->add("task_stat/husong/expratio",to_float(exp)/ob1->query("combat_exp"));

			ob1->add("sl_job", 1);
			if (ob1->query("shaolin/husong_date")!=day)
			{
				ob1->set("shaolin/husong_date",day);
				ob1->set("shaolin/husong_times",1);
			}
			else
			{
				ob1->add("shaolin/husong_times",1);
			}

            ob1->add("jobs/completed/husong", 1);        //任务平衡系统，统计所有任务完成的次数  by boost  2008.09.19
						
			tell_object(ob1,HIW"好，任务完成，你得到了" 
					+ CHINESE_D->chinese_number( exp ) 
					+ "点实战经验和" 
					+ CHINESE_D->chinese_number( pot )
					+ "点潜能。\n" NOR);
			tell_object(ob1,HIR"你的声望增加了"+CHINESE_D->chinese_number( repute)+"点！\n"NOR);
			CHANNEL_D->do_channel(this_object(), "sys_misc",
			sprintf("%s在护送任务中获得经验：%d、潜能：%d、声望%d。", ob1->name(), exp, pot, repute));


			log_file("static/husong", sprintf("%s %18s"
				+"，第%5d次，%2d个杀手，死%2d个，"
				+ "奖励%4d点\n", ctime(time())[4..15], 
				ob1->query("name")+"("+ob1->query("id")+")",
				ob1->query("sl_job"),query_temp("sljob/total"),
				ob1->query_temp("sljob/killed"),exp ) );
			ob1->set("shaolin/last_husong_exp", ob1->query("combat_exp"));
		}
		ob1->delete_temp("sljob");              //不管在场不在场，一律清除记录
		}
		call_out("leave",1);

		i = random(teamsize);
		ob1 = query_temp("team"+i);
		if (ob1 && present(ob1) && random(4)==1 ) {
			tell_object(ob1,HIG"你从"+query("name")
				+"那里得到了一颗大还丹。\n" NOR);
			ob2=new("/d/shaolin/obj/dahuan-dan");
			if( ob2 )
			{
				ob2->set("owner",ob1->query("id"));
				ob2->move(ob1);
			}
		}
		return;
	}



	if(me==query("jobleader") && me->query_temp("sljob/asked") >= 2
		&& !environment(me)->query("no_fight"))
	{
		if ((add_temp("sljob/go", 1) > 4 && !random(4))
			|| query_temp("sljob/go") > 6)
		{
			set_temp("sljob/go",0);
			set_heart_beat(0);
			set_heart_beat(1);
			ob1 = new("/d/shaolin/npc/killer");
                        message_vision(HIR "突然从路边冲出一个黑衣杀手，直向$N冲去！\n"NOR, ob);
			ob1->set("dashi", ob);
			ob1->do_copy1(query_temp("team"+random(teamsize)));
//                        ob1->move(environment(me));
            ob1->move(environment(ob));
			if(ob1)
				ob1->set_leader(ob);
//
                        add_temp("sljob/total",1);

                        ob->add_temp("sljob/total",1);
			if (!random(5)) {
				message_vision(HIY"" + query("name")+"纵身奔向远方，杀手立刻提气追了上去！\n"NOR,me);
				envs=({file_name(environment(me))});
				for(m=0;m<2;m++) {
					envs2=envs;
					for(n=0;n<sizeof(envs);n++) {
						exits=envs[n]->query("exits");
						dirs=keys(exits);
						for(k=0;k<sizeof(dirs);k++) {
							env=envs[n]->query("exits/"+dirs[k]);
							if(env&&!env->query("no_fight")&&!env->query("sleep_room")) {
								for(j=0;j<sizeof(envs2);j++) if(envs2[j]==env) break; 
								if(j==sizeof(envs2)) envs2=envs2+({env});
							}
						}
					}
					envs=envs2;
				}
				me->set_temp("env",envs);
				env=envs[random(sizeof(envs))];
				move(env);
				ob1->move(env);
			}
			ob1->start_busy(0);
			ob1->command("kill " + query("id"));
		}
	}
}

int follow_me(object me, string dir)
{
	
	int result = ::follow_me(me, dir);

	if (me==query("jobleader") && me->query_temp("sljob/asked") >= 2)
	{
		me->start_busy(1+random(2));
		call_out("init2", 2, me);
	}
	return result;

/*
	object ob = this_object();
	int repeatcount;   //在迷宫重复的次数
	write(ob->query("name") + " follow " + me->query("name") + " to " + dir + "\n");
	if (me == query("jobleader"))			//居然会出现follow队伍中非leader成员，而且只有部分房间会出现，不明白，只好作此判断  by boost 2007-10-26
	{
		write(HIR"" + ob->query("name") + " follow " + me->query("name") + " to " + dir + "\n"NOR);
		if (query_temp("lastenv"))
			write(base_name(query_temp("lastenv")) + base_name(environment(me)) + "\n");
		if (query_temp("lastenv") == environment(me))           //如果在迷宫打转
		{
			write(base_name(environment(me)) + "\n");
			add_temp("lastenvcount", 1);
			repeatcount = query_temp("lastenvcount");

			if (random(query_temp("lastenvcount")) > 3 )

			{
				switch(random(3))
				{
				case 0:
					message_vision(HIC"" + query("name") + "一脸迷茫：我们什么时候才能到达武当啊？\n"NOR , ob, me);
					break;
				case 1:
					message_vision(HIC"" + query("name") + "催促" + me->query("name")+"道：武当有难，快走吧！\n"NOR, ob, me);
					break;
				default:
					message_vision(HIC"" + query("name") + "疑惑的盯着" + me->query("name")+"，似乎对" + me->query("name") + "不太信任。\n"NOR,ob,me);
					break;
				}
				random(2) ? command("sigh") : command("push " + me->query("name"));

				if (random(query_temp("lastenvcount")) > 5)
				{
					call_out("leave",1);
				}
			}
		}
		set_temp("lastenv", environment(me));
	}
	return result;
	*/
}

string ask_job()
{
	object me = this_player();
	object ob = this_object();
	string respect = RANK_D->query_respect(me);

	if(query("jobleader") != me)
		return respect + "一片好意老衲心领了，方丈已安排了高手前来护送。";
	if(!me->query_temp("sljob/asked"))
		return "咦？你不是传言被暗算了么，怎么又出现在这里？善哉！";
	if(me->query_temp("sljob/asked") >= 2)
	{
		set_leader(me);
		return "快走罢。";
	}
	message_vision(WHT"$N决定跟随$n一起行动。\n"NOR, ob, me);
	me->set_temp("sljob/asked", 2);
	set_leader(me);
	delete("chat_msg");
	return "好的，就请这位" + respect + "在前面带路，前去武当。";
}

void auto_perform()
{
	command("exert powerup");
	command("exert recover");
}

int do_copy(object me)
{
	int temp1,temp2;
	set("combat_exp", me->query("combat_exp") / 5 + 200000);

	set("max_jing", me->query("max_jing")/3);
	set("eff_jing", query("max_jing"));
	set("jing", query("max_jing"));
	set("max_jingli", me->query("max_jingli")/3);
	set("jingli", query("max_jingli"));
	temp1=me->query("max_qi");
	if (temp1 > 30000)
	{
		temp1 = 20000;
	}
	set("max_qi", temp1);
	set("eff_qi", temp1);
	set("qi", temp1);
	temp1=me->query("max_neili");
	if (temp1 > 30000)
	{
		temp1 = 10000;
	}
	set("max_neili", temp1);
	set("neili", temp1);
	set("food", 200);
	set("water", 200);

	return 1;
}

void unconcious()
{
	message_vision(HIY"$N长叹一声：罢了！罢了！老衲这就去了，阿弥陀佛！\n"NOR, this_object());
	die();
}

void die()
{
	object ob = this_object();
	object killer = get_damage_origin_object();

	if(killer)
		CHANNEL_D->do_channel(killer, "rumor", ob->query("name")+
		"在援救武当的途中被"+killer->query("name")+"杀死了。\n");
	else
		CHANNEL_D->do_channel(ob, "rumor", ob->query("name")+"在援救武当的途中圆寂了。\n");
	::die();
}

void attempt_apprentice(object ob)
{
	message_vision(WHT""+this_object()->query("name") +
		"摇了摇头，对$N说道：大敌当前，老衲暂不收徒。\n"NOR, ob);
	return;
}

int do_none()
{
	return 1;
}
