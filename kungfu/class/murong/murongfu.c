// murongfu.c
// Modified by iszt@pkuxkx, 2007-05-21
// 调整描述，奖励微调，福缘影响略下降，失败惩罚和成功奖励恢复相同算法
//低于450k，奖励加速，double by yhzzyahoo
#define FACTOR_MR 0.9

#include <ansi.h>
#include <title.h>
inherit NPC;
inherit F_MASTER;
#include <no1master.h>

inherit "/inherit/char/silver.c";

string ask_bo();
int ask_wang();
int ask_dzxy();
int ask_job();
int ask_fail();
string ask_for_leave();

void create()
{
	set_name("慕容复", ({ "murong fu", "murong", "fu" }));
	set("long",
		"他就是有「南慕容」之称的慕容复。\n"
		"他看起来三十多岁，风流倜傥，果然名不虚传。\n");
	set("gender", "男性");
	set("age", 30);
	set("title",RED"姑苏慕容"NOR + HIW"少庄主"NOR);
	set("str", 35);
	set("int", 35);
	set("con", 35);
	set("dex", 35);
	set("combat_exp", 2000000);
	set("shen_type", 1);
  set("attitude", "friendly");
	set("max_jingli",3000);
	set("jingli",3000);
	set("neili",3000);
	set("max_neili",3000);
	set("jiali",60);
	set("score", 12000);

	set_skill("cuff", 250);
	set_skill("finger", 250);
	set_skill("sword", 250);
	set_skill("blade", 250);
	set_skill("parry",250);
	set_skill("dodge", 250);
	set_skill("force",250);
	set_skill("literate",250);
	set_skill("xingyi-zhang",250);
	set_skill("strike",250);
	set_skill("canhe-zhi",250);
	set_skill("murong-daofa",250);
	set_skill("murong-jianfa",250);
	set_skill("yanling-shenfa",250);
	set_skill("shenyuan-gong",250);
	set_skill("douzhuan-xingyi",250);

	map_skill("parry","douzhuan-xingyi");
	map_skill("finger","canhe-zhi");
	map_skill("sword","murong-jianfa");
	map_skill("blade","murong-daofa");
	map_skill("force","shenyuan-gong");
	map_skill("dodge","yanling-shenfa");
	map_skill("strike","xingyi-zhang");

	prepare_skill("finger","canhe-zhi");
	prepare_skill("strike","xingyi-zhang");
	set_temp("apply/attack", 20);
	set_temp("apply/defense", 20);

	create_family("姑苏慕容" , 2, "弟子");

	set("inquiry", ([
		"name" : "我就是以彼之道，还施彼身的姑苏慕容复。\n",
		"here" : "这里是大名鼎鼎的燕子坞，难道你没有听说过？\n",
		"rumors" : "家父突染恶疾，我连他老人家最后一面都没见到，此事顶有蹊跷！\n",
		"慕容博" : (: ask_bo :),
		"六脉神剑" : "家父一直想研读一下六脉神剑,可惜我没能帮他达成这个心愿。\n",
		"借兵" : "若能得到蒙古兵符调动蒙古大军，我必能实现复国的梦想。\n",
		"王语嫣" : (: ask_wang :),
		"斗转星移秘籍" : (: ask_dzxy :),
		"斗转星移" : (: ask_dzxy :),
		"任务" : (: ask_job() :),
		"job" : (: ask_job() :),
		"玉玺" : (: ask_job() :),
		"失败" : (: ask_fail() :),
		"fail" : (: ask_fail() :),
		"俸禄" : (: ask_silver :),
    "脱离门派" : (: ask_for_leave :), 
	]));

	set("silver_name", "俸禄"); //例银的名称，默认为“例银”
	set("silver_factor", 0.4); //例银的数量因子，默认为1
	set("silver_family_skill", "douzhuan-xingyi"); //门派武功，提升此武功时可以领取例银，默认为parry
	set("msg_silver_firsttime", "哈哈，跟着我好好干，俸禄少不了你的。"); //第一次打听例银的时候说的话
	set("msg_silver_paid", "为大燕复兴而努力！"); //领取成功时说的话
	set("msg_silver_none", "你为大燕复兴做了什么，就来领俸禄！"); //领取例银条件均不满足时说的话

	set("chat_chance",5);
	set("chat_msg",({
		"慕容复自言自语道：「我一定要继承父志，复兴大燕。」\n",
		"慕容复道：「哪里可以借到兵呢？」\n",
	}) );
	set("chat_chance_combat",100);
	set("chat_msg_combat", ({
		(: perform_action, "parry.xingyi" :),
		(: perform_action, "sword.lianhuan" :),
		(: perform_action, "sword.liuxing" :),
		(: perform_action, "sword.xingdou" :),
	}));
	set("paper_count", 1);
	setup();
	setup_no1master();
	carry_object("/d/murong/npc/obj/shoes1")->wear();
	carry_object("/d/murong/npc/obj/cloth")->wear();
	carry_object("/d/city/obj/changjian")->wield();
}

