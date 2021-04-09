// jiaoxi.c
#include <title.h>
inherit NPC;
inherit F_DEALER;
//#include "/d/yingtianfu/neicheng/npc/promote.h"
#include <ansi.h>
int ask_job();

void create()
{
        set_name("老夫子", ({ "lao fuzi", "lao", "fuzi" }));
        set("long",
"一个唯利是图的苏州老教习，肚子里有墨水，可你还要有钱。\n");
        set("gender", "男性");
        set("age", 65);
        set_skill("literate", 200);

        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_skill("parry", 20);
        set_temp("apply/attack", 20);
        set_temp("apply/defense", 20);
        set_temp("apply/damage", 20);

        set("combat_exp", 40000);
        set("shen_type", 1);
        set("inquiry", ([
            "书"   : "唉!书到用时方恨少。",
            "借书" : "借？你不还我到哪里找你？哼!",
			/*"三太子" : (: ask_job :),
            "慈焕" : (: ask_job :),
			"永王" : (: ask_job :),
            "崇祯" : "先帝爷雄才大略，可惜被李自成那狗贼所害。",*/
        ]));
        setup();

}

void init()
{
	add_action("do_answer", ({ "answer", "da"}));
	add_action("do_xuan", ({ "xuan", "choose"}));
}

int quest(object me)
{
	object ob=this_object();
	object target; 
    object loc;
	object xinwu; 
	int i;
	command("secret "+ me->query("id"));
    if(!userp(me))
    return 0;
  	target=new(__DIR__"target");
	target->set("zhusan",me->query("id"));
//过滤非法任务地点和不明区域 by segate@pkuxkx
        while (!objectp(loc) || 
               !loc->isroom()||
               TASK_D->place_belong(loc)=="不明区域"||
               base_name(loc) == "/adm/daemons/taskd")
        {
          loc = TASK_D->random_place();
        }
//   	loc = TASK_D->random_place();
   	target->move(loc);
    if (!target)    
    {
		tell_object(me,"老夫子沉吟片刻道：时机不对，你还是等会再来帮我们吧。\n");
        return 1;
    }
	else
	{
	tell_object(me,"老夫子说道：“我们的人在"+TASK_D->place_belong(loc)+"收集情报，他的名字叫"
				+target->query("name")+"("+target->query("id")+")你拿我的信物去，他自然就会明白。\n");
	xinwu=new(__DIR__"obj/xinwu");
	xinwu->set("owner",me->query("id"));
	tell_object(me,"老夫子把一件信物交给了你。\n");
	xinwu->move(me);
	ob->add_busy(1);
	return 1;
	}
}

int do_answer(string arg)
{
	object me=this_player();
	object ob=this_object();
	if (me->query_temp("zhusan/answer"))
	{
		if (!arg||(arg!="虽短必切" && arg!="必切" ))
		{
			return notify_fail("老夫子笑道：一下就露馅了吧？想来唬我？没门！\n");
		}
		
		else
		{   
			command("touch "+ me->query("id"));
			command("say 原来你真是殿下派来的高手啊。\n");
			me->delete_temp("zhusan/answer");
			me->set_temp("zhusan/quest");
			me->set("zhusantime",time());
			call_out("quest",2,me);
			return 1; 
		}
	}
	else
	{return 0;}
}


int ask_job()
{
	object ob=this_object();
	object me=this_player();
	if (me->is_busy() || me->is_fighting())
	{
		return notify_fail("你正忙着呢。\n");
	}
	if (ob->is_busy() || ob->is_fighting())
	{
		return notify_fail(ob->query("name")+"正忙着呢，你等会再问吧。\n");
	}
	if (time()-(me->query("zhusantime"))<1)//cd
	{
		return notify_fail(ob->query("name")+"不耐烦的挥挥手，看来你上次任务没完成给弄烦了。\n");
	}
	if (me->query("zhusan"))
	{
		command("whisper "+ me->query("id")+ " 你真是永王殿下派来的？\n" );
		command("xuanyao "+ me->query("id"));
		tell_object(me,"请用answer回答老夫子的暗号。\n");
		me->set_temp("zhusan/answer",1);
		ob->set("askid",me->query("id"));
		return 1;
	}
	else
	{
		command("say 都是前朝的年号了，你还提他作甚？\n" );
		return 1;
	}
}

int recognize_apprentice(object ob)
{
        if (!(int)ob->query_temp("mark/朱2"))
                return 0;
        ob->add_temp("mark/朱2", -1);
        return 1;
}

int destgg(object ob)
{
    if (ob)
    {
        destruct(ob);
    }
    return 1;
}

