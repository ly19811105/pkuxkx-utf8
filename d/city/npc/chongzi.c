// chonger.c
#include <ansi.h>

inherit NPC;

void feilong();
void heal();
int ask_title();
int ask_finish();
int ask_times();
int ask_job();
int ask_fail();
void create()
{
        set_name("虫子", ({ "chong zi", "chong" }));
        set("title", HIW"民工"NOR);
        set("shen_type", 1);
        set("gender", "男性");
        set("age", 35);
        set("str", 80);
        set("int", 84);
        set("con", 80);
        set("dex", 84);
        set("long",
                "关于虫子的传说很多，褒贬不一，很难摸清这个人的底细。\n");
        set_temp("apply/damage", 8000);
		set_temp("apply/armor", 500+random(500));
		set("combat_exp", 1800000000);
        set("attitude", "friendly");
        set("apply/attack", 500+random(500));
	      set("apply/defense", 500+random(500));
		set("jiali",1000);
	      set("max_qi", 1500000);
	      set("max_jing", 1500000);
        set("max_neili", 1000800);
        set("neili", 1000000);
	      set_skill("force", 2600);
				set_skill("dodge", 2600);
				set_skill("parry", 2600);
				set_skill("sword", 2600);
				set_skill("cuff", 2600);
				set_skill("strike", 2600);
				set_skill("huashan-neigong", 2600);
				set_skill("zixia-shengong", 2600);
				set_skill("huashan-shenfa", 2600);
				set_skill("dugu-jiujian", 2600);
				set_skill("hunyuan-zhang", 2600);
				set_skill("poyu-quan", 2600);
				map_skill("force", "huashan-neigong");
				map_skill("dodge", "huashan-shenfa");
				map_skill("parry", "dugu-jiujian");
				map_skill("sword", "dugu-jiujian");
				map_skill("cuff", "poyu-quan");
				map_skill("strike", "hunyuan-zhang");
				prepare_skill("cuff", "poyu-quan");
				prepare_skill("strike", "hunyuan-zhang");
				set("use_weapon1", "sword");
	      set("chat_chance_combat", 100);
	      set("chat_msg_combat", ({
                (: feilong() :),
                (: perform_action, "sword.po" :),
        }) );
        set("chat_chance",100);
        set("chat_msg",({
                (:heal:),
           }));
	      set("no_get",1);
        set("inquiry", ([        ]) );
        set("inquiry", ([
                "name" : "这世上还没几个人知道我是谁呢！\n",
                "here" : "去去去，问别人去。\n",
//                "锻造" : "你怎么会知道我的秘密？罢了罢了，想做兵器可以，要依着我的规矩：\n给我一份锻造秘方，保证依样造出，但是秘方恕不归还，哈哈。\n",
                "任务" : (: ask_job() :),
                "job" : (: ask_job() :),
                "失败" : (: ask_fail() :),
                "fail" : (: ask_fail() :),
                "完成" : (: ask_finish() :),
                "finish" : (: ask_finish() :),
                "次数" : (: ask_times() :),
                "times" : (: ask_times() :),
                "称号" : (: ask_title :),
                "title" : (: ask_title :),
        ]));
        setup();
        carry_object("/clone/misc/cloth")->wear();
	      carry_object("/d/city/obj/changjian")->wield();
}

int accept_fight(object ob)
{
	      command( "grin " + ob->query("id"));
	      if (ob->query("gender") == "男性") {message_vision( "虫子以迅雷不及掩耳盗铃之势一把抓住了$N的小鸡鸡，$N大惊失色，捂着裤裆夺路而逃。\n" , ob);}
        else if (ob->query("gender") == "女性") {message_vision( "虫子以迅雷不及掩耳盗铃之势一把抓住了$N的酥胸，$N大惊失色，红着脸夺路而逃。\n" , ob);}
        else {message_vision( "虫子以迅雷不及掩耳盗铃之势一把抓住了$N的下面，$N大惊失色，扭捏的夺路而逃。\n" , ob);}
        ob->move("/d/city/lichunyuan");
        return 1;
}

void feilong()
{
        object *enemy,target;
        enemy = query_enemy() - ({ 0 });
        target = enemy[random(sizeof(enemy))];
        command("jifa sword huashan-jianfa");
        command("perform sword.feilong " +target->query("id"));
        command("jifa sword dugu-jiujian");
}

