// /d/luoyang/npc/xiaobanhe.c
// Created By Zine ,Nov 13 2010，一天一次20环任务
// Modified by Zine Nov 08 2012,重新修订
// 修订下sg修改的非休闲不能接任务的限制，低exp可以接xbh by yhzzyahoo @2015.4.18

#include <localtime.h>
#include <ansi.h>
inherit NPC;
#include "banhe_bonus.h"
#include "banhe_events.h"
int ask_job();
int ask_enter();
int askforhelp();
int gene_mini_maze();
int ask_mark();
void create()
{
	set_name("萧半和", ({ "xiao banhe", "xiao", "banhe" }));
	set("long",
		"他就是有「晋阳大侠」之称的萧半和。\n");
    set("title", HIW"晋阳大侠"NOR);
	set("gender", "无性");
	set("age", 50+random(5));
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	set("combat_exp", 10000000);
	set("shen_type", 1);
    set("uni_target",1);
    set("no_get", 1);
	set("attitude", "friendly");
	set("max_jingli",3000);
	set("jingli",3000);
	set("neili",3000);
	set("max_neili",3000);
	set("jiali",60);
	set("score", 12000);

	
	set_skill("sword", 350);
	set_skill("parry",350);
	set_skill("dodge", 350);
	set_skill("force",350);
	set_skill("literate",350);
	set_skill("taiyi-zhang",350);
	set_skill("strike",350);
	set_skill("taiyi-jian",350);
	set_skill("taiyi-shengong",350);
	set_skill("taiyi-you",350);
	

	map_skill("parry","taiyi-zhang");
	map_skill("sword","taiyi-jian");
	map_skill("force","taiyi-shengong");
	map_skill("dodge","taiyi-you");
	map_skill("strike","taiyi-zhang");

	
	prepare_skill("strike","taiyi-zhang");
	set_temp("apply/attack", 20);
	set_temp("apply/defense", 20);

	

	set("inquiry", ([
		"name" : "我就是萧半和。\n",
		"rumors" : "传闻没有什么，但是我听说你喜欢造谣！\n",
		"任务" : (: ask_job() :),
		"job" : (: ask_job() :),
		"寻人" : (: ask_enter() :),
		"find" : (: ask_enter() :),
		"mark" : (: ask_mark() :),
		
	]));


	set("chat_chance",1);
	set("chat_msg",({
		"萧半和自言自语道：「中慧也不知道跑到哪里去了。」\n",
        (:askforhelp:),
	}) );
	set("chat_chance_combat",100);
	set("chat_msg_combat", ({
		(: perform_action, "dodge.lingxu" :),
		(: perform_action, "sword.jianqi" :),
		(: perform_action, "sword.jianzhang" :),
		(: perform_action, "strike.jianzhang" :),
	}));
	
	setup();
	gene_mini_maze();
	carry_object("/d/city/obj/cloth")->wear();
	carry_object("/d/city/obj/changjian")->wield();
}
int gene_mini_maze()
{
	object maze=load_object("/d/jinyang/yewai");
	if (!objectp(maze)||!maze->isroom())
	{
		return 1;
	}
	if (!maze->query("initialized"))
	{
		maze->start();
	}
	set("mini_maze",maze);
	return 1;
}
int askforhelp()
{
	if (random(100)>97)
	command("chat 仁者真可无敌？\n");
}

void destroy(object ob)
{
    ob->move(VOID_OB);
	destruct(ob);
	return;
}


int accept_object(object me, object ob)
{
    if (this_object()->is_busy())
    {
        tell_object(me,"萧半和正忙着呢。\n");
        return 1;
    }
	if(ob->query("id") != "yuanyang dao"|| ob->query_temp("owner/id") != me->query("id"))
	{
		command("slap "+(string)me->query("id"));
		command("say 你怎么拿别人的东西来交差！\n");
		return 1;
	}
	if (me->query_temp("banhe/lianxu")>20)
    {
        command("hmm");
        return 1;
    }
  if ( ob->query("xbh/time") && 
       ob->query("xbh/time")!=me->query("banhe/lasttime") )
    {
        command("hmm");
        return 1;
    }
    if ( ob->query("xbh/lianxu")>me->query_temp("banhe/lianxu") )
      me->set_temp("banhe/lianxu", ob->query("xbh/lianxu"));
	this_object()->start_busy(2);
	command("nod "+(string)me->query("id"));
	command("say 干得好！\n");
	call_out("destroying", 1, ob, me);
	return 1;
}