int accept_object(object who, object ob)
{
	    string* color=({HIR,RED,HIY,YEL,HIB,BLU,HIG,GRN,HIC,CYN,MAG,HIM,HIW,WHT});
	    string color1=color[random(sizeof(color))];
        object me = this_player();
		if (!(int)who->query_temp("mark/朱2")) who->set_temp("mark/朱2", 0);
        if (ob->query("money_id") && ob->value() >= 500)
        {
                message_vision("老夫子同意指点$N一些读书写字的问题。\n", who);
                who->add_temp("mark/朱2", ob->value() / 50);
                return 1;
        }
        /*if (ob->query("id")=="guan gao" && ob->query("ming/guangao")==6)
        {
            if (me->query("family/family_name")=="朝廷")
            {
                tell_object(me,"你从哪弄来我大明的诰身？老夫收下了。\n");
                remove_call_out("destgg");
                call_out("destgg",1,ob);
                return 1;
            }
            if (me->query("gender")=="女性")
			{return notify_fail(this_object()->query("name")+"道：我大明从来没有女人为官的先例，姑娘还是把诰身装让给别人吧！\n"NOR);}
			if (me->query("gender")=="无性")
			{return notify_fail(this_object()->query("name")+"道：呵呵，国难当头，我们不需要那么多太监了。\n"NOR);}
            if (!me->query("mingpin"))
		    {
				me->set("ming/pro","文");
				me->set("mingpin",10);
				position_me(me);
				CHANNEL_D->do_channel(this_object(), "chat", sprintf("%s持有吏部特简诰身，获封%s。\n",me->query("name"),me->query("title")));
            }
            else
            {
                return notify_fail(this_object()->query("name")+"道：大人是我大明的官员，就不要拿空白诰身跟老夫开玩笑了。\n");
            }
            remove_call_out("destgg");
            call_out("destgg",1,ob);
            return 1;
        }*/
		if( ob->query("id") != "qing bao")
		return notify_fail(this_object()->query("name")+"怒道，你这笨蛋，居然敢来忽悠我？\n");
		if (ob->query("owner")!= me->query("id"))
		return notify_fail(this_object()->query("name")+"怒道，你这笨蛋，居然拿过期的情报来忽悠我？\n");
		else
		{
			if (!me->query("zhusan"))
			{
				command("say 你从哪偷来的情报？不过嘛，既然你送来了，我也不会拒收的。\n");
				return 1;
			}
			else
			{
				command("jump");
				command("say 阁下真是我大明的骄傲，栋梁中的栋梁。");
				me->set_temp("zhusan/bonus",1);
				call_out("choose",1,me);
				return 1;
			}
		}
       
}