void heal()                                             
{                                                       
        object ob=this_player();                        
        if (ob->query("eff_qi") < ob->query("max_qi"))  
        {                                               
                command("exert heal");               
                return;                                 
        }                                               
        if (ob->query("qi") < ob->query("eff_qi"))      
        {                                               
                command("exert recover");               
                return;                                 
        }                                               
        if (ob->query("jing") < ob->query("eff_jing"))  
        {       command("exert regenerate");            
        return;
        }                                         
}        

int ask_job()
{
	object me = this_player();
	int time = time();
	int huyidao, xiaofeng, task, hubiao, joblvl, index, busytime;
	string nextjob = "xiaofeng";
	
	xiaofeng = me->query("jobs/completed/xiaofeng");
	huyidao = me->query("jobs/completed/huyidao");
	task = me->query("jobs/completed/task");
	hubiao = me->query("jobs/completed/hubiao");
	joblvl = xiaofeng;
	index = 2;
	if (huyidao<joblvl)
		{
			nextjob = "huyidao";
			joblvl = huyidao;
			index = 2;
		}
	if (task<joblvl)
		{
			nextjob = "task";
			joblvl = task;
			index = 1;
		}
	if (hubiao<joblvl)
		{
			nextjob = "hubiao";
			joblvl = hubiao;
			index = 2;
		}

	if (me->query("antirobot/deactivity") > 2)
		{
			message_vision(HIR"$N一个飞脚踹的$n连翻三个跟头，指着$n鼻子骂道：“死机器人，我这辈子最讨厌机器人了！看我怎么收拾你！”\n"NOR,this_object(),me);
			return 1;		
		}
	
	if (me->query("combat_exp") < 3000000)
	{
		message_vision("$N对$n嗤之以鼻：“就你这点儿本事，也想学人家做铁匠？”",this_object(),me);
		return 1;
	}
	
	if (me->query("forging") >= 400)
	{
			message_vision("$N对着$n摇了摇头说：“你这张脸我都看腻了，让我们给彼此一些空间和时间重新培养感情吧！”\n", this_object(), me);
			return 1;
	}
	
		if (me->query("forgingjob/onduty") == 1)
	{
		message_vision("$N一脸怒气，对着$n吼道：“你是猪啊，我不是给过你任务了吗？”\n",this_object(),me);
		return 1;
	}
	
	if (me->query_skill("forging",1) >= 100)
	{
			busytime = index*60*10;
		if ((time- me->query("forgingjob/starttime"))<busytime)
		{
			message_vision("$N对着$n摇了摇头说：“怎么又是你！我就想一个人在这儿安静的凿凿墙角，不可以嘛？！”\n", this_object(), me);
			return 1;
		}
	}
	
		me->set("forgingjob/onduty",1);
		me->set("forgingjob/nextjob",nextjob);
		me->set("forgingjob/joblvl",joblvl);
		me->set("forgingjob/index",index);
		me->set("forgingjob/starttime",time);
		if (nextjob == "xiaofeng")
			{
				message_vision("$N对$n说道：“好吧，既然你诚心想学手艺，我可以教给你，不过嘛，有个条件。\n“你去帮我萧峰萧大哥做3件任务，就说是我派你去助他一臂之力的，回来我就教你几招锻造之术。”\n",this_object(),me);
				command("whisper "+me->query("id")+" 你去萧峰那里，想办法获取他的信任，如果干得好，以后有件大事要交给你去做，事成之后，必有重赏！此事你知我知，你若走露半点儿风声，嘿嘿，教你死前看看我的真面目。");
			}
		if (nextjob == "huyidao")
			{
				message_vision("$N对$n说道：“好吧，看在你诚心想学手艺，我就教给你，不过有个条件。\n“你去给胡一刀做3件任务，不要提我的名字，我做好事从来不留名。回来我就教你几招锻造之术。”\n",this_object(),me);
				command("whisper "+me->query("id")+" 你去胡一刀那里和他混熟，等时机成熟了，我有件大事要让你去做，如果成功，你的名字将会无人不知，无人不晓！此事你知我知，你若走露半点儿风声，嘿嘿，教你死前看看我的真面目。");
			}
		if (nextjob == "task")
			{
				message_vision("$N对$n说道：“好吧，我看你诚心想学手艺，倒是可以教给你，不过嘛，有一个条件。\n“你先去做3件task，让我看看你的资质，如果做成，我就教给你几招锻造之术。”\n",this_object(),me);
				command("whisper "+me->query("id")+" 你寻找那些宝物的时候，留意一样东西：一颗没有左耳的首级。找到了立刻带来见我，必有重赏！此事你知我知，你若走露半点儿风声，嘿嘿，让你死前看看我的真面目。");
			}
		if (nextjob == "hubiao")
			{
				message_vision("$N对$n说道：“好吧，看来你是诚心想学手艺，我可以教给你，不过嘛，有个条件。\n“你去帮我家林镇南兄弟做3件任务，就说是我派你去助他一臂之力的，回来我就教你几招锻造之术。”\n",this_object(),me);
				command("whisper "+me->query("id")+" 你去林老弟那里，告诉他一切尽在虫子的掌握之中。以后还会有件大事要交给你去辅佐林老弟一同完成，事成之后，必有你享不尽的荣华富贵！此事你知我知，你若走露半点儿风声，嘿嘿，让你死前看看我的真面目。");
			}
		return 1;
	
}