void init()
{
	      add_action("do_leave",  "leave");
	      ::init();
}

string ask_for_leave()
{
	object me;

	me = this_player();

	if( (string)me->query("family/family_name") != "姑苏慕容")
		return "你非我姑苏慕容弟子，脱离门派的事情我作不得主。";

	me->set_temp("pending/leave_murong", 1);
  return "如果" + RANK_D->query_respect(me) + "真想离我姑苏慕容而去，就请下决心(leave)吧！";
}

int do_leave()
{
	object me = this_player();
	
	if (me->query_temp("pending/leave_murong") != 1)
		return 0;
	message_vision("$N对$n说道：「从此你就不再是我姑苏慕容门下了，请好自为之！」\n",this_object(), me );
	tell_object(me,HIR "你决定叛出姑苏慕容门下！\n" NOR);
	me->delete_temp("pending/leave_murong");
  me->expell_family("姑苏慕容");
	if (me->query("combat_exp") >= 1000)
		me->add("betrayer",1);
	return 1;
}	

void destroy(object ob)
{
        ob->move(VOID_OB);
	destruct(ob);
	return;
}

void attempt_apprentice(object ob)
{
	if((string)ob->query("family/family_name")!="姑苏慕容")
	{
		command("say "+RANK_D->query_respect(ob)+"要想拜本派,可先拜阿碧、阿朱。\n");
		return;
	}
	if((string)ob->query("family/master_id") == "murong bo")
	{
		command("say "+RANK_D->query_respect(ob)+"已经拜了家父，我怎敢再收你为徒。\n");
		return;
	}

	if((int)ob->query("score") < 1000)
	{
		command("say "+RANK_D->query_respect(ob)+"对本派的贡献还不够。\n");
		return;
	}

	if((int)ob->query_skill("shenyuan-gong",1) < 100)
	{
		command("say " + RANK_D->query_respect(ob) + "对我派内功的修为还不够，还需要多加练习。");
		return;
	}
	command("say 好吧，"+RANK_D->query_respect(ob)+"，我就收下你了！");
	command("recruit "+ob->query("id"));
	command("haha");
	CHANNEL_D->do_channel(this_object(), "jh", "我姑苏慕容又增添了一份力量，复兴大燕有希望了！");
	ob->set("title",RED"姑苏慕容"NOR + HIB"总管"NOR);
//title系统记录玩家title by seagate@pkuxkx
	ob->set_title(TITLE_RANK, ob->query("title"));

}
void recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
	{
		ob->set("title",RED"姑苏慕容"NOR + HIB"总管"NOR);
//title系统记录玩家title by seagate@pkuxkx
	  ob->set_title(TITLE_RANK, ob->query("title"));
	}
	return;
}
string ask_bo()
{
	object me;
	object ob;
	me=this_player();

	if( me->query("family/family_name")!="姑苏慕容")
	{
		return"这位" + RANK_D->query_respect(me) + "与本派素无来往，询问此事是何道理？";
	}
	if( me->query("family/master_id")!="murong bo")
		return" 家父已经在几年前病逝了，你就不要多问了，你下去吧！";
	if( query("paper_count") > 0)
	{
		command("say 你已经拜了家父为师了！他老人家还好吗？\n");
		command("say 他老人家最近在什么地方，你给我捎封信给他吧。\n");
		add("paper_count",-1);
		ob = new("/d/murong/npc/obj/fbpaper");
		ob->move(me);
		me->set_temp("murong/paper",1);
		return" 这件事就拜托你了，你要用心去办哪！\n";
	}
	return "你见到老爷子我就放心了，你下去吧！";
}

