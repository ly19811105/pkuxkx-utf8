// modified by iszt@pkuxkx, 2006 and 2007-02-05
// modified by zine@pkuxkx 2013 增加大宋入口
#define FACTOR_XY 0.98
#define SONG_ENTRY 100000 //大宋入门阈值，提高可以增大难度
#define CT_ENTRY 150000 //朝廷封王阈值，提高可以增大难度
#include <ansi.h>
inherit NPC;
#include "xytaskd.h"
#include <localtime.h>
string ask_for_jiangli();
string ask_for_gongshi();
string ask_for_baowei();
int ask_for_baoxiao();
int ask_for_baoxiao2();
void create()  
{
	set_name(RED "郭靖" NOR, ({ "guo jing","jing","guo" }));
	set("nickname", GRN"威震中原,名贯漠北"NOR);
	set("nocleanup", 1);
	set("id", "guo jing");
	set("title",YEL"北侠"NOR);
	set("gender", "男性");
	set("age", 40);
	set("str", 30);
	set("dex", 60);
	set("long", "这就是一代大侠郭靖。\n");
	set("combat_exp", 1800000);
        set("uni_target", 1);
	set("shen_type",1);
	set("attitude", "peaceful");
	set_skill("strike", 220);
	set_skill("force", 200);
	set_skill("xianglong-zhang", 250);
	set_skill("xiaoyaoyou", 300);        // 逍遥游
	set_skill("huntian-qigong", 300);    // 混天气功
	set_skill("dodge", 200);
	set_skill("parry", 300);                

	map_skill("force", "huntian-qigong");
	map_skill("strike", "xianglong-zhang");
	map_skill("parry", "xianglong-zhang"); 
	map_skill("dodge", "xiaoyaoyou");
	prepare_skill("strike", "xianglong-zhang");
	set_temp("apply/attack", 50);
	set_temp("apply/defense", 50);
	set_temp("apply/armor", 50);
	set_temp("apply/damage", 30);

	set("neili", 4000); 
	set("qi", 6000); 
	set("max_qi", 6000); 
	set("max_neili", 4000);
	set("jingli", 4000); 
	set("max_jingli", 4000);

	set("inquiry",([
	"保卫" : (: ask_for_baowei :), 
	"奖励"  : (: ask_for_jiangli :),
	"工事" : (: ask_for_gongshi :),
	"报效国家" : (: ask_for_baoxiao :),
	"帮助守城" : (: ask_for_baoxiao2 :),
	]));
	set("chat_chance",1);
	set("chat_msg", ({
	"听说有蒙古奸细混进城中，不知是真是假？\n",
	"蒙古大军终于来了，大家一定要把城门守好！\n"
	}) );
	setup();
	carry_object("/clone/armor/tiejia")->wear();
}
int unconcious()
{
	return 1;
}
int die()
{
	if(!query("killed")) return 1;
	::die();
}
int ask_for_baoxiao2()
{
	object me=this_player();
	if (me->query("class")!="officer")
	{
		command("say 你不是朝廷中人，有心的话也可以报效国家。");
		tell_object(me,HIR"ask guo about 报效国家，这将可能加入大宋官员（将保留原来师门）。\n"NOR);
		return 1;
	}
	if (me->query("pin")!=1)
	{
		command("say 现在朝廷在荆襄布置了近十万大军，以大人的资历，似乎不足以指挥。");
		return 1;
	}
	if (me->query("chaoting/wang")||me->query("chaoting/jiawang"))
	{
		command("say 下官不敢让大人专美于前，杀敌的事就交给我们吧。");
		return 1;
	}
	if (me->query("presong/start"))
	{
		command("say 你之前已经决定了报效国家。");
		return 1;
	}
	if (me->query("chaoting/prewang/start"))
	{
		command("say 你之前已经决定了帮助守城。");
		return 1;
	}
	if (!me->query_temp("chaoting/baoxiao"))
	{
		command("say 如果你决定帮助守卫襄阳，将在成功晋升上柱国之前，没有任何奖励可拿。\n");
		tell_object(me,"这个决定作出之后，必须连续七天胜利完成保卫并作出一定程度的贡献。如同意此条件，请再次ask guo jing about 帮助守城。\n");
		tell_object(me,HIR+"在未达到此目标之前，保卫任务将无实际经验潜能声望获得。\n"+NOR);
		tell_object(me,HIR+"如遇到某日未完成保卫或贡献太少，计次将从零开始。\n"+NOR);
		me->set_temp("chaoting/baoxiao",1);
		return 1;
	}
	me->delete_temp("chaoting/baoxiao");
	command("say 大人心善，果然爱惜子民。");
	me->set("chaoting/prewang/start",1);
	tell_object(me,HIR+"你选择了帮助守城，如果在连续七天胜利完成保卫并作出一定程度的贡献，朝廷不会亏待你的。\n"+NOR);
	tell_object(me,HIR+"在未达到此目标之前，保卫任务将无实际经验潜能声望获得。\n"+NOR);
	tell_object(me,HIR+"如遇到某日未完成保卫或贡献太少，计次将从零开始。\n"+NOR);
	return 1;
}
int ask_for_baoxiao()
{
	object me=this_player();
	if (me->query("song/pro"))
	{
		command("say 大人本来就是大宋的官员，别开玩笑了。");
		return 1;
	}
	if (me->query("presong/start"))
	{
		command("say 你之前已经决定了报效国家。");
		return 1;
	}
	if (me->query("chaoting/prewang/start"))
	{
		command("say 你之前已经决定了帮助守城。");
		return 1;
	}
	if (!me->query_temp("song/baoxiao"))
	{
		command("say 如果你决定报效国家，将在被甄选为大宋官员之前，没有任何奖励可拿。\n");
		tell_object(me,"这个决定作出之后，必须连续七天胜利完成保卫并作出一定程度的贡献。如同意此条件，请再次ask guo jing about 报效国家。\n");
		tell_object(me,HIR+"在未达到此目标之前，保卫任务将无实际经验潜能声望获得。\n"+NOR);
		tell_object(me,HIR+"如遇到某日未完成保卫或贡献太少，计次将从零开始。\n"+NOR);
		me->set_temp("song/baoxiao",1);
		return 1;
	}
	me->delete_temp("song/baoxiao");
	command("say 侠之大者，为国为民，"+me->query("name")+"，果然不同于一般人。");
	me->set("presong/start",1);
	tell_object(me,HIR+"你选择了报效国家，如果在连续七天胜利完成保卫并作出一定程度的贡献，将获得郭大侠推荐进入大宋官场。\n"+NOR);
	tell_object(me,HIR+"在未达到此目标之前，保卫任务将无实际经验潜能声望获得。\n"+NOR);
	tell_object(me,HIR+"如遇到某日未完成保卫或贡献太少，计次将从零开始。\n"+NOR);
	return 1;
}
int calcu_ct(object me,int reward)
{
	mixed* timeinfos = localtime(time());
	int hour,minute,second,total_sec,next_due;
	float percent;
	string day=sprintf("%d-%d-%d", timeinfos[5], timeinfos[4]+1,timeinfos[3]);
	if (me->query("chaoting/prewang/finish_day")==day)
	{
		tell_object(me,HIR+"你已经完成了本日的帮助守城任务。\n"+NOR);
		return -1;
	}
	hour= timeinfos[LT_HOUR];
    minute = timeinfos[LT_MIN];
	second = timeinfos[LT_SEC];
	total_sec=second+minute*60+hour*3600;
	next_due=172800+(time()-total_sec);
	if (me->query("chaoting/prewang/today")!=day)
	{
		me->set("chaoting/prewang/today_tasks",0);
		me->set("chaoting/prewang/today",day);
		if (me->query("chaoting/prewang/next_due")&&time()>me->query("chaoting/prewang/next_due"))
		{
			me->set("chaoting/prewang/total_check",0);
			tell_object(me,HIR+"因为你没有在连续两天都完成帮助守城任务，所以你的完成总次数被清零。\n"+NOR);
		}
	}
	me->add("chaoting/prewang/today_tasks",reward);
	if (me->query("chaoting/prewang/today_tasks")>=CT_ENTRY)
	{
		me->set("chaoting/prewang/today_tasks",0);
		me->add("chaoting/prewang/total_check",1);
		if (me->query("chaoting/prewang/total_check")>=7&&!me->query("chaoting/wang")&&!me->query("chaoting/jiawang"))
		{
			tell_object(me,"你已经连续七日完成了帮助守城任务，恭喜恭喜！\n");
			command("say 朝廷急召大人回临安，吴枢密正在大庆殿内相候。");
			return 1;
		}
		me->set("chaoting/prewang/finish_day",day);
		me->set("chaoting/prewang/next_due",next_due);
		tell_object(me,HIR+"你已经完成了本日的帮助守城任务，你必须在"+ctime(next_due)+"之前再胜利完成三轮保卫任务。\n"+NOR);
	}
	else
	{
		percent=to_float(me->query("chaoting/prewang/today_tasks"))/to_float(CT_ENTRY)*100;
		tell_object(me,HIR+"你本日的帮助守城任务贡献度已经完成了"+percent+"%，你必须在本日结束之前完成剩余贡献度。\n"+NOR);
	}
	return 1;
}
int calcu_song(object me,int reward)
{
	mixed* timeinfos = localtime(time());
	int hour,minute,second,total_sec,next_due;
	float percent;
	string day=sprintf("%d-%d-%d", timeinfos[5], timeinfos[4]+1,timeinfos[3]);
	if (me->query("presong/finish_day")==day)
	{
		tell_object(me,HIR+"你已经完成了本日的报效国家任务。\n"+NOR);
		return -1;
	}
	hour= timeinfos[LT_HOUR];
    minute = timeinfos[LT_MIN];
	second = timeinfos[LT_SEC];
	total_sec=second+minute*60+hour*3600;
	next_due=172800+(time()-total_sec);
	if (me->query("presong/today")!=day)
	{
		me->set("presong/today_tasks",0);
		me->set("presong/today",day);
		if (me->query("presong/next_due")&&time()>me->query("presong/next_due"))
		{
			me->set("presong/total_check",0);
			tell_object(me,HIR+"因为你没有在连续两天都完成报效国家任务，所以你的完成总次数被清零。\n"+NOR);
		}
	}
	me->add("presong/today_tasks",reward);
	if (me->query("presong/today_tasks")>=SONG_ENTRY)
	{
		me->set("presong/today_tasks",0);
		me->add("presong/total_check",1);
		if (me->query("presong/total_check")>=7&&!me->query("song/pro"))
		{
			tell_object(me,"你已经连续七日完成了报效国家任务，获得了郭靖的推荐得以进入大宋官场。\n");
			tell_object(me,"你可以从临安府和宁门pass north，进入大宋官衙所在，审官院负责低级文官的审定，三班院负责低级武官的审定。\n");
			tell_object(me,"两处官衙都在尚书省之内。\n");
			return 1;
		}
		me->set("presong/finish_day",day);
		me->set("presong/next_due",next_due);
		tell_object(me,HIR+"你已经完成了本日的报效国家任务，你必须在"+ctime(next_due)+"之前再胜利完成三轮保卫任务。\n"+NOR);
	}
	else
	{
		percent=to_float(me->query("presong/today_tasks"))/to_float(SONG_ENTRY)*100;
		tell_object(me,HIR+"你本日的报效国家任务贡献度已经完成了"+percent+"%，你必须在本日结束之前完成剩余贡献度。\n"+NOR);
	}
	return 1;
}
string ask_for_baowei()
{
	object xytask, me=this_player();
    object ob=this_object();
	string *ulist;
	xytask=load_object("/adm/daemons/xytaskd.c");

	if (xytask->query("victory"))
		return "这次保卫已经成功了，"+ RANK_D->query_respect(me) + "若是有心报国请下次保卫开始时再来。\n";
  
  if (!query("bwlist"))
  	ulist=({});
  else
  	ulist=query("bwlist");
  
  if ( me->query("combat_exp")/10000>=10000 &&
  	   member_array(me->query("id"), ulist)<0 )
  	ulist+=({me->query("id")});
  
  if ( !query("bwtime") )
  	set("bwtime", time());
  else if ( (xytask->query("times")==1 && time()-query("bwtime")>180) ||
  	        (xytask->query("times")!=1 && time()-query("bwtime")>60) )
  	return "这次保卫报名已经截止了！\n";
 
  set("bwlist", ulist);
  me->delete_temp("xytaskd");
  me->set_temp("xytaskd/startid", query("taskid") );
 // me->set_temp("pfm_skip",1);
  if (sizeof(ulist)<5)
  {
      ob->delete_temp("btasked");
  }
  if ( sizeof(ulist)>=5&&!ob->query_temp("btasked"))//chat一次就够了，chat十几次几十次，刷屏实在太厉害。Zine
  {
      CHANNEL_D->do_channel(this_object(), "bd", "今天襄阳有幸得到诸位高手相助，乃我大宋之福。");
      ob->set_temp("btasked",1);
  }
  return "希望" + RANK_D->query_respect(me) + "能为保卫襄阳出一份力。\n";
}