int do_xuan(string arg)
{
	object me=this_player();
	object baoshi = new("/obj/gem/gem");
	int i,wenwu;
	string gem;
	if (!me->query_temp("zhusan/bonus"))
	{
		return 0;
	}
	else
	{
		if (!arg)
		{
			return notify_fail(this_object()->query("name")+"怒道，你这笨蛋，莫非来消遣老夫？快些重选。\n");
		}
		/*if (me->query("ming/in_wait_list")&&(arg!="名"&&arg!="ming"))
		{
			return notify_fail(this_object()->query("name")+"道：不是告诉过你了，作为大明候补官员，你只能选择“名”。\n");
		}
		if (arg=="名"||arg=="ming")
		{
			if (me->query("family/family_name")=="朝廷")
			{return notify_fail(this_object()->query("name")+"道：你既已加入清廷，就再无回头路可走，老夫敬你是一条好汉，让你再选一次。\n"NOR);}
			if (me->query("gender")=="女性")
			{return notify_fail(this_object()->query("name")+"道：我大明从来没有女人为官的先例，姑娘还是选其他奖励吧？\n"NOR);}
			if (me->query("gender")=="无性")
			{return notify_fail(this_object()->query("name")+"道：呵呵，国难当头，我们不需要那么多太监了。\n"NOR);}
			if (me->query("ming_already_ciguan")&&!me->query("mingpin"))
            return notify_fail(this_object()->query("name")+"道：辞职的官员再想回大明可不是我区区一个老夫子能决定得了。\n");
			if (me->query("ming/in_wait_list")) me->delete("ming/in_wait_list");
			if (!me->query("mingpin"))
			{
				wenwu=random(100);
				if (wenwu>49)
				{
					me->set("ming/pro","武");
					me->set("mingpin",8);
				}
				else
				{
					me->set("ming/pro","文");
					me->set("mingpin",10);
				}
				position_me(me);
				me->add("zhusan",-1);
				me->delete_temp("zhusan");
				return 1;
			}	
			else
			{
				me->add("ming/credit",2+random(3));
				tell_object(me,this_object()->query("name")+"道：恭喜"+me->query("name")+"大人，立下此汗马功劳，我已呈报吏部。\n"NOR);
				me->add("zhusan",-1);
				me->delete_temp("zhusan");
				return 1;
			}
				
		}*/
		if (arg=="利"||arg=="li")
		{
			 i = random(20);
			if (i < 3) gem = "yan";
			else if (i < 6) gem = "mu";
			else if (i < 9) gem = "sui";
			else if (i < 12) gem = "jin";
			else if (i < 15) gem = "bing";
			else if (i < 16) gem = "gu";
			else if (i < 17) gem = "yu";
			else if (i < 18) gem = "jiao";
			else gem = "jia";
			/*
			if (me->query("mingpin")&&me->query("mingpin")>4)
			{
                me->add("ming/zhusan_laofuzi_job_li",1);
                if (me->query("ming/zhusan_laofuzi_job_li")>=2)
                {
                    tell_object(me,"老夫子道：大人加入我大明后，实在过于不思进取，光顾着贪财了。不升到四品以上别想从我这再领到一毛钱！\n");
                    return 1;
                }
				tell_object(me,"老夫子道：大人加入我大明后，实在过于不思进取，光顾着贪财了！\n");
                tell_object(me,HIR+BLINK+"如果不升官至四品以上，你今后总共还可以再选“利”作为奖励"+chinese_number(3-(int)me->query("ming/zhusan_laofuzi_job_li"))+"次。\n"+NOR);
				
			}*/
			if (me->query_temp("zhusan/toukui"))
			{
				baoshi->set_level(8335,9999,gem);    //5级及以上
				baoshi->move(me);
				CHANNEL_D->do_channel(this_object(), "jh", me->name(1) +"在帮助朱三太子后，获得"+baoshi->name()+"一枚!");
				CHANNEL_D->do_channel(this_object(), "sys_misc", me->name(1) +"在帮助朱三太子后，获得"+baoshi->name()+"一枚!"); 
				log_file("static/skf",sprintf("%s(%s) 在%s朱三太子任务中获得"+baoshi->name()+"一枚！\n",  
				me->query("name"),me->query("id"),ctime(time()))); 
			}
			else
			{
				baoshi->set_level(9815,9999,gem);    //3级及以上
				baoshi->move(me);
				CHANNEL_D->do_channel(this_object(), "jh", me->name(1) +"在帮助朱三太子后，获得"+baoshi->name()+"一枚!");
				CHANNEL_D->do_channel(this_object(), "sys_misc", me->name(1) +"在帮助朱三太子后，获得"+baoshi->name()+"一枚!"); 
				log_file("static/skf",sprintf("%s(%s) 在%s朱三太子任务中获得"+baoshi->name()+"一枚！\n",  
				me->query("name"),me->query("id"),ctime(time()))); 
			}
			me->add("zhusan",-1);
			me->delete_temp("zhusan");
			return 1;
		}
		if (arg=="实力"||arg=="shili")
		{
			if (me->query_temp("zhusan/toukui"))
			{
				me->add_temp("apply/strength", 10+random(10));
				me->add_temp("apply/dexerity", 10+random(10));
				me->add_temp("apply/intelligence", 5+random(5));

			}
			else
			{
				me->add_temp("apply/strength", 20+random(20));
				me->add_temp("apply/dexerity", 20+random(20));
				me->add_temp("apply/intelligence", 10+random(10));

			}
			tell_object(me,"经此一事，你觉得自己的进攻防御都更胜从前了。\n");
			CHANNEL_D->do_channel(this_object(), "jh", sprintf("%s在朱三太子任务中获得历练，功力大胜往昔。\n",me->query("name")));
			me->add("zhusan",-1);
			me->delete_temp("zhusan");
			return 1;
		}
		else
		{
			return notify_fail(this_object()->query("name")+"怒道，你这笨蛋，莫非来消遣老夫？快些重选。\n");
		}
	}
}


int choose(object me)
{
	/*if (me->query("ming/in_wait_list"))
	{
		tell_object(me,"因为你是大明候补官员，所以只能用xuan命令选择“名”。\n");
		return 1;
	}*/
	tell_object(me,"你可以用xuan命令，选择你希望的奖励“利”或者是“实力”。\n");
	//tell_object(me,HIW"如果选择了“名”，就算正式踏入我大明官场，江湖中一切名声都是过眼云烟了，慎之。\n"NOR);
	return 1;
}