int ask_wang()
{
	object me,ob;
	me = this_player();
	if(base_name(environment()) != query("startroom"))
		return 0;
	command("say 语嫣是我表妹，我挺喜欢她的，不过......\n");
	command("say 这样吧，这里有封信，帮我带给她吧，多谢！\n");
	ob = new("/d/murong/npc/obj/fwpaper");
	ob->move(me);
	me->set_temp("murong/qing",1);
	command("say 拜托你了！\n");
	return 1;
}

int ask_dzxy()
{
	object me,ob;
	me = this_player();
	if(me->query("family/family_name")!="姑苏慕容")
	{
		command("say 斗转星移是我派武功秘笈，不能乱给别人。\n");
		return 1;
	}
	if(!me->query_temp("murong/dzxy"))
	{
		command("say " + RANK_D->query_respect(me) + "若能帮在下一个小忙，我就给你秘笈。\n");
		return 1;
	}
	if(base_name(environment()) != query("startroom"))
	{
		command("say 对不起，斗转星移秘笈在下没有带出来。");
		return 1;
	}
	ob = new("/d/murong/npc/obj/dzxy_book");
	ob->move(me);
	me->delete_temp("murong/dzxy");
	command("say 这本斗转星移秘籍你拿去读吧，要好好保存哪！");
	return 1;
}

int destletter(object ob)
{
	if(ob)
	destruct(ob);
	return 1;
}

int accept_object(object me, object ob)
{
	object obb;
	me=this_player();

	this_object()->start_busy(2);
    if( ob->query("letterback")==3&&ob->query("owner")==me->query("id"))
    {
        call_out("destletter", 1, ob);
        message_vision("$N接过$n手里的家信，感动的热泪盈眶：这是老婆写给我的信，我，我不会亏待你的！",this_object(),me);
	    me->set_temp("extrajob/mr",1);
        return 1;
    }
	if(ob->query("id") == "yu xi"
				&& me->query("murong/yuxi") == 1
				&& !me->query("murong/done"))
		{
			command("slap "+(string)me->query("id"));
			command("say 过期的东西别给我！\n");
			return 0;
		}
	if(ob->query("id") == "yu xi"
			&& me->query("murong/yuxi") == 1
			&& ob->query_temp("owner/id") == me->query("id"))
	{
		me->add("jobs/completed/murong",1);
		command("nod "+(string)me->query("id"));
		command("say 干得好！\n");
		call_out("destroying", 2, ob, me);
		return 1;
	}
	else
		if(ob->query("id") == "yu xi"
				&& me->query("murong/yuxi") == 1
				&& ob->query_temp("owner/id") != me->query("id"))
		{
			command("slap "+(string)me->query("id"));
			command("say 你怎么拿别人的东西来交差！\n");
			return 0;
		}

	if((string)me->query("family/family_name")!="姑苏慕容")
	{
		if(ob->query("id")=="hui xin")
		{
			command("nod");
			command("say 是老爷子的回信，多谢你了！");
			call_out("destroy",1,ob);
			return 1;
		}
		else if(ob->query("id")=="bing fu")
		{
			command("bow");
			command("say 你给我带来了蒙古兵符，太感谢你了！");
			call_out("destroy",1,ob);
			return 1;
		}
	}
	else
	{
		if(ob->query("id")=="hui xin")
		{
			command("nod");
			command("say 是老爷子的回信，多谢你了！");
			me->set_temp("murong/huixin2",1);
			call_out("destroy",1,ob);
			call_out("check",0,me);
			return 1;
		}
		else if(ob->query("id")== "bing fu")
		{
			command("admire");
			command("say 你给我带来了蒙古兵符，太感谢你了！");
			me->set_temp("murong/bingfu",1);
			call_out("destroy",1,ob);
			call_out("check",0,me);
			return 1;
		}
	}

	if(ob->query("id")=="shou juan")
	{
		if(me->query_temp("murong/juan"))
		{
			command("say 多谢你了！\n");
			command("say 我知道表妹很惦记我，你把这把扇子交给表妹，叫他放心。");
			obb=new("/d/murong/npc/obj/shan");
			obb->move(me);
			me->set_temp("murong/shan",1);
			me->delete_temp("murong/juan");
			call_out("destroy",1,ob);
			return 1;
		}else
		{
			command("say 多谢你了。你下去吧！\n");
			call_out("destroy",1,ob);
			return 1;
		}
	}
	return 0;
}

