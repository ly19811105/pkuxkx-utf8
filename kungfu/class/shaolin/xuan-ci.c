// Npc: /kungfu/class/shaolin/xuan-ci.c
// Date: YZC 96/01/19
// Modified By  : iszt@pkuxkx, 2006-12-07
// 护送任务
// Modified By  : iszt@pkuxkx, 2007-02-06
// 例银，有关达摩等小改动
//护送任务修改modify by yhzzyahoo@pkuxkx，2017-4-28

#include <ansi.h>
#include <title.h>
inherit NPC;
inherit F_MASTER;
inherit "/inherit/char/silver.c";
#include <no1master.h>

string ask_me();
string ask_xisui();
int ask_damo();
string ask_job();
string ask_fail();
int do_change();
int do_copy1(object me);

string *ds_name = ({
		"远",   "济",   "恒",   "妙",   "禅",   "证",
		"鸣",   "素",   "悟",   "谛",   "竹",   "性",   
		"奥","成","法","木","定","简",
		"云","舟","无","量","易","而",
		"未","思","清","明","山","水",
		"刚","柔","并","安","松","然",
});
string *ds_id = ({
	"yuan", "ji",   "heng", "miao", "chan", "zheng",
		"ming", "su",   "wu",   "di",   "zhu",  "xing",
		"ao","cheng","fa","mu","ding","jian",
		"yun","zhou","wu","liang","yi","er",
		"wei","si","qing","ming","shan","shui",
		"gang","rou","bing","an","song","ran",
});

void create()
{
	set_name("玄慈大师", ({
		"xuanci dashi",
		"xuanci",
		"dashi",
	}));
	set("long",     "他是一位白须白眉的老僧，身穿一袭金丝绣红护法袈裟。\n"
		"他身材略显佝偻，但却满面红光，目蕴慈笑，显得神完气足。\n"
		);
	set("nickname", "少林寺方丈");
	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 70);
	set("shen_type", 1);
	set("str", 40);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	set("max_qi", 2000);
	set("max_jing", 1000);
	set("neili", 2500);
	set("max_neili", 2500);

	set("jiali", 150);
	set("combat_exp", 1000000);
	set("score", 100000);

	set_skill("force", 150);
	set_skill("hunyuan-yiqi", 150);
	set_skill("dodge", 150);
	set_skill("shaolin-shenfa", 150);
	set_skill("finger", 150);
	set_skill("strike", 150);
	set_skill("hand", 150);
	set_skill("claw", 150);
	set_skill("parry", 150);
	set_skill("nianhua-zhi", 150);
	set_skill("sanhua-zhang", 150);
	set_skill("fengyun-shou", 150);
	set_skill("longzhua-gong", 150);
	set_skill("buddhism", 150);
	set_skill("literate", 150);

	map_skill("force", "hunyuan-yiqi");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("finger", "nianhua-zhi");

	map_skill("strike", "sanhua-zhang");
	map_skill("hand", "fengyun-shou");
	map_skill("claw", "longzhua-gong");
	map_skill("parry", "nianhua-zhi");

	prepare_skill("finger", "nianhua-zhi");
	prepare_skill("strike", "sanhua-zhang");
	set("inquiry", ([
		"达摩老祖" : (: ask_damo :),
			"达摩心经" : (: ask_me :),
			"洗髓经" : (: ask_xisui :),
			"武当" : "近日接到飞鸽传书，说道武当有难，本寺正将派出玄字辈长老前往共商对策。",
			"job" : (: ask_job :),
			"护送" : (: ask_job :),
			"fail" : (: ask_fail :),
			"失败" : (: ask_fail :),
			"斋薪" : (: ask_silver :),
		    "大韦陀杵":(:do_change:),
	]));


	set("silver_name", "斋薪"); //例银的名称，默认为“例银”
	set("silver_factor", 1); //例银的数量因子，默认为1
	set("silver_family_skill", "hunyuan-yiqi"); //门派武功，提升此武功时可以领取例银，默认为parry

	set("msg_silver_firsttime", "善哉，往后每月就在老衲这里领取斋薪罢。"); //第一次打听例银的时候说的话
	set("msg_silver_record", "$N双手合十，口宣佛号：「阿弥佗佛！」\n"); //作记录时的描述\n
	set("msg_silver_check", "$N双手合十，口宣佛号：「阿弥佗佛！」\n"); //检查记录时的描述\n
	set("msg_silver_mudage", "出家人戒贪，一月之期都等不得么？"); //时间未到不能领取时说的话
	set("msg_silver_paid", "本寺斋薪虽不多，却也仰仗佛祖，务必要严守戒律才是。"); //领取成功时说的话
	set("msg_silver_score", "$N赞许地对着$n点了点头，道：「难得你对本寺如此尽心。」\n"); //由于提升师门忠诚而领取例银时的描述\n
	set("msg_silver_skill", "$N赞许地对着$n点了点头，道：「看来你的混元一气功修为大有进境。」\n"); //由于提升师门武功而领取例银时的描述\n
	set("msg_silver_exp", "$N赞许地对着$n点了点头，道：「你的武功又强了一分。」\n"); //由于提升经验而领取例银时的描述\n
	set("msg_silver_none", "善哉，数月以来似乎你并无甚进展，如何当得起这斋薪？"); //领取例银条件均不满足时说的话

	set("last_give_time", 0);
	create_family("少林派", 36, "弟子");
    set_temp("apply/armor", 300);
    set_temp("apply/damage", 250);
	set("book_count" , 1);
	set("no_get", 1);
	setup();

	setup_no1master();

	carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}
