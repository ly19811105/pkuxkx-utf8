// /d/yingtiansouth/dufu/npc/meng.c
// created by Zine@pkuxkx 2014/7/15 for meng job.
inherit NPC;
#include <ansi.h>
#include "/d/yingtiansouth/dufu/npc/Pro.h"
//"深红":HIR,"暗红":RED,"深绿":HIG,"暗绿":GRN,"深黄":HIY,"暗黄":YEL,"深蓝":HIB,"暗蓝":BLU,"深紫":MAG,"暗紫":HIM,"天青":HIC,"靛青":CYN,"深白":HIW,"暗白":WHT
int ask_job();
int ask_finish();
int ask_fail();
int ask_stat();
int test()//测试模式return 1,只提示会奖励多少，并不实际奖励
{
	return 0;
}
void create()
{
	set("Pro_Colors",({"深紫","暗紫"}));
	set("Pro_id","MZJ");
	set_name("孟之经", ({ "meng zhijing", "meng","zhijing" }));
	set("gender", "男性");
	set("title",HIR"大宋 "+HIW+"建康都统制府赞划"+NOR);
	set("age", 25);
	set("str", 10);
	set("dex", 10);
	set("long", "他是建康府诸军督统制孟珙的儿子，孟之经，在父亲入朝时期负责都府的情报工作。\n");
	set("combat_exp", 1200000);
	set("shen_type", 1);
	set("attitude", "peaceful");
	set_skill("unarmed", 150);
	set_skill("force", 200);
	set_skill("dodge", 150);
	set_skill("parry", 200);
	set("QUEST_DROP_GEM",1);
	set("CustomizedAskMode","finish");
	set("qi",2000);
	set("max_qi",2000);
	set("jing",2000);
	set("max_jing",2000);
	set("jingli",5000);
	set("inquiry", ([
        "情报" : (: ask_job :),
        "job" : (: ask_job :),
		"复命" : (: ask_finish :),
        "finish" : (: ask_finish :),
		"失败" : (: ask_fail :),
        "fail" : (: ask_fail :),
		"stat" : (: ask_stat :),
        ]));
	set("no_get",1);
	setup();
	carry_object("/d/song/npc/obj/cloth2.c")->wear();
}