void check(object me)
{
	object ob;
	int sc;
	me=this_player();

	if( me->query_temp("murong/huixin")
			&& me->query_temp("murong/huixin2")
			&& me->query_temp("murong/bingfu"))
	{
		command("say 见你这么忠心，就准许你进入还施水阁参悟！");
		//	  sc=random(20);
		//	  me->add("score","sc");
		me->delete_temp("murong/huixin");
		me->delete_temp("murong/huixin2");
		me->delete_temp("murong/bingfu");
		me->set_temp("murong/tingxiang",1);
	}

}
int ask_job()
{
	object me = this_player();
	int time = time();
	object ob, yuxi,where;
	mapping quest = ([]);
	mapping skl;
	string *sname, place;
	int i, f, skill = 0;
	int pin,busytime;
    int cdmore;
	skl = me->query_skills();
	if ( !skl ) {
		tell_object(me, "你先去学一些本事吧！\n");
		return 1;
	}
	sname  = sort_array( keys(skl), (: strcmp :) );
	for(i=0; i<sizeof(skl); i++)
		if (intp(skl[sname[i]]) && skl[sname[i]] >= skill && SKILL_D(sname[i])->type() != "knowledge")
			skill = skl[sname[i]];
  
	if (skill < 10) skill = 10;
  
    cdmore=0;
    if (me->query("murongjob/mayberobot")&&me->query("combat_exp")>3000000 && me->query("antirobot/deactivity") > 1)
    {
        cdmore=120;
    }
	if (me->query("mud_age") < 86400)
	{
		command("haha");
		command("say " + RANK_D->query_respect(me) + "还太年轻，去找大燕传国玉玺太难为你了。");
		return 1;
	}
	if (me->query_combatgrade() < 3)
	{
		command("haha");
		command("say " + RANK_D->query_respect(me) + "的经验不足，叫我怎么放心让你去？");
		return 1;
	}
	if (me->query_combatgrade() >=20)
	{
			busytime = 40;
		if ((time- me->query("mrjob_busy"))<busytime+cdmore&&time()>me->query("mrjob_busy"))
		{
			message_vision("$N对着$n摇了摇头说：「你刚做过任务，先去休息休息吧。」\n", this_object(), me);
			return 1;
		}
	}
	//防止连续故意fail降经验
	if (me->query("murong/lianxu_fail") > 4)
			if (time() - me->query("mrjob_busy") < (60+cdmore)*(me->query("murong/lianxu_fail")-4)&&time()> me->query("mrjob_busy"))
			{
				message_vision("$N对着$n摇了摇头说：「你连续失败次数过多，先去休息休息吧。」\n", this_object(), me);
				return 1;
			}
	if (me->query("antirobot/deactivity") > 2) message("vision",HIR"慕容复一巴掌扇在你的大脸瓜子上，吼道：“小小机器人，别想在我这儿占便宜！”\n"NOR,me);
	if (me->query("murong/yuxi") == 1)
	{
		command("kick " + me->query("id"));
		command("say 我不是给了你任务了吗？");
		return 1;
	}
	else
	{
		me->delete("murong/random_place");
        me->set("当机CD补偿4",1);

		//分配随机地点
        where = MAP_D->random_place_ex(me);
        if(MAP_D->place_belong(where))//随机分配成功
        {
            quest["place"]=base_name(where);
            quest["short"]=MAP_D->place_belong(where) + where->query("short");
            me->set("murong/random_place",1);
        }

        command("nod" + me->query("id"));
		command("say " + RANK_D->query_respect(me) + "能为大燕出力，真是太好了。");
        if ((random(100)>74||me->query("murong/pic")) && !ANTIROBOT_D->stopped())
            {
                tell_object(me,HIC"慕容复说道：大燕传国玉玺在以下地点附近出现，快去吧！\n" NOR);
                ANTIROBOT_D->mxpantirobot_ex(me,quest["short"]);
                me->set("murong/pic",1);
            }
        else
        {
	
            tell_object(me,HIC"慕容复说道：大燕传国玉玺在『" + quest["short"] + "』附近出现，快去吧！\n" NOR);
        }
		ob = new(__DIR__"qiangdao",1);
		ob->set("killer", me->query("id"));
		ob->do_copy(me, skill);
		ob->set("title",me->query("name")+"发现的");
    ob->set_name(ob->query("name"),({ob->query("killer")+"'s murong pantu","murong pantu","pantu"}));
		pin = random(1000);
		ob->set("murong/pin",pin);
		me->set("murong/pin",pin);
		me->set("murong/current_qiangdao",ob);
		ob->move(quest["place"]);
		//从上面移过来避免叛徒一出现就死亡时找不到ob出错，iszt 2006-09-02
		me->set("murong/yuxi", 1);
		me->set("mrjob_busy", time());
		me->set_temp("murong/yuxi_where",quest["short"]);
        if (me->query("murong/pic"))
        {
            me->set_temp("murong/yuxi_where","未知区域");
        }
		return 1;
	}
}