string ask_for_gongshi()
{
	object xytask,tieqiao;
	object me;
	me=this_player();
	xytask=load_object("/adm/daemons/xytaskd.c");
	
	if (xytask->query("victory"))
		return "这次保卫已经成功了，"+ RANK_D->query_respect(me) + "若是有心报国请下次保卫开始时再来。";
	if (me->query_temp("xytaskd/tieqiao"))
		return "战争时期资源有限，" + RANK_D->query_respect(me) + "已经领取过铁锹，就不要再领了。";
	message_vision("郭靖令手下军士给$N一把铁锹。\n",me);
	tieqiao = new("/d/xytaskd/obj/tieqiao");
	tieqiao->set("taskid",xytask->query("taskid"));
	me->set_temp("xytaskd/taskid",xytask->query("taskid"));
	tieqiao->move(me);
	me->set_temp("xytaskd/tieqiao",1);
	return "希望" + RANK_D->query_respect(me) + "能好好利用这把铁锹，为保卫襄阳进一份力！";
}

string ask_for_jiangli()
{
	int jiangli,bonus,times,cost_time;
	object me = this_player();
	int jiangli1,jiangli2,jiangli3,jiangli4;
	int killzhang = me->query_temp("xytaskd/qianhuzhang");
	int killbing = me->query_temp("xytaskd/number");
	int killjianxi = me->query_temp("xytaskd/jianxi");
	int gongshi = me->query_temp("xytaskd/gongshi");
	object xytask;
	int bts=join_bts(1), hour=now_hour();
	
	xytask=load_object("/adm/daemons/xytaskd.c");
	bonus=4-xytask->query("occupied");
	times = xytask->query("times");
	//if(!xytaskd->query("victory"))
	if(!query("killed"))
	{
		command("faint");
		CHANNEL_D->do_channel(this_object(), "bd", "zt2 "+me->query("id"), 1);
		tell_object(me,HIW"郭靖怒道：「襄阳现在正在水深火热之中，你跑来领赏，真是岂有此理！」\n"NOR);
		me->delete_temp("xytaskd");
		return "请自重！";
	}
	else if( (!killzhang && !killbing && !killjianxi && !gongshi) || 
		       query("taskid")!=me->query_temp("xytaskd/taskid") ||
		       query("taskid")!=me->query_temp("xytaskd/startid") )
	{
		command("faint");
		CHANNEL_D->do_channel(this_object(), "bd", "zt3 "+me->query("id"), 1);
		return "你寸功未建，还想来领赏？";
	}
	else
	{
		if (me->query("age") < 15)
			return RANK_D->query_respect(me) + "年龄太小，保卫襄阳太危险，以后不要来了。";
		command("admire "+me->query("id"));
		if (!me->query("biography/jobs/baowei"))
		{
			me->set("biography/jobs/baowei",time());//个人传记记录第一次完成任务时间ZINE
		}
		//领取奖励
		CHANNEL_D->do_channel(this_object(), "bd", HIW + me->query("name")+HIW"在保卫襄阳的战斗中杀敌军士卒"+chinese_number(killbing)+"人，杀蒙古奸细"+chinese_number(killjianxi)+"人，杀蒙古千户长"+chinese_number(killzhang)+"人，修筑防御工事"+chinese_number(gongshi) + "次，特此嘉奖!" NOR);
//		jiangli=(me->query_temp("xytaskd/qianhuzhang")*(4000+bonus*500)+me->query_temp("xytaskd/jianxi")*(1000+bonus*500)+me->query_temp("xytaskd/number")*(600+bonus*400))*times*3/5+me->query_temp("xytaskd/gongshi")*random(200+bonus*200);

		jiangli1 = gongshi * (100 + random(bonus*100) + bonus*50); //修建工事
		jiangli2 = killzhang * (4000 + bonus*500); //千户长
		jiangli3 = to_int( pow(killjianxi*1.0, 0.7) * 2 ) * (1000 + bonus*500); //奸细
		//以16为基数，16之前的提高奖励，16之后的降低降低
		//既然用了pow，0.5和0.7性能上是一样的吧，大概12个奸细奖励和以前一样
		jiangli4 = to_int( pow(killbing*1.0, 0.7) * 3 ) * (600 + bonus*400); //士卒
		//大概34个和以前奖励一样
//                jiangli=jiangli1+to_int((jiangli2+jiangli3+jiangli4)*(times*11/10-3/10)*3/5)
		jiangli = jiangli1 + jiangli2 + jiangli3 + jiangli4*times*3/5;
		//按照advent改之前的算法只有士卒是和第几轮有关的，不知是不是疏忽，如果有特别的考虑就改回去吧
    //100m以上参与人超过5个人以上难度增加，奖励也增加50%
    if ( bts>=5 )
    	jiangli = jiangli * (FACTOR_XY+0.2);
    else
		  jiangli = jiangli * FACTOR_XY;

		//在开头#define一个FACTOR_XY，以后观察奖励多少方便随时调整
    jiangli = jiangli * SPEWEEK_D->query_baowei_bonus()/100;//特殊周效果
		if (me->query("presong/start"))
		{
			if (calcu_song(me,jiangli)==1)
			{
				me->delete_temp("xytaskd");
				return "因为你选择的报效国家，所以在此期间，只记录功劳，并无实际奖励。\n";
			}
		}
		if (me->query("chaoting/prewang/start"))
		{
			if (calcu_ct(me,jiangli)==1)
			{
				me->delete_temp("xytaskd");
				return "因为你选择的帮助守城，所以在此期间，只记录功劳，并无实际奖励。\n";
			}
		}
		if( me->query("combat_exp") > 200000000 && bts < 5 )
		{
			CHANNEL_D->do_channel(this_object(), "sys", sprintf("%s（exp>100M）在保卫襄阳中获得潜能：%d。", me->name(), jiangli/5));
			tell_object(me,HIR"你共得到"+chinese_number(jiangli/5)+"点潜能的奖励！感谢你对大宋长期以来的贡献！\n"NOR);
			me->add("potential", jiangli/5);
			me->add("pot/xytask", jiangli/5);
			jiangli = killzhang*300 + killbing*10 + killjianxi*30;
			if(jiangli)
			{
				jiangli = REWARD_D->add_rep(me,jiangli);
//				me->add("repute", jiangli);
				tell_object(me,HIR"由于你在战斗中的突出表现，你的江湖声望上升了"+chinese_number(jiangli)+"点！\n"NOR);
			}
			me->delete_temp("xytaskd");
			return "谢谢你为保护襄阳出了一分力！";
		}
		
		if (me->query("age") > 14)
		{
			//潜能奖励以经验奖励为标准，所以只把经验奖励纳入reward_d管理，如果以后标准变化，可能需要加入潜能奖励的reward_d管理
      //超过100m以后奖励随着经验每一M降低1/500，直到降低到0
			if ( me->query("combat_exp")/1000000>100 && me->query("combat_exp")/1000000<500 )
				jiangli=jiangli*(700-me->query("combat_exp")/1000000)/600;
			else if ( me->query("combat_exp")/1000000>=500 )
        jiangli=jiangli/3;
			jiangli = REWARD_D->add_exp(me,jiangli,"xiangyang");
			me->add("exp/xytask",jiangli);
			me->add("potential",jiangli/12);
			me->add("pot/xytask",jiangli/12);
			CHANNEL_D->do_channel(this_object(), "sys",sprintf("%s在保卫襄阳中获得经验：%d、潜能：%d。", me->name(),jiangli,jiangli/12));
			tell_object(me,HIR"你共得到"+chinese_number(jiangli)+"点经验，和"+chinese_number(jiangli/12)+"点潜能的奖励!\n"NOR);

			//加入任务统计系统 by icer
			cost_time = time()-XYTASK_D->query("begin_time");
			COMBAT_D->add("task_stat/baowei/complete_times",1);
			COMBAT_D->add("task_stat/baowei/cost_time",cost_time);
			COMBAT_D->add("task_stat/baowei/exp",jiangli);
			COMBAT_D->add("task_stat/baowei/pot",jiangli/12);
			COMBAT_D->add("task_stat/baowei/expratio",to_float(jiangli)/me->query("combat_exp"));

			jiangli = me->query_temp("xytaskd/qianhuzhang") * 100   //千户长一个100声望
				+ me->query_temp("xytaskd/number") * 3          //普通兵一个3点声望
				+ me->query_temp("xytaskd/jianxi") * 10;        //奸细一个10点声望(原来30点）
			if(jiangli)
			{
			jiangli = REWARD_D->add_rep(me,jiangli);
//			me->add("repute",jiangli);
			tell_object(me,HIR"由于你在战斗中的突出表现，你的江湖声望上升了"+chinese_number(jiangli)+"点!\n"NOR);
	
			COMBAT_D->add("task_stat/baowei/repute",jiangli);
	
			}
		}
		
		me->delete_temp("xytaskd");
		/*if (me->query_temp("pfm_skip"))
		{
			me->delete_temp("pfm_skip");
		}*/
		return "谢谢你为保护襄阳出了一分力！";
	}
}