int ask_fail()
{
	if ((time()- this_player()->query("forgingjob/starttime"))>60*18*this_player()->query("forgingjob/index"))
		{
			message_vision("$N对着$n失望的摇了摇头：“就知道你屁都干不了！”\n",this_object(),this_player());
			this_player()->set("forgingjob/onduty",0);
			return 1;
		}
	else
		{
			command("heihei "+this_player()->query("id"));
			command("whisper "+this_player()->query("id")+" 想退出？没那么容易！");
			return 1;
		}
}

int ask_times()
{
	message_vision("$N从怀里摸出一张破纸片，瞄了两眼，对$n说：“你已经帮我做了"+this_player()->query("forgingjob/completed")+"件事，不错，不错！”\n",this_object(),this_player());
	return 1;
}

int ask_finish()
{
	if (!this_player()->query("forgingjob/onduty"))
		{
			message_vision("$N满脸疑惑的问$n：“我给过你任务？我怎么不知道！”\n",this_object(),this_player());
			return 1;
		}
	if (this_player()->query("jobs/completed/"+this_player()->query("forgingjob/nextjob"))-3<this_player()->query("forgingjob/joblvl"))
		{
			message_vision("$N凶神恶煞的对着$n大吼：“敢骗我！信不信我一指头戳死你！”\n",this_object(),this_player());
			return 1;
		}
	if ((time()- this_player()->query("forgingjob/starttime"))>60*18*this_player()->query("forgingjob/index"))
		{
			message_vision("$N对着$n失望的摇了摇头：“你还知道回来啊，我以为你死了呢！不好意思啊，我的耐性是有限滴。”\n",this_object(),this_player());
			this_player()->set("forgingjob/onduty",0);
			return 1;
		}
	message_vision("$N兴奋地拍了拍$n的肩，说：“好样的，果然没看错你，这就教你我的独门绝学——虫式锻造术！”\n说完把$n拉到墙角，拿起一把破铁锤在空中胡乱挥舞了几下，神秘兮兮的，不知道搞得什么鬼。\n", this_object(), this_player());
	write(HIC"\n你的「锻造之术」进步了！\n"NOR);
	this_player()->set("forgingjob/onduty",0);
	this_player()->add("forgingjob/completed",1);
	if (this_player()->query_skill("forging",1))
	{
		if (this_player()->query_skill("forging",1)<this_player()->query("forging"))
		{
			this_player()->add("forging",this_player()->query_skill("forging",1));
		}
		else
		{
			this_player()->set("forging",this_player()->query_skill("forging",1));
		}
		this_player()->delete_skill("forging");
		tell_object(this_player(),"因为和新锻造系统的锻造技能容易混淆，现在把forging技能转化为记号，你可以正常使用。在becool npc处query_forge，查询点数。\n");
	}
	this_player()->set("forging",this_player()->query("forging")+this_player()->query("forgingjob/index"));
	return 1;
}
void init()
{
	add_action("query_forge","query_forge");
}
int query_forge()
{
	object me=this_player();
	if (!me->query("forging"))
	command("say 你完全不会。\n");
	else
	command("say 你的锻造技能点是"+me->query("forging")+"。\n");
	return 1;
}
int ask_title()
{
	message_vision("$N盯着$n的那张脸气不打一处来：“就你这点儿本事还想要称号？赶紧给我消失！”\n",this_object(),this_player());
	return 1;
}