int ask_fail()
{
	object me = this_player();
	object qiangdao;
	
	int exp, pot, rep, sc;

	exp = (me->query("kar")/2 + 40) * (14 + random(25));
        exp = exp / 2; //降低难度，by whuan，2007-5-24
	pot = exp / 8;
        rep = 20 * random(2) + 20;
	sc = 1 + random(5);
	if (me->query_combatgrade() < 20)
	{
		exp = exp / 4;
		pot = exp / 8;
	}
	else if (me->query_combatgrade() < 30)
	{
		exp = exp / 2;
		pot = exp / 8;
	}
	exp = exp * FACTOR_MR;
	pot = pot * FACTOR_MR;
	//iszt@pkuxkx, 2006-09-13
    if (me->query("combat_exp")<450000)//450K之前新人没有其他好任务，进一步降低难度。Zine 2011-08-03
    {
        exp=exp/5;
        pot=pot/5;
    }
    if (exp<1)
    {
        exp=1;
    }
    if (pot<1)
    {
        pot=1;
    }
    if (me->query("murong/pic"))
    {   
        exp=exp*2;
        pot=pot*2;
    }
	if (me->query("murong/yuxi") == 1) {
		command("sigh");
		command("say 你这身手也来找宝物。");
		if((string)me->query("family/family_name")!="姑苏慕容")
		{
            exp=REWARD_D->add_exp(me,-exp);
            me->add("exp/murong", exp);
            pot=REWARD_D->add_pot(me,-pot);
            me->add("pot/murong", pot);
            rep=REWARD_D->add_rep(me,-rep);
            me->add("rep/murong", rep);  // Zine Oct 31 2010 用rewardd控制奖励
			tell_object(me,HIC "由于你没有找回大燕传国玉玺，被扣除：\n"
				+ chinese_number(-exp) + "点实战经验，\n"
				+ chinese_number(-pot) + "点潜能，\n"
				+ chinese_number(-rep) + "点江湖声望作为惩罚。\n" NOR);            
		}
		else
		{
			if (me->query_combatgrade() >= 30)   
            sc = 2 * sc;

            exp=REWARD_D->add_exp(me,-exp);
            me->add("exp/murong", exp);
            pot=REWARD_D->add_pot(me,-pot);
            me->add("pot/murong", pot);
            sc=REWARD_D->add_score(me, -sc);// Zine Oct 31 2010 用rewardd控制奖励
			tell_object(me,HIC "由于你没有找回大燕传国玉玺，被扣除：\n"
				+ chinese_number(-exp) + "点实战经验，\n"
				+ chinese_number(-pot) + "点潜能，\n"
				+ chinese_number(-sc) + "点师门忠诚度作为惩罚。\n" NOR);
                if (me->query("score")<1)// Zine 防止门忠变成负值的bug
                {
                    me->set("score",1);
                }
		}
		
		if(me->query("combat_exp") < 2000) me->set("combat_exp",2000);
		
		//if (me->query("potential") < me->query("learned_points"))
		//	me->set("potential", me->query("learned_points"));
		me->delete("murong/yuxi");
		me->delete("murong/lianxu");
		me->delete("murong/pin");
		me->delete("murong/done");
		me->add("murong/lianxu_fail",1);
		if (objectp(qiangdao=me->query("murong/current_qiangdao")))
			qiangdao->leave();
		if (me->query("murong/pic"))
        {   
            me->set("mrjob_busy", time()+60);
        }	
		return 1;
	}
	else
		tell_object(me,HIC "你没有接过任务啊。\n");
	return 1;
}