int ask_damo()
{
	mapping myfam;
	object me = this_player();
	if (!(myfam = me->query("family")) || myfam["family_name"] != "少林派")
	{
		say("达摩老祖是我少林祖师，施主非我佛门弟子，还是请回吧。\n");
		return 1;
	}
	else if (me->query("combat_exp") < 800000 && me->query_skill("buddhism", 1) < 200)
	{
		say("达摩老祖是本派祖师，正在后山修行，无事还是不要轻易打扰。");
		return 1;
	}
	else
	{
		say("老祖在达摩洞后修行，有事你可到那去找他。\n");
		me->set_temp("marks/达",1);
		return 1;
	}
}
string ask_me()
{
	mapping fam;
	object me = this_player();
	object ob;
	if (!(fam = me->query("family")) || fam["family_name"]!="少林派")
		return RANK_D->query_respect(this_player())+"与本派素无来往，不知此话从何说起？";
	if ( me->query("score") < 200 )
		return "你对本派贡献太小，宝经交给你老衲可不放心啊。";
	if (me->query("family/generation") > 37)
		return RANK_D->query_respect(this_player())+"你的地位不够，宝经不能交付你保管。";
	if(query("book_count")<1)
		return "你来晚了，宝经已经被人要走了。";
	add("book_count",-1);
	me->add("score", -random(4));
	ob = new("d/shaolin/obj/damoxinjing");
	ob->move(this_player());
	return "好吧，宝经就交给你保管了。";
}

string ask_xisui()
{
	mapping fam;
	object me = this_player();
	object ob;
	if (!(fam = me->query("family")) || fam["family_name"]!="少林派")
		return RANK_D->query_respect(this_player())+"与本派素无来往，不知此话从何说起？";
	if ( me->query("score") < 400 )
		return "你对本派贡献太小，老衲可不放心啊。";
	if (me->query("family/generation") > 38)
		return RANK_D->query_respect(this_player())+"你的辈份不够，还是先自行修习罢。";

	me->set_temp("marks/达",1);

	return "达摩老祖在达摩洞后修行，你可到那去找他要洗髓经。";
}

