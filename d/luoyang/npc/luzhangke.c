//鹿杖客
//by picewolf 2009-5-8
#include <ansi.h>
inherit NPC;
string RandomDigtal();
int ask_enter();
int do_answer(string arg);
int ask_test();
int ask_tongji();
void task_stat();
void create()
{
        set_name("鹿杖客", ({ "luzhang ke", "luzhang","ke" }));
		set("title",HIB"玄冥二老"NOR);
        set("long","他大约60多岁年纪，与鹤笔翁共称”玄冥二老“，凭借玄冥神掌纵横江湖。\n");
        set("shen_type", 1);
        set("gender", "男性");
        set("age", 66);
		set("combat_exp", 600000000);
		 set("str", 60);
        set("int", 50);
        set("con", 50);
        set("dex", 50);

        set("max_qi", 28000);
        set("max_jing",28000);
        set("neili", 28000);
        set("max_neili", 28000);
        set("jiali", 350);
        
        set("score", 500000);
		set_skill("force", 1500);
        set_skill("jiuyin-zhengong", 1500);
        set_skill("xuanming-zhangfa", 1500);
        set_skill("dodge", 1500);
        set_skill("jiuyin-shenfa", 1500);
        set_skill("strike", 1500);  
        set_skill("parry",1500);
        

        map_skill("force","jiuyin-zhengong");
        map_skill("dodge","jiuyin-shenfa");
        map_skill("strike","xuanming-zhangfa");
        map_skill("parry","xuanming-zhangfa");
		set_temp("apply/armor", 500);
		set_temp("apply/damage", 400);

	 
        prepare_skill("strike", "xuanming-zhangfa");

		set("inquiry",([
			"赵敏":"那是我们郡主，她现在在绿柳山庄。你问这做什么？",
			"赵明":"那是我们小王爷。",
			"番邦武士":"这些不成材的武士都是郡主训练的，略晓中原武功，还请阁下手下留情。",
			"闯塔":"阁下要想闯塔，只需告诉我即可。只要入塔，比武就开始了，所以还请准备妥
当之后再行进入。每过一层阁下便可用“jiangli”查看王府送的厚礼。闯的层数越多
，礼物也就越多，如果失败身亡，王府也为您准备了上好的柳州棺木。",
			"玄冥神掌":"哈哈，这可是我们的看家本领，若是阁下能闯的过塔，老夫指点一二，也未尝不可。",
			"阴谋":"阴谋？哪里有什么阴谋，阁下切不可轻信谣言，郡主发这个英雄帖，只不过想结交中原豪杰而已。",
			"进塔" : (: ask_enter :),
					]));

        setup();
}

void init()
{
        //add_action("do_answer", "answer");
		add_action("do_tongji", "tongji");
}

int ask_enter()
{
	object me=this_player();
	object *allob;
	object suicong;
	allob=all_inventory(me);

	
	if (!wizardp(me) && me->query("wananta/start") && time()-me->query("wananta/start")<=900)
	{
		write("鹿杖客将你拦住，道：阁下刚刚来过，还请稍后！\n");
		return 1;
	}
  if (me->is_busy())
	{
		tell_object(me,"鹿杖客将你拦住，道:你先忙完自己的事情再说吧。\n");
		return 1;
	}  	

	if (me->query("combat_exp")<1000000)
	{
		tell_object(me,"鹿杖客将你拦住，道:此塔危机重重，这位兄弟还是回去再练练吧。\n");
		return 1;
	}

	for (int i=0;i<sizeof(allob);i++ )
	{
		if (userp(allob[i]))
		{
			write("鹿杖客说道：阁下只能独自进去，这还背了一个人。。似乎不大妥当吧！\n");
			return 1;
		}
	}
	if (me->query("antirobot/deactivity") > 2) message("vision",HIR"鹿杖客瞪圆了眼睛对你说到：“又他奶奶的是你！我看你是机器人吧。”\n"NOR,me);
	/*me->set_temp("wanansi/randomcode",RandomDigtal());
	printf("%s","/d/luoyang/npc/display.c"->Display((string)this_player()->query_temp("wanansi/randomcode")));
	printf("%s","\n");  
	command("say 请在30秒内回答(answer/huifu)出口令的内容。");
	command("say 如果没看清，请ask ke about 进塔 再问一次。");*/
	
	write("鹿杖客微微颔首道：“请壮士入塔！”\n");
	me->set("wananta/start",time()); 
	me->move("/d/wananta/wananta1");
	if(objectp(suicong = present(me->query("id") + " suicong")))
	{
		tell_object(me,"你的随从弟子毫不犹豫的跟上了你了。\n");
		suicong->move("/d/wananta/wananta1");
	}	
	return 1;
	
}



string RandomDigtal()
{
   string *ABC=({"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"});
   string *DIG=({"0","1","2","3","4","5","6","7","8","9"});
   string MyCode;
   MyCode=ABC[random(sizeof(ABC))]+ABC[random(sizeof(ABC))]+DIG[random(sizeof(DIG))]+DIG[random(sizeof(DIG))];
   return MyCode;
}

int do_answer(string arg)
{
	object me=this_player();
	object *allob;
	allob=all_inventory(me);
	for (int i=0;i<sizeof(allob);i++ )
	{
		if (userp(allob[i]))
		{
			write("鹿杖客说道：“背着人肉炸弹想做什么，恐怖分子？！” \n");
			return 1;
		}
	}
	if ((int)me->query_temp("wanansi/randomcode")==0)
       return 0;
	message("vision",me->name()+"回答道：“是"HIR+arg+NOR"么?”\n",environment(me));
    if (arg==(string)me->query_temp("wanansi/randomcode") )
    	{
			write("鹿杖客微微颔首道：“口令无误，请壮士入塔！”\n");
			me->delete_temp("wanansi/randomcode");
			me->set("wananta/start",time()); 
			me->move("/d/wananta/wananta1");
			return 1;
		 }
    else
       write("鹿杖客摇摇头说道：“不对！”\n"); 
    return 1;
}

int do_tongji()
{
	if (wizardp(this_player()))
	{
		task_stat();
		return 1;
	}
	return 0;
	
}
void task_stat()
{
	int levels = 7;
	string result;
	int i;
	
	result = "自上次更新combatd之后，万安塔任务数据统计如下：\n" ;
	for (i=1;i<=levels;i++)
	{
		result += HIW+"第" + chinese_number(i) + "层：\n" +NOR;
		result += "进入：" + COMBAT_D->query("task_stat/wat/"+i+"/times") + "人次\n";
		result += "死亡：" + COMBAT_D->query("task_stat/wat/"+i+"/penalty/times")+"人次\n";
		result += "惩罚经验：" + COMBAT_D->query("task_stat/wat/"+i+"/penalty/exp")+"，潜能：" + COMBAT_D->query("task_stat/wat/"+i+"/penalty/potential")+"，声望：" + COMBAT_D->query("task_stat/wat/"+i+"/penalty/reputy")+"\n";
		//以下统计尚未实现
		result += "奖励经验：" + COMBAT_D->query("task_stat/wat/"+i+"/reward/exp")+"，潜能：" + COMBAT_D->query("task_stat/wat/"+i+"/reward/potential")+"，声望：" + COMBAT_D->query("task_stat/wat/"+i+"/reward/reputy")+"\n";
	}
	write(result);
	return;
}
