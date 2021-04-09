//hongdou 开心辞典npc                                                                                                
//by kiden@pkuxkx                                                                                                
#include <ansi.h>
inherit NPC;   

string get_question(object me); //随机选择题目
int ask_test();//出题
int do_answer(string arg);//回答
void create()                                                                                          
{  
	set_name("红豆", ({ "hongdou npc","hongdou"}) ); 
	set("gender","女性");   
	set("title",HIY"开心使者"NOR);
	set("age",25);
	set("per",40); 
	set("str",40); 
	set("int",40); 
	set("dex",40); 
	set("con",40); 
	set("kar",40);
	set("attitude", "friendly");
	set("combat_exp", 2000000000);
	set("apply/attack",  300000); 
	set("apply/defense", 30000);
	set("inquiry",([
		"test":(: ask_test :),
			"question":(: ask_test :),
			"开心词典":(: ask_test :),
			"开心辞典":(: ask_test :),
	]));
	setup();
	carry_object("/d/huashan/obj/greenrobe")->wear();
}

void init()
{
	add_action("do_answer", "answer");
	add_action("do_answer", "huida");
}

int ask_test()
{
	object me=this_player();
	string question; //题目
	if (me->query("last_kxcd")>=time())  //如果答错或者不答至少需要间隔1分钟
	{
		tell_object(me,"红豆说道：回答问题太费脑筋了，你还是休息一下吧。\n");
		return 1;
	}
	if (me->query("kxcd/success")>=500)
	{
		tell_object(me,"红豆道：你是此中高手，这些都难不倒你了。\n");
		return 1;
	}
	me->set("last_kxcd",time()+60);
	question=get_question(me);
	tell_object(me,"红豆说道：准备好了吗？我开始出题了哦。\n\n");   
	tell_object(me,HIY+question+"\n"NOR);
	tell_object(me,"\n");
	tell_object(me,"红豆说道：请用answer来回答(例如“answer 3”，表示你认为
		第三个答案是正确的)，你只有30秒钟的时间。\n");
		return 1;
}

string get_question(object me)
{
	int i, j, k;

	string file,str,*quest_list,*quests;
	string *quest;
	int answer;
	file = read_file("/d/wizard/npc/QRdata");
	quest_list =  explode(file,"\n");
	while(1)
	{
		i = random(sizeof(quest_list));
		quests =  explode(quest_list[i],"@@@@");
		if (sizeof(quests) == 2)
		{
			quest = explode(quests[0],"√");				//有些题有敏感字用√分开了，所以需要踢掉那些
			if(sizeof(quest) == 5)
			{
				answer = to_int(replace_string(quests[1]," ",""));
				
				str = quest[0];
				j = random(4) + 1;					//从答案中随机挑一个与现有答案交换
				for( k = 1; k <= 4; k++)	
				{
					str += "√";
					if (k == j)
						 str += quest[answer];
					else if( k == answer)
						str += quest[j];
					else 
						str += quest[k];
				}
				me->set_temp("answer_kxcd",j);
				return str;
			}
		}
	}
	return "题库出错了!";   
}

int do_answer(string arg)
{
	object me=this_player();
	if (!me->query_temp("answer_kxcd")) return 0;
	if (!arg || arg=="") 
	{
		tell_object(me,"红豆疑惑道：你的答案呢？");      
		return 1;        
	}
	if (to_int(arg)!=me->query_temp("answer_kxcd"))
	{
		tell_object(me,"红豆笑道：哈哈，你回答错了，正确的答案是"HIR+
			me->query_temp("answer_kxcd")+NOR"。\n");
		me->delete_temp("kxcd/lianxu");
		me->delete_temp("answer_kxcd");
		return 1;
	}   
	tell_object(me,"红豆说道：恭喜你，答对了！\n");
	if (me->query("last_kxcd")-30<=time())
	{
		tell_object(me,"红豆说道：可惜你答题太慢，没有奖励！\n");
		return 1;
	}
	tell_object(me,"你的经验和潜能提高了！\n");     
	me->add("kxcd/success",1);
	me->add("combat_exp",50+random(50));
	me->add("potential",50+random(20));
	me->add_temp("kxcd/lianxu",1);
	me->delete("last_kxcd");
	me->delete_temp("answer_kxcd");
	if(me->query_temp("kxcd/lianxu")==20)
	{
		tell_object(me,"你已经连续答对20道题了，真是小强啊!\n");
		me->add("potential",2000);
		tell_object(me,"你获得了2000潜能的额外奖励！\n");
	}   
	if(me->query_temp("kxcd/lianxu")==50)
	{
		tell_object(me,"你已经连续答对50道题了，真是大牛啊!\n");
		me->add("potential",10000);
		tell_object(me,"你获得了10000潜能的额外奖励！\n");
		command("chat "+me->query("id")+"连续答对了50道题！");
		command("chat* admire "+me->query("id"));
	}
	return 1;
}