void attempt_apprentice(object ob)
{
	object me; 
	mapping ob_fam, my_fam;
	string name, new_name;

	me = this_object();
	my_fam = me->query("family");

	name = ob->query("name");

	if (!(ob_fam = ob->query("family")) || ob_fam["family_name"] != "少林派")
	{
		command("say " + RANK_D->query_respect(ob) + "与本派素无来往，不知此话从何谈起？");
		return;
	}

	if ( (string)ob->query("class")!="bonze" && ob_fam["family_name"] == "少林派") 
	{
		command("say " + RANK_D->query_respect(ob) + "是俗家弟子，不能在寺内学艺。");
		return;
	}

	if ( ob_fam["generation"] <= my_fam["generation"] )
	{
		command("say " + RANK_D->query_respect(ob) + "，贫僧哪里敢当 !");
		return;
	}

	if ( ob_fam["generation"] == (my_fam["generation"] + 1) && name[0..0] == "澄")
	{
		command("say " + ob_fam["master_name"] + "的徒弟怎麽跑到我这儿来了，哈哈哈 !");
		command("recruit " + ob->query("id"));
	}
	else
	{
		command("say " + RANK_D->query_respect(ob) + "，你辈份不合，不能越级拜师。");
		return;
	}

	return;
}

#include "/kungfu/class/shaolin/xuan1.h"


void recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
	{
		ob->set("title",HIR "少林" NOR + CYN "达摩院" NOR + RED "弟子" NOR);
//title系统记录玩家title by seagate@pkuxkx
	  ob->set_title(TITLE_RANK, ob->query("title"));
	}
	return;
}

void re_rank(object student)
{
	student->set("title",HIR "少林" NOR + CYN "达摩院" NOR + RED "弟子" NOR);
//title系统记录玩家title by seagate@pkuxkx
	student->set_title(TITLE_RANK, student->query("title"));
	return;
}