int accept_object(object me, object ob)
{
	object xytask,obj;
	xytask=load_object("/adm/daemons/xytaskd.c");
	if(!xytask->query("begin"))
	{
		command("haha");
		command("hoho "+me->query("id"));
		if(!ob->is_character()) 
		{
			remove_call_out("des");
			call_out("des",1,ob);
		}
		else
		{
			command("faint");
			remove_call_out("return_ob");
			call_out("return_ob",1,me,ob);                  
		}
		return 1;
	}
	if(ob->query("id")=="yingxiong tie")
	{
		command("haha");
		command("say 你收到我的信了？这里是一把钢刀和一件铁甲，英雄拿去用吧！");
		command("say 希望能够对你杀敌有所帮助！");
		message_vision("郭靖给$N一把钢刀和一件铁甲。\n",me);
		obj=new("/clone/armor/tiejia.c");
		obj->set_weight(0);
		obj->move(me);
		obj=new("/clone/weapon/gangdao.c");
		obj->set_weight(0);
		obj->move(me);
		if(!ob->is_character()) 
		{
			remove_call_out("des");
			call_out("des",1,ob);
		}
		else
		{
			command("faint");
			remove_call_out("return_ob");
			call_out("return_ob",1,me,ob);
		}
		return 1;
	}
	if(!ob->is_character()) 
	{
		remove_call_out("des");
		call_out("des",1,ob);
	}
	else
	{
		command("faint");
		remove_call_out("return_ob");
		call_out("return_ob",1,me,ob);
	}

	return 1;
}
int des(object obj)
{
	if(obj)
		destruct(obj);
	return 1;
}
int return_ob(object me,object ob)
{
	command("faint "+me->query("id"));
	command("give "+ob->query("id")+" to "+me->query("id"));
	return 1;
}