void destroying(object obj, object me)
{
	int exp, pot, rep, sc, random_opt, gold, cost_time,adv;
	
	if ( me->query("murong/hard") )
	{
	    adv=1;
	    me->delete("murong/hard");
	}
	
	if ( adv )
	  exp = (me->query("kar")/2 + 40) * (24 + random(15));
	else 
	  exp = (me->query("kar")/2 + 40) * (14 + random(25));
	
	random_opt = (int)me->query("murong/random_place");
	me->delete("murong/random_place");
	if (random_opt != 0)
		exp = (exp * 9) / 5; //随机地点的玉玺任务奖励1.8倍(原来为1.5倍)
	pot = exp / 8;
	rep = 20 * random(5) + 150;  //玩家初期声望不够，提升一点声望奖励。by picewolf
	sc = 1 + random(5);
    if (!me->query("biography/jobs/murong"))
	{
		me->set("biography/jobs/murong",time());//个人传记记录第一次完成任务时间ZINE
	}
    if (me->query("combat_exp")-me->query("murong/lastexp")<200)
        {
            me->set("murong/mayberobot",1);
        }
        if (me->query("combat_exp")-me->query("murong/lastexp")>=200)
        {
            me->delete("murong/mayberobot",1);
        }
	if (me->query_combatgrade() < 10)
	{
		exp = exp / 4;
		pot = exp /8;
		gold=2000;
	}
	else if ((me->query_combatgrade() < 20) && (me->query_combatgrade() >= 10))
	{
		exp = exp / 3;
		pot = exp /8;
		gold=5000;
	}
	else if ((me->query_combatgrade() < 30) && (me->query_combatgrade() >= 20))
	{
		exp = exp / 2;
		pot = exp /8;
		gold=8000;
	}
	else if (me->query_combatgrade() < 50)
	{
		exp = exp / 3 * 2;
		pot = exp /8;
		gold=12000;
	}
        me->set("murongjob/mayberobot",1);
        if (me->query("jobs/completed/huyidao")-me->query("murongjob/hyd")>0
            ||me->query("jobs/completed/hubiao")-me->query("murongjob/hb")>0
            ||me->query("jobs/completed/xiaofeng")-me->query("murongjob/xf")>0
            ||me->query("jobs/completed/task")-me->query("murongjob/task")>0
            ||me->query("jobs/completed/husong")-me->query("murongjob/hs")>0
            ||me->query("newjobs/completed/pyh")-me->query("murongjob/pyh")>0) //by Zine 反机器人设定
        {
            me->delete("murongjob/mayberobot",1);
        }
    
    
    
	exp = exp * FACTOR_MR;
	pot = pot * FACTOR_MR;
	gold= 15000+random(10000);
	//特殊周效果
        exp = exp * SPEWEEK_D->query_murong_bonus()/100;
        pot = pot * SPEWEEK_D->query_murong_bonus()/100;  
        rep = rep * SPEWEEK_D->query_murong_bonus()/100;
	if ((me->query("combat_exp"))<1000000) gold=gold/3;

	//iszt@pkuxkx, 2006-09-13
	if(obj) destruct(obj);
	
	//全自动机器人影响
    if (!me->query("murongjob/mayberobot"))
        {
            exp=exp*21/20;
            pot=pot*21/20;
            rep=rep*21/20;
        }
        if (me->query_temp("extrajob/mr"))
        {
            me->delete_temp("extrajob/mr");
            exp=exp*2;
            pot=pot*2;
            rep=rep*2;
        }
	if (me->query("combat_exp")<450000)
    {
        exp=exp*12/5;
        pot=pot*12/5;
		rep=rep*2;
    }
    if (me->query("murong/pic"))
    {   
        exp=exp*2;
        pot=pot*2;
        me->delete("murong/pic");
        ANTIROBOT_D->same_as_fullme(me);
    }
	  if ( adv )
	  {
	      exp=exp*150/100;
	      pot=pot*400/100;
	      me->add("cjg/point", 1 );
	  }
    exp = REWARD_D->add_exp(me,exp);
	  pot = REWARD_D->add_pot(me,pot);
    me->set("murongjob/hyd",me->query("jobs/completed/huyidao"));
    me->set("murongjob/hb",me->query("jobs/completed/hubiao"));
    me->set("murongjob/xf",me->query("jobs/completed/xiaofeng"));
    me->set("murongjob/task",me->query("jobs/completed/task"));
    me->set("murongjob/hs",me->query("jobs/completed/husong"));
    me->set("murongjob/pyh",me->query("newjobs/completed/pyh"));
	
	if((string)me->query("family/family_name")!="姑苏慕容")
	{
		rep=REWARD_D->add_rep(me,rep);
		CHANNEL_D->do_channel(this_object(), "sys_misc",
			sprintf("%s在慕容任务中获得经验：%d、潜能：%d。", me->name(), exp, pot));
	  if ( adv )
		  tell_object(me,HIC "由于你成功的找回大燕传国玉玺，被奖励：\n"
			  + chinese_number(exp) + "点实战经验，\n"
			  + chinese_number(pot) + "点潜能，\n"
			  + chinese_number(rep) + "点江湖声望，\n"
			  + "一点任务积分作为答谢。\n" NOR);
	  else
		  tell_object(me,HIC "由于你成功的找回大燕传国玉玺，被奖励：\n"
			  + chinese_number(exp) + "点实战经验，\n"
			  + chinese_number(pot) + "点潜能，\n"
			  + chinese_number(rep) + "点江湖声望作为答谢。\n" NOR);
		me->add("exp/murong", exp);
		me->add("pot/murong", pot);
	}
	else
	{
		if (me->query_combatgrade() >= 30)   sc = 2 * sc;
		sc=REWARD_D->add_score(me,sc);
		CHANNEL_D->do_channel(this_object(), "sys_misc",
			sprintf("%s在慕容任务中获得经验：%d、潜能：%d。", me->name(), exp, pot));
	  if ( adv )
		  tell_object(me,HIC "由于你成功的找回大燕传国玉玺，被奖励：\n"
			  + chinese_number(exp) + "点实战经验，\n"
			  + chinese_number(pot) + "点潜能，\n"
			  + "一点任务积分，\n"
			  + chinese_number(sc) + "点师门忠诚度。\n" NOR);
	  else
		  tell_object(me,HIC "由于你成功的找回大燕传国玉玺，被奖励：\n"
			  + chinese_number(exp) + "点实战经验，\n"
			  + chinese_number(pot) + "点潜能，\n"
			  + chinese_number(sc) + "点师门忠诚度。\n" NOR);
		me->add("exp/murong", exp);
		me->add("pot/murong", pot);
	}

	//加入任务统计系统 by icer
	cost_time = time()-me->query("mrjob_busy");
	me->add("task_stat/yuxi/complete_times",1);
	COMBAT_D->add("task_stat/yuxi/complete_times",1);
	COMBAT_D->add("task_stat/yuxi/cost_time",cost_time);
	COMBAT_D->add("task_stat/yuxi/exp",exp);
	COMBAT_D->add("task_stat/yuxi/pot",pot);
	COMBAT_D->add("task_stat/yuxi/repute",rep);
	COMBAT_D->add("task_stat/yuxi/expratio",to_float(exp)/me->query("combat_exp"));
	
	REWARD_D->add_money(me,gold);
	me->add("murong/lianxu",1);
	me->delete("murong/yuxi");
	me->delete("murong/lianxu_fail");
	me->delete("murong/done");
	command("smile "+me->query("id"));
	command("whisper "+me->query("id")+" 为了表达对你的谢意，我已经吩咐下人向你的帐户存了一些辛苦费！");
	return;
}