string cal_place(object me,string place)
{string back_str="";
int j,in_cnt;
	string *rdm_place=({"中原", "长江", "清凉峰", "镇江", "杀手帮", "长江北岸", "黄河", "西天目山", "襄阳", "岳阳", "北京", "灵州" ,
		"大轮寺","建康府南城","大理城中","黄河南岸","无量山","西湖梅庄","长安","西湖","黄河北岸","少林寺","提督府","峨嵋","峨眉后山",
		"嘉兴","苏州","岳王墓","昆明","桃源","灵州","灵鹫","天坛","扬州","丐帮","日月神教","全真","畲寨","星宿","紫禁城","姑苏慕容",
		"武当山","少林寺","华山","小山村","苗疆","晋阳","张家口","白驼山","凌霄城","明教","丝绸之路","成都",});
	in_cnt = random(4);
	for (j=0;j<3 ;j++ )
	{
		if (in_cnt==j)
		{
			back_str+=place;
			back_str+=",";
		}
		back_str += rdm_place[random(53)];
		back_str += ",";
	}
	if (in_cnt==3)
	{
		back_str+=place;
		back_str+=",";
	}
	me->set_temp("mzj/pic_place",in_cnt+1);
	me->set("mzj/is_on",1);

return back_str;
}
string cipher_place(object me,string place)
{
	string answer="",pic_answer="",msg="\n",word="中原长江洛阳清凉峰镇江杀手帮泰山江州曲阜南昌麒麟村东天目山岳阳襄阳西天目山北京灵州大石谷星宿康亲王府畲寨全真紫禁城丐帮扬州天坛灵鹫神龙岛日月神教晋阳张家口长江北岸黄河北岸建康府南城黄河南岸白驼山明教岳王墓丝绸之路牙山成都桃源昆明嘉兴苗疆泉州天龙寺平西王府福州峨嵋桃花岛归云庄峨眉后山苏州无量山姑苏慕容华山凌霄城临安府小山村大轮寺西湖大理城中武当山临安府提督府少林寺建康府北城古墓临安府皇宫中原信阳西湖梅庄长安";
	int line_no=0,col_no=0,x1,y1,x2,y2,x3,y3,x4,y4,x5,y5,start_bit,len=strwidth(word),line=6+random(6),col=6+random(6),total;
	total=(line+1)*(col+1);
	x1=1+random(line);
	y1=1+random(col);
	x2=1+random(line);
	y2=1+random(col);
	x3=1+random(line);
	y3=1+random(col);
	x4=1+random(line);
	y4=1+random(col);
	x5=1+random(line);
	y5=1+random(col);
	answer+="第一个字在：第"+chinese_number(x1)+"行，第"+chinese_number(y1)+"列。";
	pic_answer+="["+chinese_number(x1)+"|"+chinese_number(y1)+"]";
	switch (strwidth(place))
	{
		case 4:
		while (x1==x2&&y1==y2)
		{x2=1+random(line);y2=1+random(col);}
		answer+="第二个字在：第"+chinese_number(x2)+"行，第"+chinese_number(y2)+"列。";
		pic_answer+="["+chinese_number(x2)+"|"+chinese_number(y2)+"]";
		break;
		case 6:
		while (x1==x2&&y1==y2)
		{x2=1+random(line);y2=1+random(col);}
		answer+="第二个字在：第"+chinese_number(x2)+"行，第"+chinese_number(y2)+"列。";
		pic_answer+="["+chinese_number(x2)+"|"+chinese_number(y2)+"]";
		while ((x3==x2&&y3==y2)||(x3==x1&&y3==y1))
		{x3=1+random(line);y3=1+random(col);}
		answer+="第三个字在：第"+chinese_number(x3)+"行，第"+chinese_number(y3)+"列。";
		pic_answer+="["+chinese_number(x3)+"|"+chinese_number(y3)+"]";
		break;
		case 8:
		while (x1==x2&&y1==y2)
		{x2=1+random(line);y2=1+random(col);}
		answer+="第二个字在：第"+chinese_number(x2)+"行，第"+chinese_number(y2)+"列。";
		pic_answer+="["+chinese_number(x2)+"|"+chinese_number(y2)+"]";
		while ((x3==x2&&y3==y2)||(x3==x1&&y3==y1))
		{x3=1+random(line);y3=1+random(col);}
		answer+="第三个字在：第"+chinese_number(x3)+"行，第"+chinese_number(y3)+"列。";
		pic_answer+="["+chinese_number(x3)+"|"+chinese_number(y3)+"]";
		while ((x4==x3&&y4==y3)||(x4==x2&&y4==y2)||(x4==x1&&y4==y1))
		{x4=1+random(line);y4=1+random(col);}
		answer+="第四个字在：第"+chinese_number(x4)+"行，第"+chinese_number(y4)+"列。";
		pic_answer+="["+chinese_number(x4)+"|"+chinese_number(y4)+"]";
		break;
		case 10:
		while (x1==x2&&y1==y2)
		{x2=1+random(line);y2=1+random(col);}
		answer+="第二个字在：第"+chinese_number(x2)+"行，第"+chinese_number(y2)+"列。";
		pic_answer+="["+chinese_number(x2)+"|"+chinese_number(y2)+"]";
		while ((x3==x2&&y3==y2)||(x3==x1&&y3==y1))
		{x3=1+random(line);y3=1+random(col);}
		answer+="第三个字在：第"+chinese_number(x3)+"行，第"+chinese_number(y3)+"列。";
		pic_answer+="["+chinese_number(x3)+"|"+chinese_number(y3)+"]";
		while ((x4==x3&&y4==y3)||(x4==x2&&y4==y2)||(x4==x1&&y4==y1))
		{x4=1+random(line);y4=1+random(col);}
		answer+="第四个字在：第"+chinese_number(x4)+"行，第"+chinese_number(y4)+"列。";
		pic_answer+="["+chinese_number(x4)+"|"+chinese_number(y4)+"]";
		while ((x5==x4&&y5==y4)||(x5==x3&&y5==y3)||(x5==x2&&y5==y2)||(x5==x1&&y5==y1))
		{x5=1+random(line);y5=1+random(col);}
		answer+="第五个字在：第"+chinese_number(x5)+"行，第"+chinese_number(y5)+"列。";
		pic_answer+="["+chinese_number(x5)+"|"+chinese_number(y5)+"]";
		break;
	}
	for (int i=0;i<total;i++)
	{
		if (line_no==0&&col_no==0) msg+=sprintf("%-2s","殺");
		else if (line_no==0) msg+=sprintf("%-2s",""+col_no);
		else if (col_no==0) msg+=sprintf("%-2s",""+line_no);
		else if (line_no==x1&&col_no==y1)
		msg+=place[0..1];
		else if (line_no==x2&&col_no==y2)
		msg+=place[2..3];
		else if (strwidth(place)>4&&line_no==x3&&col_no==y3)
		msg+=place[4..5];
		else if (strwidth(place)>6&&line_no==x4&&col_no==y4)
		msg+=place[6..7];
		else if (strwidth(place)>8&&line_no==x5&&col_no==y5)
		msg+=place[8..9];
		else
		{
			start_bit=random(len-2);
			if (start_bit%2==1) start_bit+=1;
			msg+=word[start_bit..start_bit+1];
		}
		col_no+=1;
		if ((i+1)%(col+1)==0&&i!=0)
		{
			msg+="\n";
			line_no+=1;
			col_no=0;
		}
	}
	me->set_temp("mzj/answer",answer);
	me->set_temp("mzj/pic_answer",pic_answer);
	me->set("mzj/is_on",1);
	msg=replace_string(msg,"殺",HBWHT+HIR+"殺"+NOR);
	return msg+"\n\n";
}
int give_job(object me,string wait_place)
{
	object paper,place,npc;
	string info,space="",place_str;
	int blank_line=random(8);
	int rdm;
	if (!me||!living(me)) return 1;
	if (COLOR_D->uncolor(environment(me)->query("short"))!=wait_place)
	{
		write(HIR+"还不去目的地等待，快要失期了！\n"NOR);
		me->set("mzj/is_on",1);
		me->set("mzj/last_task",time());
		command("tell "+me->query("id")+" 叫你到"+wait_place+"等候，你就不听，以为我说着玩的吗？");
		return 1;
	}

	while (!objectp(place) || 
         !place->isroom()||
         TASK_D->place_belong(place)=="不明区域"||
         TASK_D->place_belong(place)=="未知区域"||
         base_name(place) == "/adm/daemons/taskd")
	place=TASK_D->random_place();
	npc=new(__DIR__"target");
	npc->move(place);
	for (int i=0;i<3;i++)
	if (npc&&living(npc))
	npc->random_move();
	if (!npc)	//killer在移动期间晕倒或被房间call die了
	{
		command("tell "+me->query("id")+" 狗汉奸收到消息，这段时间不露面了，你等会再来吧。");
		return 1;
	}
	npc->do_copy(me);
	me->set("mzj/last_task",time());
	me->set_temp("mzj/target",npc);
	me->set_temp("mzj/place",place);
	me->set_temp("mzj/complex",MAP_D->obtain_area_complexity(place->query_location()));
	rdm=random(100);

	if (rdm<75)
	{
		info=cipher_place(me,TASK_D->place_belong(place));
		paper=new(__DIR__"obj/paper");
		paper->set("owner",me);
		if (blank_line>0)
		for (int i=0;i<blank_line;i++)
		space+="\n";
		paper->set("info",space+info);
		paper->move(me);
		tell_object(me,HIG+this_object()->query("name")+"托付都府内常随送给了你一页密码。\n"NOR);
		if (rdm>25&&!wizardp(me))
		command("tell "+me->query("id")+" "+me->query_temp("mzj/answer")+"对照(duizhao)这页，你就知道你要刺杀的人在哪了。");
		else
		{
			me->set_temp("mzj/pic",1);
			tell_object(me,"对照(duizhao)此页，你就知道你要刺杀的人在哪了。\n");
			ANTIROBOT_D->mxpantirobot_ex(me,me->query_temp("mzj/pic_answer"));
	
		}
	}
	else
	{
		me->set_temp("mzj/pic",1);
		tell_object(me,HIG+this_object()->query("name")+"托付都府内常随在你眼前打开了一张纸片。\n你的刺杀目标在下列地址："NOR);
		place_str=cal_place(me,TASK_D->place_belong(place));
		switch(random(2))
		{
			case 0:
		//tell_object(me,HIW+"第"+chinese_number(me->query_temp("mzj/pic_place"))+"个:"+place_str+NOR);
				ANTIROBOT_D->mxpantirobot_ex(me,"第"+chinese_number(me->query_temp("mzj/pic_place"))+"个:"+place_str);
			break;
			case 1:
		//tell_object(me,HIW+place_str+"中第"+chinese_number(me->query_temp("mzj/pic_place"))+"个"NOR);

				ANTIROBOT_D->mxpantirobot_ex(me,place_str+"中第"+chinese_number(me->query_temp("mzj/pic_place"))+"个");
			break;
		}

		tell_object(me,HIG+"随后，都府内常随就将纸片一撮，揉成团，吞了下去。\n"NOR);
	}
	return 1;
}
string gem_drop_msg(object me,object item)
{
	return query("name")+"又从私人储藏里，拿出了一"+item->query("unit")+item->name()+"交给"+me->name()+"，作为完成刺杀任务的额外奖励。\n";
}
void task_stat(object me,int reward,int flag)
{
	int cost_time = time()-me->query_temp("task_stat/mzj/mzj_starttime");
	if (flag==1)
	{
		COMBAT_D->add("task_stat/mzj/exp",reward);
		me->add("exp/mzj",reward);
		COMBAT_D->add("task_stat/mzj/complete_times",1);
		COMBAT_D->add("task_stat/mzj/cost_time",cost_time);
		COMBAT_D->add("task_stat/mzj/expratio",to_float(reward)/me->query("combat_exp"));
	}
	if (flag==2)
	{
		COMBAT_D->add("task_stat/mzj/pot",reward);
		me->add("pot/mzj",reward);
	}
	if (flag==3)
	{
		COMBAT_D->add("task_stat/mzj/repute",reward);
		me->add("rep/mzj",reward);
	}
}
void Give_Reward(object me,int mark)
{
	object ob,material;
	int reward,exp_reward,complex_reward,accu_reward,tmp,score;
	mixed *tm=localtime(time());
    string date=sprintf("%d-%d-%d", tm[5], tm[4]+1, tm[3]);
	if (mark>0)//Reward the user
	{
		exp_reward=me->query("combat_exp")/10000000;
		if (exp_reward> 12) exp_reward=12;
		exp_reward+=6;
		exp_reward*=(300+random(100));
		complex_reward=me->query_temp("mzj/complex")/30;
		if (complex_reward>12) complex_reward=12;
		complex_reward+=6;
		complex_reward*=(300+random(100));
		accu_reward=me->query("newjobs/completed/mzj")/100;
		if (accu_reward>35) accu_reward=35;
		accu_reward*=(150+random(50));
		reward=2000+exp_reward+complex_reward+accu_reward;
		if (me->query_temp("mzj/pic"))
		{
			reward*=2;
			ANTIROBOT_D->same_as_fullme(me);
		}
		//if (time()<1407974399)//新任务单独开一周双倍。
		//reward*=2;

		reward*=MyProBonus(me);
		if (SPECIAL_D("lucky")->active_level(me)>=2 && (me->query("age")>=18))
			reward = reward + reward/10; //有lucky 2的玩家奖励多10%
		if (reward>20000)
		{
			log_file( "user/assassin", sprintf("%s在%d经验时获得%d的奖励基数，地图复杂度为%d。\n", me->query("id"),me->query("combat_exp"),reward,me->query_temp("mzj/complex")) ); 
			if (reward > 40000)
			{
				reward = 40000;
			}
			if (reward > 30000)
			{
				reward *= 55;
				reward >>= 6;
			}
			else
			{
				if (reward > 25000)
				{
				reward *= 29;
				reward >>= 5;
				}
			}
		}
		reward=reward *SPEWEEK_D->query_mzj_bonus()/100;
		if (test())
		{
			write("本次为测试模式，正常模式下，你应获得经验为"+to_int(to_float(reward)*0.4089)+"点，潜能约为一半经验，声望约为十分之一经验。\n");
			write(HIW+"你实际获得了");
			reward=REWARD_D->add_exp(me,10000);
			task_stat(me,reward,1);
			write("经验："+reward+"，");
			reward=REWARD_D->add_pot(me,5000);
			task_stat(me,reward,2);
			write("潜能："+reward+"，");
			reward=REWARD_D->add_rep(me,1000);
			task_stat(me,reward,3);
			write("声望："+reward+"。\n"+NOR);
		}
		else
		{
			write(HBBLU+HIW+"完成了都统制府刺杀任务后，你被奖励了：");
			tmp=REWARD_D->add_exp(me,reward);
			task_stat(me,tmp,1);
			write(chinese_number(tmp)+"点经验，");
			tmp=REWARD_D->add_pot(me,(reward*3/10+random(reward/5)));
			task_stat(me,tmp,2);
			write(chinese_number(tmp)+"点潜能，");
			tmp=REWARD_D->add_rep(me,(reward*4/50+random(reward/50)));
			task_stat(me,tmp,3);
			write(chinese_number(tmp)+"点声望。\n"+NOR);
		}
		if (me->query("family/family_name")=="朝廷")
		{
			if (me->query("mzj/score/date")!=date)
			{
				me->set("mzj/score/date",date);
				me->set("mzj/score/times",0);
			}
			if (me->query("mzj/score/times")<100)
			{	
				me->add("mzj/score/times",1);
				score=2+me->query("mzj/score/times")/10;
				me->add("score",score);
				me->add("mzj/obtain_score",score);
				write(HIR+"你获得了"+chinese_number(score)+"点朝廷贡献度奖励！今日你仍可以有"+chinese_number(100-me->query("mzj/score/times"))+"次机会获得朝廷贡献度奖励。\n"+NOR);
			}
		}
		write(HIW+"你累计共完成了"+me->query("newjobs/completed/mzj")+"次都统制府刺杀任务。\n"+NOR);
		command("great "+me->query("id"));
// 提高任务奖励。by lordstar 20171016
// 复制玩家经验，因为经验影响掉落。
		if (random(2)||wizardp(me))
		{
			ob = this_object();
			if (me->query("combat_exp") > 1200000)
				ob->set("combat_exp", me->query("combat_exp"));
			GEM_D->drop(ob, me);
			ob->set("combat_exp", 1200000);
		}
		
//增加无常造化丹药材掉落。by lordstar 20171102
//  取消掉落 by lordstar 20171106
/*
		if (random(10000)>9970 && !me->query("hsz_auto"))
		{
			material=new("/obj/remedy/drug/wuchang-material");
			if (objectp(material))
			{
				material->set("owner", me->query("id"));
				material->move(me);
				tell_object(me, this_object()->name()+"又送你一份罕见的珍贵药材作为额外馈赠。\n");
			}
		}
  */		
	}
	else//Punish the user
	{
		reward=-1000-random(1000);
		if (test())
		write("本次为测试模式，你放弃任务零损失，正常模式下，你应被扣除经验为"+to_int(to_float(-reward)*0.4089)+"点，潜能约为一半经验，声望约为十分之一经验。\n");
		else
		{
			if (me->query_temp("mzj/pic"))
			{
				reward*=2;
			}
			write(RED+"放弃刺杀任务，你被扣除了：");
			tmp=REWARD_D->add_exp(me,reward);
			me->add("exp/mzj",tmp);
			write(chinese_number(-tmp)+"点经验，");
			tmp=REWARD_D->add_pot(me,(reward*3/10+random(reward/5)));
			me->add("pot/mzj",tmp);
			write(chinese_number(-tmp)+"点潜能，");
			tmp=REWARD_D->add_rep(me,(reward*4/50+random(reward/50)));
			me->add("rep/mzj",tmp);
			write(chinese_number(-tmp)+"点声望。\n"+NOR);
		}
		command("sigh");
		me->delete("mzj/continue_suc");
		me->set("mzj/fail",1);
	}
	me->delete("mzj/is_on");
	me->delete_temp("mzj");
	return;
}
int ask_finish()
{
	object me=this_player();
	message_vision(HIW"$N"+HIW+"平静地看着$n"+HIW+"，上前一步，道：“幸不辱命。”\n"NOR,me,this_object());
	if (!me->query("mzj/is_on"))
	{
		command("say 我没有给过你任务。");
		return 1;
	}
	if (!me->query_temp("mzj/finish"))
	{
		command("say 你的行刺任务并没有完成。");
		return 1;
	}
	me->add("mzj/continue_suc",1);
	if (me->query("mzj/continue_suc")>=5)
	me->delete("mzj/fail");
	if (me->query("mzj/longest_run")<me->query("mzj/continue_suc"))
	me->set("mzj/longest_run",me->query("mzj/continue_suc"));
	me->add("newjobs/completed/mzj",1);
	me->set("jobs/completed/mzj",me->query("newjobs/completed/mzj"));
	Give_Reward(me,1);
	return 1;
}
int ask_fail()
{
	object me=this_player();
	if (!me->query("mzj/is_on"))
	{
		command("say 我没有给过你任务。");
		return 1;
	}
	Give_Reward(me,-1);
	return 1;
}
int ask_stat()
{
	object me=this_player();
	if (!me->query("newjobs/completed/mzj"))
	{
		command("say stat是刺杀任务的一些统计信息，因为你没有完成过任意一次刺杀任务，所以没有stat信息。");
		return 1;
	}
	command("say 你共计完成了"+me->query("newjobs/completed/mzj")+"次都统制府刺杀任务。\n");
	command("say 你目前连续完成了"+me->query("mzj/continue_suc")+"次都统制府刺杀任务，你的最长记录是"+me->query("mzj/longest_run")+"次。\n");
	if (me->query("family/family_name")=="朝廷")
	command("say 通过都统制府刺杀任务，你总共获得门忠"+me->query("mzj/obtain_score")+"点。\n");
	return 1;
}
int cd(object me)
{
	int res=180;
	if (me->query("mzj/fail"))
	res+=90;
	return res;
}
string display_time(int timep)
{
	int min,sec;
	if (timep>=60)
	{
		min=timep/60;
		sec=timep%60;
		if (sec<10)
		{
			if (sec==0)
			return "["+min+":"+"00]";
			else
			return "["+min+":"+"0"+sec+"]";
		}
		else
		return "["+min+":"+sec+"]";
	}
	else
	{
		min=0;
		sec=timep;
		if (sec<10)
		{
			if (sec==0)
			return "[00:00]";
			else
			return "[00:0"+sec+"]";
		}
		else
		return "[00:"+sec+"]";
	}
	
}
int ask_job()
{
	object me=this_player(),where;
	if (me->is_busy()||me->is_fighting()) return notify_fail("你正忙着呢。\n");
	if (me->query("combat_exp")<3000000)
	{
		command("say 以你的武功来完成这个任务，基本上就是送死。");
		return 1;
	}
	if (time()-me->query("mzj/last_task")<cd(me))
	{
		command("say 你上次大发神威之后，汉奸们都大多不敢出头了，过段时间再来吧。"+display_time(cd(me)-(time()-me->query("mzj/last_task"))));
		return 1;
	}
	if (me->query("mzj/is_on")) 
	{
		command("say 我给你的你上一个任务还没完成呢。");
		return 1;
	}
	if (me->query_temp("mzj/pre_approve"))
	{
		command("hmm");
		command("say 叫你去某地等着了吗，你的耳朵呢？");
		return 1;
	}
	while (!objectp(where) || 
         !where->isroom()||
         TASK_D->place_belong(where)=="不明区域"||
         TASK_D->place_belong(where)=="未知区域"||
         base_name(where) == "/adm/daemons/taskd")
	where = TASK_D->random_room("/d/yingtiansouth/");
	me->set_temp("mzj/pre_approve",where->query("short"));
	me->set_temp("task_stat/mzj/mzj_starttime",time());
	if (random(5))
	{
		command("say 这里人多眼杂，你先到"+where->query("short")+"等候，我自会通知你。");
		call_out("give_job",15+random(10),me,COLOR_D->uncolor(where->query("short")));
	}
	else
	{
		command("say 这里人多眼杂，你先到这个地址等候，我自会找人通知你详细事宜。");
	//	tell_object(me,"快去"+where->query("short")+"。\n");
		ANTIROBOT_D->mxpantirobot_ex(me,where->query("short"));
		call_out("give_job",20+random(10),me,COLOR_D->uncolor(where->query("short")));

	}

//	call_out("give_job",15+random(10),me,COLOR_D->uncolor(where->query("short")));
	return 1;
}

void unconcious()
{
    die();
}

void die()
{
    set("eff_qi",this_object()->query("max_qi"));
    set("qi",this_object()->query("max_qi"));
    set("eff_jing",this_object()->query("max_jing"));
    set("jing",this_object()->query("max_jing"));
    return;
}