string ask_job()
{
	mixed tm= localtime(time());
    string day=sprintf("%d-%d-%d", tm[5], tm[4]+1,tm[3]);
	int i,temp1;
	object me = this_player();
	object ob,ob1,ob2;
	string respect = RANK_D->query_respect(me);
	object* team;
	int teamsize;
	int maxexp, minexp, totalexp, minqi;
	object maxplayer, minplayer;
	string* file = ({
		"/d/qufu/southgate", "/d/qufu/guandaos1",
		"/d/qufu/guandaos2", "/d/qufu/guandaosw2",
		"/d/qufu/guandaosw1","/d/qufu/guandaow1",
		"/d/qufu/guandaonw1","/d/qufu/guandaonw2",
		"/d/city/guandaon","/d/taishan/yidao",
		"/d/taishan/yidao1","/d/taishan/yidao2",
		"/d/taishan/yidao3","/d/taishan/daizong",
		"/d/city/beimen", "/d/city/beidajie1",
		"/d/city/beidajie2", "/d/city/guangchang", 
		"/d/city/dongdajie1","/d/city/xidajie1",
		"/d/city/xidajie2","/d/city/ximen",
		"/d/city/nandajie1", "/d/city/nandajie2",
		"/d/city/nandajie3", "/d/city/nanmen",
		"/d/zhongyuan/guandao4","/d/zhongyuan/guandao4a",
		"/d/zhongyuan/guandao2","/d/zhongyuan/guandao1",
		"/d/xinyang/eastgate","/d/xinyang/northgate",
		"/d/xinyang/southgate","/d/xinyang/shanjiao",
		"/d/xinyang/guandaoe3","/d/xinyang/guandaoe2",
		"/d/xinyang/guandaoe1","/d/xinyang/guandaon1",
		"/d/xinyang/guandaon2","/d/village/sroad4",
		"/d/village/sroad3","/d/village/sroad2",
		"/d/village/sroad1","/d/village/nwroad2",
		"/d/village/nwroad1","/d/village/eroad3",
		"/d/village/eroad2","/d/village/eroad1",
		"/d/village/sexit",
	});
	string* place = ({
		"曲阜南城门", "曲阜青石大道", "曲阜青石大道", 
		"曲阜青石大道", "曲阜青石大道", "曲阜青石大道","曲阜青石大道", 
		"曲阜青石大道",	"泰山大驿道","泰山大驿道","泰山大驿道",
		"泰山大驿道","泰山岱宗坊","扬州青石大道",
		"扬州北门", "扬州北大街", "扬州北大街", "扬州中央广场",
		"扬州东大街","扬州西大街","扬州西大街","扬州西门",
		"扬州南大街", "扬州南大街", "扬州南大街", "扬州南门",
		"中原青石大道","中原青石大道","中原青石大道","中原青石大道",
		"信阳东门","信阳北门","信阳南门","信阳鸡公山下",
		"信阳官道","信阳官道","信阳官道","信阳官道",
		"信阳官道","小山村碎石路","小山村碎石路","小山村碎石路",
		"小山村碎石路","小山村碎石路","小山村碎石路","小山村碎石路",
		"小山村碎石路","小山村碎石路","小山村南村口",
	});
	int index;
	int dashinum = sizeof(children("/d/shaolin/npc/dashi.c"));

	/*
	if(!wizardp(me))
	return 0;
	*/
	if(me->query_temp("sljob/asked"))
		return "这位"+respect+"，事不宜迟也，快去！";
	if(me->query("shaolin/on_husong"))
		return "这位"+respect+"，老衲不是交给你护送任务了么？";
	/* 首领无需正神 - whuan
	if (me->query("shen") < 0)
		return "阿弥陀佛！";
	*/

	if(time() - query("last_give_time") < 120)
		return "阿弥陀佛！本寺长老刚刚出发不久，多谢"+respect+"好意。";
	if(dashinum > 2)
		return "阿弥陀佛！这位"+respect+"，已有人在护送本寺长老了。";
	if(me->query("combat_exp") < 1000000)
		return "江湖险恶，此事关系重大，老衲还是另找他人吧。";
        if(me->query("combat_exp") > 1000000000)
                return respect+"名动江湖，老衲岂敢有劳。";
		//	if (!wizardp(me) && me->query("shaolin")==day && me->query("cabiwu/number")>=2)

		if (me->query("combat_exp") > 250000000 && me->query("shaolin/husong_date")==day && me->query("shaolin/husong_times")>=5)
		{
			return respect+"今天已经够累了，老衲不敢再有劳了。";
		}

	team = me->query_team();

	teamsize = sizeof(team);
	if(teamsize < 2)
		return "此去武当路途危险，" + respect + "切莫逞强，还要多找人手才是。";
	if(teamsize > 4)
		return "此去武当路途危险，但我们尚且不必倾巢出动，失了少林的身份。";
	for(i=0; i<teamsize; i++)
	{
		if (!team[i])
			return "你的队伍有人不在，请重新组织。";
		if (team[i] == me)
			continue;
		if (!present(team[i], environment(me)))
			return "让"+team[i]->query("name")+"速来此处，老衲好作布置。";
		//              if (!interactive(team[i]) || query_ip_number(team[i]) == query_ip_number(me))
		//                      return("say 你还是将"+team[i]->query("name")+"换成其他人吧。");
	}
	maxexp = minexp = team[0]->query("combat_exp");
	maxplayer = team[0];
	minplayer = team[0];
	minqi = team[0]->query("max_qi");
	for (i=0; i<teamsize; i++)
	{
		if (team[i]->query("combat_exp") < 1000000)
			return "此去武当路途危险，老衲看这位"
			+team[i]->query("name")+"武功似乎不足。";
		//                  if( team[i]->query("combat_exp") - team[i]->query("shaolin/last_husong_exp") < 4000 && !team[i]->query("on_test"))
		if( !team[i]->query("on_test") && (team[i]->query("combat_exp") - team[i]->query("shaolin/last_husong_exp") < 100))
		{ //由于升级造成了一些经验的降低，这里略微改一下，不知道有没有bug，by whuan
			team[i]->set("shaolin/last_husong_exp",team[i]->query("combat_exp") ); 
			return ""+team[i]->query("name")+"武功精进太慢，不太合适。";
		}
        if (team[i]->query("combat_exp") >=1000000000)
		{
			command("whisper "+ me->query("id")+" 老衲看你队伍中的"
                +team[i]->query("name")+"已经是名动江湖的大人物了，老衲岂敢惊动他老人家大驾。");


		return 0;
		}
		if (team[i]->query("combat_exp") > 250000000 && team[i]->query("shaolin/husong_date")==day && team[i]->query("shaolin/husong_times")>=5)
		{
			return "老衲看你队伍中的"
                +team[i]->query("name")+"今天已经够累了，老衲不敢再有劳了。";
		}

		team[i]->delete_temp("sljob/killed"); //删除杀的人，qianr报告的bug
		totalexp += team[i]->query("combat_exp");
		if(team[i]->query("combat_exp") > maxexp )
		{
			maxexp=team[i]->query("combat_exp");
			maxplayer=team[i];
		}
		else if(team[i]->query("combat_exp") < minexp)
		{
			minexp=team[i]->query("combat_exp");
			minplayer=team[i];
		}
		if(team[i]->query("max_qi") > minqi)
			minqi = team[i]->query("max_qi");
		
		//任务统计系统记录任务开始时间
		team[i]->set_temp("task_stat/husong_starttime",time());
		//记录任务时间
//		team[i]->set("shaolin/husong_date",day);
	}
	if(totalexp < 2500000)
		return "此去武当路途危险，依老衲看诸位武功稍显不足？";
	//          if(maxexp > minexp * 4 / 3)
	if(maxexp > minexp * 2)           //差距太小，很少玩家能组队 
		return "此去武当路途危险，诸位武功强弱差距太大，不利同进同退。";
	if(team[0] != me)
		return "还是让你们的首领来问罢。";
	

	set("last_give_time", time());
	index = random(sizeof(place));
	if(!(ob = new("/d/shaolin/npc/dashi.c")))
		return "嗯？有点问题，请向巫师报告。";
	temp1=ob->query("number");

	if(!(ob1 = new("/d/shaolin/npc/dashi.c")))
		return "嗯？有点问题，请向巫师报告。";
	else
	{//不要一样的名字
		if (temp1<35)
		{
			ob1->set("name",ds_name[temp1+1]);
			ob1->set("id",ds_id[temp1+1]);
		}
		else
		{
			ob1->set("name",ds_name[0]);
			ob1->set("id",ds_id[0]);
		}

	}
	if(!(ob2 = new("/d/shaolin/npc/dashi.c")))
		return "嗯？有点问题，请向巫师报告。";
	else
	{
		if (temp1<34)
		{
			ob2->set("name",ds_name[temp1+2]);
			ob2->set("id",ds_id[temp1+2]);
		}
		else
		{
			ob2->set("name",ds_name[1]);
			ob2->set("id",ds_id[1]);
		}	
	}
	ob->set_temp("teamsize",teamsize);
	if(teamsize>3)
		ob->set_temp("team3",team[3]);
	if(teamsize>2)
		ob->set_temp("team2",team[2]);
	if(teamsize>1)
		ob->set_temp("team1",team[1]);
	ob->set_temp("team0",me);

	message_vision(HIY"玄慈大师神色凝重的略一点头：「请"+respect+HIY"速带众人去此地护送本寺长老前往武当！」\n"NOR, me);
//	write("大师名字："+ob->query("name")+"，大师所在："+place[index]+"\n");
	ANTIROBOT_D->mxpantirobot_ex(me,ob->query("name")+"在"+place[index]);

	me->set_temp("sljob/asked",1);
	me->set("shaolin/on_husong", ob->query("name"));
	ob->do_copy(minplayer);
	ob->set("max_qi", minqi);
	ob->set("jobleader", me);
	tell_room(environment(ob), ob->name() + "走了过来。\n", ({ ob }));
	ob->move(file[index]);
	index = random(sizeof(place));
	ob1->do_copy(minplayer);
	ob1->set("max_qi", minqi);
	ob1->set("jobleader", me);
	tell_room(environment(ob1), ob1->name() + "走了过来。\n", ({ ob1 }));
	ob1->move(file[index]);
	ob2->do_copy(minplayer);
	index = random(sizeof(place));
	ob2->set("max_qi", minqi);
	ob2->set("jobleader", me);
	tell_room(environment(ob2), ob2->name() + "走了过来。\n", ({ ob2 }));
	ob2->move(file[index]);
	return "事不宜迟，请即刻动身吧！";
}