int accept_object(object me, object ob)
{
        object obj; 
        object smith=this_object();
        if (ob->query("duanzao"))
        {
        	if(smith->query_temp("working"))
        	 {
        	 	if(me->query("id") == smith->query_temp("whogaveme")) {return notify_fail("你不是都给我了么，快去找原料吧。\n");}
        	  else {return notify_fail("没看我这儿正忙着呢么！你过会儿再来吧。\n");}
           }
           else
           	{ 	smith->set_temp("working",1);
            	smith->set_temp("whogaveme",me->query("id"));
            	call_out("workover",60, smith);
            	command("say "+" 这不是传说中战神龙二爷的兵器么？好，好，好。。。\n我需要任意大小的红宝石和黄宝石各一个做原料，限你一分钟内取来，过时不候！\n");
            	call_out("destroy",1,ob);
            	return 1;
            }
        }
        if (ob->query("material")=="ruby" && me->query("id") == smith->query_temp("whogaveme")) 
           {
           if (smith->query_temp("havegems/topaz")){
           	  command("say " + "龙二爷的兵器一共有三件，我只能做其中一个，而且做哪个也得由我说了算，哈哈，在这儿等着我！\n"); 
           	  message_vision( "虫子一阵风似的消失在了角落里，一炷香的功夫，不知从哪儿又钻了出来。\n" , me);
              command("say " + "拿去吧，不送。\n");  
              call_out("destroy",1,ob);
              //smith->delete_temp("working");
              smith->delete_temp("havegems");  
              smith->delete_temp("whogaveme");
              if (random(10)+1>7) {obj = new("/d/gift/becool/longya.c");}
              	else if (random(10)+1>4) {obj = new("/d/gift/becool/longxin.c");}
              		else {obj = new("/d/gift/becool/longlin.c");}
              obj->move(this_player());
              message_vision( "虫子交给$N一" + obj->query("unit")+obj->query("name") + "。\n" , me);
              return 1;
              }
         else {
              command("ok2 " + me->query("id"));
              smith->set_temp("havegems/ruby",1);
              call_out("destroy",1,ob);
              return 1;
              }
           }
           if (ob->query("material")=="topaz" && me->query("id") == smith->query_temp("whogaveme")) 
           {
           if (smith->query_temp("havegems/ruby")){
           	  command("say " + "龙二爷的兵器一共有三件，我只能做其中一个，而且做哪个也得由我说了算，哈哈，在这儿等着我！\n"); 
           	  message_vision( "虫子一阵风似的消失在了角落里，一炷香的功夫，不知从哪儿又钻了出来。\n" , me);
              command("say " + "拿去吧，不送。\n");  
              call_out("destroy",1,ob);
              //smith->delete_temp("working");
              smith->delete_temp("havegems");
              smith->delete_temp("whogaveme");   
              if (random(10)+1>7) {obj = new("/d/gift/becool/longya.c");}
              	else if (random(10)+1>4) {obj = new("/d/gift/becool/longxin.c");}
              		else {obj = new("/d/gift/becool/longlin.c");}
              obj->move(this_player());  
              message_vision( "虫子交给$N一" + obj->query("unit")+obj->query("name") + "。\n" , me);
              return 1;
              }
         else {
              command("ok2 " + me->query("id"));
              smith->set_temp("havegems/topaz",1);
              call_out("destroy",1,ob);
              return 1;
              }
           }
         return notify_fail("什么破玩意儿，还好意思给我！\n");
}

void workover( object me )
{
        me->delete_temp("working");
        me->delete_temp("havegems");
        me->delete_temp("whogaveme"); 
        return;
}

void destroy(object ob)
{
        destruct(ob);
        return;
}