int ask_enter()
{
	object maze,me=this_player();
	if (!maze=query("mini_maze")||!me->query_temp("banhe/random_event"))
	{
		command("say 暂时还没有中慧的下落，有劳你费心了。");
	}
	else
	{
		message_vision("$N告诉了$n萧中慧可能的下落。\n",this_object(),me);
		tell_object(me,"霎时间，你觉得你的侠义值爆棚，这件事绝对义不容辞！\n"+HIC+"你再次踏上了寻找萧中慧的路途。\n"+NOR);
		me->move(maze);
	}
	return 1;
}
int relative_exp(object me)
{
	int exp=me->query("combat_exp");
	exp+="/cmds/usr/levelup.c"->exp_require(0,(int)me->query("level"));
	exp+=me->query("transferred_exp");
	return exp;
}
int gene_robber(object me,int flag)
{
	object where,ob;
	mapping skl;
	string *sname,*robber_id,place_short;
	int i,skill = 0;
	skl = me->query_skills();
	sname  = sort_array( keys(skl), (: strcmp :) );
	for(i=0; i<sizeof(skl); i++)
	if (intp(skl[sname[i]]) && skl[sname[i]] >= skill && SKILL_D(sname[i])->type() != "knowledge")
	skill = skl[sname[i]];
	if (skill < 10) skill = 10;
	else
	{
		command("nod" + me->query("id"));
		command("say " + RANK_D->query_respect(me) + "你能愿意帮我，真是太感激了。");
		if (flag==2&&!random(5)&&!me->query_temp("banhe/random_event"))
		{
			me->set_temp("banhe/random_event",1);
			if (random_event(me)!=1)
			gene_robber(me,2);
			return 1;
		}
		while (	!objectp(where) || 
				!where->isroom()||
				TASK_D->place_belong(where)=="不明区域"||
				TASK_D->place_belong(where)=="未知区域"||
				base_name(where) == "/adm/daemons/taskd")
        {
			where = TASK_D->random_place();
        }
		place_short=TASK_D->place_belong(where) + where->query("short");
		ob = new(__DIR__"qiangdao");
		ob->set("killer", me);
		ob->do_copy(me, skill);
		robber_id=ob->parse_command_id_list();
		robber_id+=({ob->query("killer")->query("id")+"'s qiangdao","qiangdao","robber"});
		ob->set("title","形迹可疑的");
        ob->set_name(ob->query("name"),robber_id);
		if (flag==1)
		{
			command("say 有人说小女在此地址遇到了困难，我有事脱不开身，只好劳烦你去一下了！");
			ANTIROBOT_D->mxpantirobot_ex(me,place_short);
			me->set_temp("banhe/lianxu",0);
			me->set("banhe/askexp",relative_exp(me));
			me->set("banhe/accu_exp",0);
		}
		else
		{
			command("say 找小女麻烦的贼人听说还有同伙"+ob->query("name")+"在"+place_short+"作恶，可否劳烦你去解决一下？");
		}
		ob->set("xbh/time", me->query("banhe/lasttime") );
		ob->set("xbh/lianxu", me->query_temp("banhe/lianxu") );
		me->set_temp("banhe/busy", time());
		if (flag==1)
		me->set_temp("banhe/current_qiangdao",ob);
		else
		me->set_temp("banhe/current_qiangdao",ob->query("name"));
		ob->move(where);
		return 1;
	}
}
int ask_mark()
{
	object me=this_player();
	if (me->query_temp("banhe/busy"))
	{
		command("say 你现在不是正在帮我吗？别想东想西的。");
	}
	else if (relative_exp(me)-me->query("banhe/askexp")>=me->query("banhe/accu_exp")*2)
	{
		me->set("banhe/improve_mark",1);
		command("say 不错啊，进步真快，下次再来找我啊。");
	}
	else
	{
		command("say 加油加油！");
	}
	return 1;
}
int ask_job()
{
    mixed tm= localtime(time());
    string day=sprintf("%d-%d-%d", tm[5], tm[4]+1,tm[3]);
	object me = this_player(), lastob, *inv;
	
	  
	  if ( !me->query("xiuxian_player") )
	  {
		  if ( me->query("combat_exp")>10000000)
		  {//10m以下可以做xbh
		  tell_object(me, "看来萧大侠对你不太信任，拒绝了你的帮助。\n");
		  return 1;
		  }
	  }
	  
    if (me->query("banhe/lasttime")==day)
    {
        command("say 你今天已经帮过我了，多谢你的好意。\n");
		return 1;
    }
    if (relative_exp(me)-me->query("banhe/askexp")<me->query("banhe/accu_exp")*2&&!me->query("banhe/improve_mark"))
    {
        command("say " + RANK_D->query_respect(me) +"你上次帮我之后，好像都没有练功啊？罢了罢了，我用不起你，别耽误了你。\n");
		return 1;
    }
	me->delete("banhe/improve_mark");
    if (me->query("combat_exp")<=800000)
    {
        command("say " + RANK_D->query_respect(me) +"你这么菜，怎么帮助我呢？\n");
		return 1;
    }
	if (me->query("combat_exp") > 900000&&time()-me->query_temp("banhe/busy")<30)
	{
		message_vision("$N对着$n摇了摇头说：「你刚刚回来，先去休息休息吧。」\n", this_object(), me);
		return 1;
	}
	if (!me->query("banhe/lasttime"))//删除旧MARK，新版萧半和Zine 2012 11 07
	{
		me->delete("banhejob_lasttime");
		me->delete("xiaobanheaskexp");
		me->delete("currentbanhejob");
		me->delete("banhejob_busy");
		me->delete("banhejob");
	}
	lastob=me->query_temp("banhe/current_qiangdao");
	if ( objectp(lastob) )
	  destruct(lastob);
	inv=deep_inventory(me);
	for(int lp=0;lp<sizeof(inv);lp++)
	  if ( inv[lp]->query("id")=="yuanyang dao" )
	    destruct(inv[lp]);
	me->set("banhe/lasttime",day);
	return gene_robber(me,1);
}

void destroying(object obj, object me)
{
	mixed tm;
	bonus(me,1);
	if(obj) destroy(obj);
    if (me->query_temp("banhe/lianxu")<20)
    {
		gene_robber(me,2);
    }
    else
    {
        tell_object(me,BLINK+HIC+"仁者无敌，天下无双。\n"NOR);
        CHANNEL_D->do_channel(this_object(), "rw", me->query("name")+"仁者无敌，天下无双。" );
        me->add("newjobs/completed/xiaobanhe",1);
		me->delete_temp("banhe");
		tm=localtime(time());
		me->set("banhe/20",sprintf("%d-%d-%d", tm[5], tm[4]+1, tm[3]));
        tell_object(me,"你已经完成了"+chinese_number((int)me->query("newjobs/completed/xiaobanhe"))+"次萧半和任务。\n"NOR);
		finish_bonus(me);
    }
	return;
}