string ask_fail()
{
	object me = this_player();
	int penalty;
	string msg;
	string dashi = me->query("shaolin/on_husong");



	if(!dashi)
		return RANK_D->query_respect(me) + "莫拿此事开玩笑，又没有任务，失败什么？\n";
	msg = HIG"" + this_object()->query("name") + "双手合十，低眉念道："
		"「阿弥陀佛！" + dashi + "造化如此，也是前世的恶业罢。」\n";
	msg += HIR"$N不禁想到"+dashi+"被贼人伏击、最终不敌而死的惨酷情状，只觉脑中天旋地转，跟着轻诵佛号。\n"NOR;
	msg += HIY"" + this_object()->query("name") + "一声长叹，摆摆手，$N连忙退下。\n"NOR;
	message_vision(msg, me);
	penalty = random(10000) + 10000;
	me->add("combat_exp", -penalty);
	me->add("exp/husong", -penalty);
	me->set("shaolin/last_husong_exp", me->query("combat_exp"));  //失败也记下上次护送经验
	penalty /= 3;
	me->add("potential", -penalty);
	me->add("pot/husong", -penalty);                                 
	me->add("repute", -random(800));          
	/*
	me->add("combat_exp", -40000);
	me->add("exp/husong", -40000);
	me->set("shaolin/last_husong_exp", me->query("combat_exp"));  //失败也记下上次护送经验
	me->add("potential", -6000);
	me->add("pot/husong", -6000);
	*/
	if(me->query("combat_exp") < 5000) me->set("combat_exp", 5000);
	if(me->query("potential") < 0) me->set("potential", 0);
	me->receive_damage("jing", me->query("jing"), this_object());
	me->receive_wound("jing", me->query("eff_jing"), this_object());
	me->delete("shaolin/on_husong");
	me->delete_temp("sljob/killed");
	me->delete_temp("sljob/asked");
	return RANK_D->query_respect(me)+"不必太过自责，还须保重身体。";
}
int do_change()
{
	object ob=this_player();
	if ((int)ob->query_skill("wuying-jian", 1)>0)  
   {    
		//如果有无影剑，则先判断基本剑法与棍法的转换
		//如果有基本剑法、基本棍法并且剑法等级高，那么棍法等级等于剑法等级
		if ((int)ob->query_skill("staff", 1)>0 && (int)ob->query_skill("sword", 1)>0 && (int)ob->query_skill("staff", 1)<(int)ob->query_skill("sword", 1) )
		{
			ob->set_skill("staff",ob->query_skill("sword",1));
		}
		//如果没有基本棍法，那么棍法等级copy剑法等级
		if (!(int)ob->query_skill("staff", 1)>0 && (int)ob->query_skill("sword", 1)>0 )
		{
			ob->set_skill("staff",ob->query_skill("sword",1));
		}
		//如果有无影剑也学了大韦陀杵，进行如下判断
		if ((int)ob->query_skill("daweituo-chu", 1)>0)
		{
			if ((int)ob->query_skill("daweituo-chu", 1)<(int)ob->query_skill("wuying-jian", 1))
			{
				ob->set_skill("daweituo-chu",ob->query_skill("wuying-jian",1));    
				ob->delete_skill("wuying-jian");
				tell_object(ob,"你的无影剑已经改成大韦陀杵。\n");    
				"/cmds/skill/enable.c"->main(ob,"staff daweituo-chu");
				return 1;
			}
			else
			{
				ob->delete_skill("wuying-jian");
				tell_object(ob,"你的无影剑已经被废除。\n");  
				"/cmds/skill/enable.c"->main(ob,"staff daweituo-chu");
				return 1;
			}
		}
		//如果只有无影剑
		else
		{
			ob->set_skill("daweituo-chu",ob->query_skill("wuying-jian",1));    
			ob->delete_skill("wuying-jian");
			tell_object(ob,"你的无影剑已经改成大韦陀杵。\n");    
			"/cmds/skill/enable.c"->main(ob,"staff daweituo-chu");
			return 1;
		}
	}
	write("你根本不会无影剑，来凑什么热闹？\n");
	return 1;	
}

