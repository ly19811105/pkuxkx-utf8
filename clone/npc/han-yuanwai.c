//韩员外任务 Zine
//Modified By Zine 2012/12/20
//合并一些mark，重写了一些程序，减少占用资源。
//fix by yhzzyahoo 2015/4/27 堵住一个降低exp到2k以下的bug
//加一点额外奖励宝石等级by yhzzyahoo@15.7.23
#define FACTOR 10 //系数 Zine e.g. 16既为1.6倍,如需调整2倍奖励，则factor 20.

#include <ansi.h>
inherit NPC;
inherit F_SAVE;
#define HAN "/data/npc/han-yuanwai"
string query_save_file()
{
	return HAN;
}
#include <localtime.h>
#include <gene_map.h>
#include "/d/yingtiansouth/dufu/npc/Pro.h"
//"深红":HIR,"暗红":RED,"深绿":HIG,"暗绿":GRN,"深黄":HIY,"暗黄":YEL,"深蓝":HIB,"暗蓝":BLU,"深紫":MAG,"暗紫":HIM,"天青":HIC,"靛青":CYN,"深白":HIW,"暗白":WHT
int ask_job();
int ask_fail();
int ask_join();
int ask_finish();
int ask_pipa();
int ask_quest();
int ask_map();
int set_inquiry()
{
	set("inquiry", ([
		"name" : "小姓韩，只是一个本分商人。\n",
		"here" : "这里是江州城，城北过江就是信阳了。\n",
		"加入" : (: ask_join :),
		"join" : (: ask_join :),
		"任务" : (: ask_job() :),
		"job" : (: ask_job() :),
		"复仇" : (: ask_job() :),
		"失败" : (: ask_fail() :),
        "fangqi" : (: ask_fail() :),
		"fail" : (: ask_fail() :),
        "完成" : (: ask_finish() :),
		"finish" : (: ask_finish() :),
        "done" : (: ask_finish() :),
        "铁琵琶手" : (: ask_pipa() :),
        "pipa" : (: ask_pipa() :),
        "quest" : (: ask_quest :),
        "江南八镇" : (: ask_quest :),
        "地图版错误" : (: ask_map :),
        "map_error" : (: ask_map :),
		
	]));
}
void create()
{
	set_name("韩员外", ({ "han yuanwai", "yuanwai", "han" }));
	set("long",
		"他就是江州城的韩大善人。\n"
		"他看起来四十多岁，细皮嫩肉，保养得相当不错。\n");
	set("gender", "男性");
	set("age", 40+random(10));
	set("title",HIW"大善人"NOR);
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
    set("uni_target",this_object());
    set("no_get", 1);
    set("is_hanyuanwai",1);
	set_skill("hand", 250);
	set_skill("parry",250);
	set_skill("dodge", 250);
	set_skill("force",250);
	set_skill("literate",250);
	set_skill("pipa-shou",250);
	set_skill("taiyi-you",250);
	set_skill("jiuyin-shengong",250);

	map_skill("parry","pipa-shou");
	map_skill("hand","pipa-shou");
	map_skill("force","jiuyin-shengong");
	map_skill("dodge","taiyi-you");
	
	prepare_skill("hand","pipa-shou");
	set_temp("apply/attack", 20);
	set_temp("apply/defense", 20);


	set_inquiry();

	set("chat_chance",2);
	set("chat_msg",({
		"韩员外自言自语道：「又是一天啊。。」\n",
	}) );
	set("chat_chance_combat",100);
	set("chat_msg_combat", ({
		(: perform_action, "dodge.lingxu" :),
	}));
	
	setup();
	carry_object("/d/murong/npc/obj/shoes1")->wear();
	carry_object("/d/murong/npc/obj/cloth")->wear();
	
    call_out("check_env",1);  	
}
//增加检查该NPC是否被正确放置在某个房间里，如果是无环境的NPC则消除该NPC。
void check_env()
{
	if (!environment(this_object()))
		destruct(this_object());
}

//任务npc不死
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
//家信附加任务
int dest(object ob)
{
	if(ob)
	destruct(ob);
	return 1;
}

int accept_object(object me, object ob)
{
	if (ob->query("owner")!=me->query("id"))
	return notify_fail("这是哪来的？\n");
	if (ob->query("letterback")!=6)
	return notify_fail(query("name")+"别拿乱七八糟东西来忽悠我。\n");
	else
	{
		message_vision("$N接过$n手里的家信，感动的热泪盈眶：这是老婆写给我的信，我，我不会亏待你的！",this_object(),me);
		me->set_temp("extrajob/hyw",1);
		call_out("dest",1,ob);
		return 1;
	}
}

//江南八镇任务相关
int ask_quest()
{
    object me=this_player();
	if (me->query("jiangnanquest/step7"))
	{
		command("say 建康府，将是你江南之行的最后一站。\n");
		command("whisper "+me->query("id")+" 也许神策门外的老汉需要你的帮助。");
		return 1;
	}
	else
	{
		if (me->query("jiangnanquest/step6"))
		{
			command("say 你到城里杂货铺去买个鱼钩送给鄱阳湖畔的钓鱼人,他会指示你下一步的行动。\n");
			me->set_temp("jn/step7a",1);
			return 1;
		}
		else
		{
			command("say 江南八镇就是建康府、镇江、南昌、江州、昆明、成都、岳阳和苗疆。\n");
			return 1;
		}
		return 1;
	}
}
//铁琵琶手任务相关
int ask_pipa()
{
	object me=this_player();
	if (me->query("jiangnan/randomskill2"))
	{
		command("say 我不是把铁琵琶手传给你了吗？你又忘了？什么悟性啊，不适合学武！");
		return 1;
	}
	if (!me->query_temp("pipacanask"))
	{
		command("? " + me->query("id"));
		command("say 铁琵琶手是什么玩意？用来弹琵琶的？");
		return 1;
	}
	else
	{
		command("say 韩家的血海深仇也终于得报，我就把铁琵琶手绝技传授于你。");
		me->set_skill("pipa-shou",10);
		tell_object(me,"你学会了韩家绝技——『铁琵琶手』\n");
		CHANNEL_D->do_channel(this_object(), "jh", HIW + "听说" + me->query("name") +HIW "习得了失传已久的绝技——『铁琵琶手』!", -1);
		me->set("jiangnan/randomskill2",1);
		return 1;
	}
}
//韩员外任务
int ask_join()
{
	object ob=this_object(),me=this_player();
	if (me->query_temp("hanjob"))
	{
		command("say 你怎么如此反复？打退堂鼓了吗？");
		command("zt5 "+me->query("id"));
		return 1;
	}
	if (me->is_busy() || me->is_fighting())
	return notify_fail("你正忙着呢！\n");
    if (ob->is_busy() || ob->is_fighting())
	return notify_fail("韩员外正忙着呢！\n");
    if (me->query_combatgrade() < 30)
	{
		command("say 等你厉害点再来帮我吧，我的仇家可是很棘手的。\n");
		return 1;
	}
	//删除不用的mark。更新版HYW Zine 2012/12/20
	me->delete("hyw_busy");
	me->delete("hyw/gogogo");
	me->delete("hyw/pin");
	me->delete("hyw/current_qiangdao");
	me->delete("hywjob/mayberobot");
	command("say 不错，既然你愿意帮我复仇，我自然来者不拒。\n");
	tell_object(me,"你被允许帮助韩家工作！\n");
	me->set_temp("hanjob",1);
	return 1;
}
int adjust(int value,int para1,int para2,object me,int flag)
{
	int para3=me->query_temp("hyw/difficulty"),para4=me->query_temp("hyw/pic");
	value = value* FACTOR*para2/1000*(10+para1)*para3/4;
	if (para4)
	{
		value=value*8/3;
		me->delete("hyw/jobmayberobot");
		ANTIROBOT_D->same_as_fullme(me);
	}
	if (flag)
	{
		if (value>10000)
        value=10000+(value-10000)/10*8;
		if (value>13000)
		value=13000+(value-13000)/10*6;
		if (value>16000)
		value=16000+(value-16000)/10*5;
	}
	if (!me->query("hyw/jobmayberobot"))
	value=value*41/40;
	if (me->query_temp("extrajob/hyw"))
	{
		me->delete_temp("extrajob/hyw");
		value=value*2;
	}
	value=value* SPEWEEK_D->query_han_bonus()/100;
    return value;
}
int calculate_wait_no_punish(object me,int lv)
{  // 修改等待时间算法，让提示和实际计算的相一致 by lordstar 2017/8/29
	int wait_time;
/*	int base_cd=me->query("newjobs/completed/hyw")/45;
	int exp=me->query("hyw/last_reward_exp")/165;
	wait_time=base_cd+exp*(lv+1)+random(60);
	if (wait_time<120)
	wait_time=120;
	if (wait_time>800)
	wait_time=800;  */
    int extra_cd=(int)me->query("newjobs/completed/hyw")/100;
	if (extra_cd>50)
		extra_cd=50;
	wait_time=60+extra_cd*5;
	return wait_time;
}
int get_minute(int sec)
{
	int min=0;
	if (sec<60)
	return 1;
	else
	{
		while (sec>0)
		{
			sec-=60;
			min+=1;
		}
		return min;
	}
}
int ask_finish()
{
    object me=this_player(),ob=this_object(),letter;
	string *gems=({"gu","yu","jiao","jia"});
	object gem,material;
	object xtshi;
    mixed* timeinfos=localtime(time());
    int folds,exp, pot,rep,gold,cost_time,f=10,mday,h_lv,extra,extra_cd,difficulty=0;
	int id_mf,i;
    gold=2000;
    cost_time=time()-me->query("hyw/lasttime");
    extra=(int)me->query("newjobs/completed/hyw")/50;
    extra_cd=(int)me->query("newjobs/completed/hyw")/100;
	if (extra_cd>50)
	extra_cd=50;
	set("Pro_Colors",({"深蓝","暗蓝"}));
	set("Pro_id","HYW");
    if (extra>100)
    {
        extra=100+(extra-100)/5;
    }
    if ((!me->query_temp("hyw/start")&&!me->query("hyw/gogogo"))||!me->query_temp("hyw/done"))
    {
        command("? " + me->query("id"));
	    return 1;
    }
    if (cost_time>900)
    {
        me->delete_temp("hyw");
        command("say 你去哪儿玩了？到现在才回来。");
        command("angry");
	    return 1;
    }
    else
	{
		if (!me->query("biography/jobs/hyw"))
		me->set("biography/jobs/hyw",time());//个人传记记录第一次完成任务时间ZINE
        mday = timeinfos[LT_MDAY];
		ob->restore();
		if (!ob->query("hyw/past_count")) ob->set("hyw/past_count", 45);
        if (ob->query("hyw/sta_day")!=mday)//日期变更
        {
           if (!ob->query("hyw/level") || (int)ob->query("hyw/level")==0)
            {
                if (ob->query("hyw/finish_count")>=50)
                {
                    ob->set("hyw/level",1);
                }
            }
            else if (ob->query("hyw/finish_count")>ob->query("hyw/past_count")*11/10)
            {
				ob->add("hyw/level",1);
            }
            else
            {
                ob->set("hyw/level",0);
				ob->set("hyw/finish_count", 45);  // 重置为0级同时也重置任务数提示 (1+45*11/10)=50次表示需要做50次提升到1级。by lordstar 2017/8/29
            }
            if (ob->query("hyw/level")>10)
            {
                ob->set("hyw/level",10);
            }
			ob->set("hyw/past_count",ob->query("hyw/finish_count"));
			ob->set("hyw/finish_count",0);
			if (ob->query("hyw/level"))
            {
                CHANNEL_D->do_channel(ob, "rw", "昨日所有江湖大侠共完成复仇任务"+chinese_number(ob->query("hyw/past_count"))
                                      +"次，昨日任务等级"+chinese_number(ob->query("hyw/level"))+"。");
                CHANNEL_D->do_channel(ob, "rw", "今日共须完成复仇任务"+chinese_number(1+ob->query("hyw/past_count")*11/10)+"次才能获得奖励提升。");
            }
			else
			{
                CHANNEL_D->do_channel(ob, "rw", "昨日所有江湖大侠完成的复仇任务总数未达标，任务等级重置为 0 级。");
                CHANNEL_D->do_channel(ob, "rw", "今日共须完成复仇任务"+chinese_number(50)+"次才能获得奖励提升。");
			}
            
        }
        
        ob->add("hyw/finish_count",1);
        ob->set("hyw/sta_day",mday);
		ob->save();
		set_inquiry();
		me->delete_temp("hyw/done");
        me->delete_temp("hyw/name");
        me->delete_temp("hyw/new_map");
		if(me->query("hyw/jobcount") > me->query("newjobs/completed/hyw"))
		{
			me->set("newjobs/completed/hyw",me->query("hyw/jobcount"));			
		}
        me->set("hyw/jobmayberobot",1);
        if (me->query("jobs/completed/huyidao")-me->query("hyw/jobhyd")>0
            ||me->query("jobs/completed/hubiao")-me->query("hyw/jobhb")>0
            ||me->query("jobs/completed/xiaofeng")-me->query("hyw/jobxf")>0
            ||me->query("jobs/completed/task")-me->query("hyw/jobtask")>0
            ||me->query("jobs/completed/husong")-me->query("hyw/jobhs")>0
            ||me->query("newjobs/completed/pyh")-me->query("hyw/jobpyh")>0) //by Zine 反机器人设定
        me->delete("hyw/jobmayberobot",1);
        me->add("hyw/jobcount",1);
        me->add("newjobs/completed/hyw",1);
        if (cost_time<60+random(11)+extra_cd*5) //做得太快，说明简单，拿6-7成奖励 Zine
        {
            f=7-random(2);
            command("say 这么快就完成了？看来这活儿对你只需要"+chinese_number(f)+"成力啊，好吧，我也马马虎虎给你"+chinese_number(f)+"成的奖励好了。");
        }
		exp = (me->query("kar")/2 + 33) * (24 + random(8))*11/5;
		if (me->query_temp("hyw/factor")>5)
		exp=exp+me->query("level")*(me->query_temp("hyw/factor")-5)*10;
		pot = exp/3+random(exp/5);
		rep = 20 * random(5) + 150;
        if (me->query_combatgrade()<10)
        {
            exp = exp / 4;
            pot = pot / 4;
// 提高任务奖励。by lordstar 20171016
            gold= 8000;
        }
        else if (me->query_combatgrade()<20)
        {
            exp = exp / 3;
            pot = pot / 3;
            gold= 12000;
        }
        else if (me->query_combatgrade() < 30)
        {
            exp = exp / 2;
            pot = pot / 2;
            gold= 16000;
        }
	    else if (me->query_combatgrade() < 50)
	    {
            exp = exp / 3 * 2;
            pot = pot / 3 * 2;
            gold= 20000;
        }
        exp=exp+extra*(68+random(21));
        pot=pot+extra*(50+random(16));
        rep=rep+extra*10;
		exp=adjust(exp,ob->query("hyw/level"),f,me,1);
		pot=adjust(pot,ob->query("hyw/level"),f,me,0);
		rep=adjust(rep,ob->query("hyw/level"),f,me,0);
		gold= gold+random(gold)*2;
		if (me->query_combatgrade() < 30) gold=gold/3;
		if ((me->query("special_level/lucky")>1)&&me->query("special_skill/sociability")&&me->query("special_skill/lucky") && (me->query("age")>=18))
			exp = exp + exp/10; //有lucky 2的玩家奖励多10%
		folds=MyProBonus(me);
		exp*=folds;
		pot*=folds;
		rep*=folds;
		exp=REWARD_D->add_exp(me,exp);
        pot=REWARD_D->add_pot(me,pot);
        rep=REWARD_D->add_rep(me,rep);
		//STATISTIC_D->task_record("HYW",exp,pot,rep,1);
        me->set("hyw/last_reward_exp",exp);
        me->set("hyw/last_reward_pot",pot);
        me->set("hyw/last_reward_rep",rep);
        me->set("hyw/jobhyd",me->query("jobs/completed/huyidao"));
        me->set("hyw/jobhb",me->query("jobs/completed/hubiao"));
        me->set("hyw/jobxf",me->query("jobs/completed/xiaofeng"));
        me->set("hyw/jobtask",me->query("jobs/completed/task"));
        me->set("hyw/jobhs",me->query("jobs/completed/husong"));
        me->set("hyw/jobpyh",me->query("newjobs/completed/pyh"));
		me->add("balance",gold);
		CHANNEL_D->do_channel(this_object(), "sys_misc",
			sprintf("%s在韩员外复仇任务中获得经验：%d、潜能：%d、声望：%d。", me->name(), exp, pot, rep));
		tell_object(me,HIC "由于你帮助韩员外复仇，被奖励：\n"
			+ chinese_number(exp) + "点实战经验，\n"
			+ chinese_number(pot) + "点潜能，\n"
			+ chinese_number(rep) + "点江湖声望作为答谢。\n" 
            + "你已经完成了"+chinese_number((int)me->query("newjobs/completed/hyw"))+"次复仇任务。\n"NOR);
		if (exp>8000&&!wizardp(me)&&!random(5))
		{
			CHANNEL_D->do_channel(this_object(), "rw",
			sprintf("%s在韩员外复仇任务中获得经验%s点、潜能%s点以及声望%s点。", me->query("name"), chinese_number(exp), chinese_number(pot), chinese_number(rep)));
        }
        COMBAT_D->add("task_stat/han/complete_times",1);
        COMBAT_D->add("task_stat/han/cost_time",cost_time);
        COMBAT_D->add("task_stat/han/exp",exp);
        COMBAT_D->add("task_stat/han/pot",pot);
        COMBAT_D->add("task_stat/han/repute",rep);
        COMBAT_D->add("task_stat/han/expratio",to_float(exp)/me->query("combat_exp"));
		me->add("exp/hyw", exp);
		me->add("pot/hyw", pot);
		me->add("rep/hyw", rep);
        me->delete("hyw/lianxu_fail");
		me->delete("hyw/pic_fail");
		me->delete("hyw/start");
		me->delete_temp("hyw");
	    command("whisper "+me->query("id")+" 我已经把你的辛苦费存到了城内的月记票号你账上！");
		//增加升级提示。by lordstar
 		if (ob->query("hyw/finish_count")<=ob->query("hyw/past_count")*11/10)
		{
			command("say 加油啊！今天我这名单上还有"+ to_chinese(ob->query("hyw/past_count")*11/10-ob->query("hyw/finish_count")+1) +"个仇家等着各位大侠去铲除呢！");
		}
		else 
		{
			command("say 很好！今天的仇家已经铲除得差不多了，剩下就看各位大侠能否多弄些宝石回来了……嘿嘿嘿嘿！");
		}

		if (me->query("jiangnan/randomskill"))
        difficulty=1;
		if (me->query("hyw/jobcount")*me->query("kar")>random(10000)+15000+random(10000)*difficulty && !me->query("jiangnan/randomskill2"))
		{
			me->set_temp("pipacanask",1);
			me->set("hyw/jobcount",0);
			tell_object(me,HIC"你心念一动，也许此时韩员外会告知你铁琵琶手的秘密。\n"NOR);
		}
		if ((int)me->query("newjobs/completed/hyw")%50==49)
		{
			letter=new("/d/changjiang/obj/letter");
			letter->set("owner",me->query("id"));
			letter->move(me);
			tell_object(me,this_object()->name()+"身上掉下了一封信，你赶忙捡了起来。\n");
		}
		if (random(10000)>9950)
		{
			xtshi= new("/obj/m_weapon/item/xuantie");
			xtshi->move(me);
			CHANNEL_D->do_channel(this_object(), "rw", me->query("name")+"完成韩员外任务，获得千年玄铁一枚。");
		}
		 id_mf=(int)me->query_temp("apply/magic");
		 i=3-(int)id_mf/1000;
		 id_mf=(int)id_mf/5;
		 if (i<1)
		 {
			 i=1;
		 }
		if (random(i)==0)
		{
			gem=new("/obj/gem/gem");
// 提高任务奖励。by lordstar 20171016
			id_mf += 6500;
			i = id_mf + random(3000);
			if (i>10000) i=10000;
			gem->set_level(id_mf,i,gems[random(sizeof(gems))]);
			gem->move(me);
			write("\n韩员外给你一颗"+gem->name()+"作为额外奖励！\n");  
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
				tell_object(me, "韩员外又送你一份罕见的珍贵药材作为额外馈赠。\n");
			}
		}
		*/
		return 1;
	}
	
}

string notice_color(int count)
{
	if (count>60)
	return HIG;
	else if (count>30)
	return HIC;
	else if (count>20)
	return HIB;
	else if (count>10)
	return HIW;
	else
	return BLINK+HIR;
}
int countdown(object me,object ob)
{
    int count;
    object room;
    string location,area;
    if (!me)
    {
		if (ob)
		destruct(ob);
        return 0;
    }
    if (!ob)
    {
		tell_object(me,"韩家的仇人竟莫名其妙的失踪了！\n");
		me->set("hyw/lasttime",0);
		me->delete_temp("hyw/start");
		tell_object(me,"虽然没有找到他，想必韩员外不会责怪你，再去看看他还有什么事吧。\n");
		return 1;
    }
	area=me->query_temp("hyw/task7_area");
	location=me->query_temp("hyw/task7_loc");
	room=environment(me);
	count=me->query_temp("hyw/countdown");
    if (count>5&&COLOR_D->uncolor(room->query("short"))==location&&TASK_D->place_belong(room)==area)
    {
		tell_object(me,"你过早地来到的狙击地点，打草惊蛇，"+ob->name()+"决定改换路线，远走高飞了。\n");
		if (ob)
		destruct(ob);
		return 1;
    }
    if (count<=1&&(COLOR_D->uncolor(room->query("short"))!=location||TASK_D->place_belong(room)!=area))
    {
		tell_object(me,"你磨磨蹭蹭，到现在还没到达狙击地点，"+ob->name()+"已经逃之夭夭了。\n");
		if (ob)
		destruct(ob);
		return 1;
    }
    if (count<=3&&count>=1&&COLOR_D->uncolor(room->query("short"))==location&&TASK_D->place_belong(room)==area)
    {
		if (ob&&!ob->query("appear"))
		{
			ob->set("appear",1);
			ob->move(room);
			tell_object(me,HIG+ob->name()+"出现了！正是狙杀其的大好时机！\n"+NOR);
			message_vision("$N很错愕的看着$n：你是韩员外派来的？\n",ob,me);
		}
		return 1;
    }
	count-=1;
	me->set_temp("hyw/countdown",count);
	if ((count>60&&me->query_temp("hyw/lastcount")-count>3)
		||(count<=60&&count>30&&me->query_temp("hyw/lastcount")-count>2)
		||(count<=30&&count>20&&me->query_temp("hyw/lastcount")-count>1)
		||(count<=20&&count>10&&me->query_temp("hyw/lastcount")-count>0)
		||count<=10)
	{
		me->set_temp("hyw/lastcount",count);
		tell_object(me,notice_color(count)+"韩家仇人"+ob->name()+"将在"+chinese_number(count)+"秒后经过狙击地点。\n"+NOR);
	}
	call_out("countdown",1,me,ob);
	return 1;
}

int ask_map()
{
	object me = this_player();
	if (!me->query_temp("hyw/new_map"))
	{
		tell_object(me,"你现在的韩员外任务并非新地图类型，无法报错！\n");
		return 1;
	}
	log_file("wiz/han_area",sprintf("%s%s%s",me->query("id")+"报告"+me->query_temp("hyw/new_map"),me->query_temp("hyw/newmapInfo")[1]+"FRONT"+NOR,me->query_temp("hyw/newmapInfo")[2]+"BACK"+NOR+"结束。\t"));
	me->delete_temp("hyw/new_map");
	tell_object(me,"任务无法识别已报错，感谢你的帮助。\n");
	return 1;
}

int intro(object me,object ob)
{
	if (ob->query("task_type")==1)
	tell_object(me,"其人不足为惧，只是真凶的爪牙，你把他就地处决即可。\n");
	if (ob->query("task_type")==2)
	tell_object(me,HIR+"其人与我家有血海深仇，你必须将其擒回，当着我的面诛杀此獠。\n"+NOR);
	if (ob->query("task_type")==3)
	tell_object(me,HIB+"此人是易容高手，须谨防其走脱。\n"+NOR);
	if (ob->query("task_type")==4)
	tell_object(me,HIG+"其人轻功甚是了得，就地诛杀，不可让他逃脱。\n"+NOR);
	if (ob->query("task_type")==5)
	tell_object(me,HIY+"其人奸诈似鬼，疑心甚重，你须变换容貌前去将其刺杀。\n"+NOR);
	return 1;
}
int ask_job()
{
	object me = this_player(),room=environment(this_object()),ob,where,*all;
	string place,location,area,*map,*wheres,say_msg;
	int i,j_num=0,j,f,busytime=180;
    if (!me->query_temp("hanjob"))
    {
        command("say 任务？啥任务啊？庄户人家还能干啥？种地呗！");
        return 1;
    }
	if (base_name(room)!="/d/jiangzhou/dating"&&!wizardp(me))
	{
		command("say 有什么事等我先回了家再说。");
		return 1;
	}
	if (time()-me->query_temp("shilian/start")<1800)
	{
		busytime -= 90;
	}
    all=all_inventory(room);
	for (j=0;j<sizeof(all);j++)
	if (!all[j]->is_character())
	j_num+=1;
	if (j_num>5)
	{
		command("say 你看我这屋子里被人堆的都一些什么乱七八糟的啊，你把这些给我拿开先。");
		return 1;
	}
    if (me->query("hyw/jobmayberobot")&&me->query("combat_exp")>3000000&&me->query("antirobot/deactivity")>1)
    {
		busytime+=180;
		tell_object(me,"这次你的cd时间被加长了，立刻fullme或者做个别的任务可以大幅减少cd时间。\n");
	}
	if (busytime>360)
	busytime=360;
	if ((time()- (int)me->query("hyw/lasttime"))<busytime&&time()>me->query("hyw/lasttime"))
	{
		message_vision("$N对着$n摇了摇头说：「你刚做过任务，先去休息休息吧。」\n", this_object(), me);
		return 1;
	}
	//防止连续故意fail降经验
	if (me->query("hyw/lianxu_fail") > 3)
	if (time()-me->query("hyw/lasttime")<90*(me->query("hyw/lianxu_fail")-4)&&time()>me->query("hyw/lasttime"))
	{
		message_vision("$N对着$n摇了摇头说：「你连续失败次数过多，先去休息休息吧。」\n", this_object(), me);
		return 1;
	}
	if (me->query_temp("hyw/start")||me->query("hyw/start"))
	{
		command("hammer " + me->query("id"));
		command("say 我不是给了你任务了吗？");
		return 1;
	}
	else
	{
		ob=new("/d/jiangzhou/npc/qd"+(1+random(7)));
		if (me->query("hyw/pic_fail"))
		{
			//调试信息
	//		write("调试:进入图片失败模式。\n");
			i=6;
		}
			else
		{
			i=random(8);
		}
		//调试信息
	//	i=5;

		ob->set("task_type",i+1);
		switch(i)
		{
			case 0:
			me->set_temp("hyw/difficulty",3);//普通
			break;
			case 1:
			me->set_temp("hyw/difficulty",5);//打昏杀
			break;
			case 2:
			me->set_temp("hyw/difficulty",8);//易容高手
			break;
			case 3:
			me->set_temp("hyw/difficulty",6);//会逃跑
			break;
			case 4:
			me->set_temp("hyw/difficulty",4);//易容去杀
			break;
			case 5:
			ob->set("is_tasknpc",1);//三个地点
			ob->set("dontseekme",1);
			me->set_temp("hyw/difficulty",10);
			break;
			case 6:
			me->set_temp("hyw/difficulty",6);//读秒狙击
			break;
			case 7:
			ob->set("dontseekme",1);//新地图
			ob->set("is_tasknpc",1);
			me->set_temp("hyw/difficulty",4);
			break;
		}
		if (wizardp(me)&&this_object()->query("wiz"))//测试新类型
		ob->set("task_type",this_object()->query("wiz"));
//过滤非法任务地点和不明区域 by segate@pkuxkx
		while (!objectp(where) || 
				!where->isroom()||
				TASK_D->place_belong(where)=="不明区域"||
				base_name(where) == "/adm/daemons/taskd"||
				(ob->query("task_type")==8&&TASK_D->place_belong(where)=="荆州")||
				where==environment(this_object()))
		where = TASK_D->random_place();
		ob->set("hyw_npc",1);
		ob->set("killer", me->query("id"));
		ob->set("killername",me->name());
		ob->do_copy(me);
		ob->move(where);
		//调试信心
	//	write("目标任务类型："+ob->query("task_type")+"\n");
		me->set_temp("hyw/name",ob->query("name"));
		me->set_temp("hyw/where",TASK_D->place_belong(where));
		me->set_temp("hyw/current_qiangdao",ob);
		me->set("hyw/lasttime", time());
		me->set("hyw/nonpunish_waittime", time()+calculate_wait_no_punish(me,ob->query("hyw/level")));
		me->set_temp("hyw/start",1);
		me->set("hyw/start",1);
		say_msg=RANK_D->query_respect(me) + "能为我韩家出头，复仇指日可待！";
		if (query("hyw/level"))
		say_msg+="["+HIR+"+"+query("hyw/level")+NOR+"]";
		command("say "+say_msg);
		tell_object(me,HBGRN+HIW+"大约需要至少经历"+get_minute(me->query("hyw/nonpunish_waittime")-time())+"分钟后，任务奖励可以全额获取。\n"+NOR);
		if (ob->query("task_type")==8)
		{
			area=TASK_D->place_belong(where);
            message_vision(HIW"$N随意指了指地图上一个方位，说道：韩家仇人"+ob->query("name")+"("+ob->query("id")+")"+"在此出现，$n"+HIW+"去把他宰了！\n" NOR,this_object(),me);
            map=gene_area(area);
            tell_object(me,map[0]);
            tell_object(me,BLINK+HIG+"如遇到无法识别的情况，如整个图片同一颜色，请用ask han about map_error报错。注：此项报错信息为匿名收集。\n"+NOR);
            me->set_temp("hyw/new_map",area);
			me->set_temp("hyw/newmapInfo",map);
            me->set_temp("hyw/where","某处");
            return 1;
        }
        if (ob->query("task_type")==7)
        {
			location=where->query("short");
			area=TASK_D->place_belong(where);
			me->set_temp("hyw/task7_area",area);
			me->set_temp("hyw/task7_loc",COLOR_D->uncolor(location));
			me->set_temp("hyw/countdown",70+random(40));
			me->set_temp("hyw/lastcount",(int)me->query_temp("hyw/countdown"));
            countdown(me,ob);
            where=load_object("/d/city/hideroom");
			ob->move(where);
		//调试信心
		//	write("目标任务类型2："+ob->query("task_type")+"\n");

            if ((random(100)>74 && !ANTIROBOT_D->stopped())||(me->query("hyw/pic_fail")))
            {
		//调试信心
		//	write("进入再次图片模式："+ob->query("task_type")+"\n");

                tell_object(me,HIW"韩员外给你一张字条，并向你解说，此獠将在一分钟后出现。\n");
				ANTIROBOT_D->mxpantirobot_ex(me,ob->query("name")+" "+area+" "+location);
                me->set_temp("hyw/pic",1);
				me->set_temp("hyw/name","某人");
                me->set_temp("hyw/where","某处");
                tell_object(me,MAG+"其人心思缜密，你不到最后五秒不要现身，否则打草惊蛇，悔之晚矣。但也不能迟过他出现的时分，否则其人脱困而去。\n"+NOR);
                return 1;
                
            }
            tell_object(me,HIW"韩员外说道：韩家仇人"+ob->query("name")+"("+ob->query("id")+")"+"据传将在" + area +"的"+location+ "出现，你去将其狙杀！\n" NOR);
            tell_object(me,MAG+"其人心思缜密，你不到最后五秒不要现身，否则打草惊蛇，悔之晚矣。但也不能迟过他出现的时分，否则其人脱困而去。\n"+NOR);
            return 1;
        }
        if (ob->query("task_type")==6)
        {
			location="inherit/char/area_info.c"->random_area_name();
			wheres=({TASK_D->place_belong(where)});
			while (sizeof(wheres)<3)
			{
				if (member_array(location,wheres)==-1)
				{
					wheres+=({location});
				}
				location="inherit/char/area_info.c"->random_area_name();
			}
			ob->move(where);
			switch (random(6))
			{
			case 0:
			location=wheres[0]+"、"+wheres[1]+"、"+wheres[2];
			break;
			case 1:
			location=wheres[0]+"、"+wheres[2]+"、"+wheres[1];
			break;
			case 2:
			location=wheres[1]+"、"+wheres[2]+"、"+wheres[0];
			break;
			case 3:
			location=wheres[1]+"、"+wheres[0]+"、"+wheres[2];
			break;
			case 4:
			location=wheres[2]+"、"+wheres[1]+"、"+wheres[0];
			break;
			case 5:
			location=wheres[2]+"、"+wheres[0]+"、"+wheres[1];
			break;
			}
			tell_object(me,HIW"韩员外说道：韩家仇人"+ob->query("name")+"("+ob->query("id")+")"+"据传在" +location+ "三处出现过，快去找到他帮我杀了他！\n" NOR);;
			me->set_temp("hyw/where","某处");
			tell_object(me,HIC+"其人虚虚实实，狡兔三窟，端的不容易被找到。\n"+NOR);
			return 1;
		}
        if (ob->query("task_type")!=7&&ob->query("task_type")!=8)
        {
			for (i=0;i<3;i++)
			if (ob)  
			ob->random_move();
        }
		if (!ob)
		{
			tell_object(me,HIW"韩员外有思量了一下，沉吟道：“暂时不需要你做什么，一会再来吧。”\n" NOR);
			me->set("hyw/lasttime",0);
			me->delete_temp("hyw/start");
			return 1;
		}
        else
        {
			if ((random(100)>80 && !ANTIROBOT_D->stopped())||(me->query("hyw/pic_fail")))
			{
                message_vision(HIW"$N给$n一张字条。\n"NOR,this_object(),me);
			//调试信息
		//	write("进入再次图片模式："+ob->query("task_type")+"\n");
				ANTIROBOT_D->mxpantirobot_ex(me,ob->query("name")+","+TASK_D->place_belong(where));
                me->set_temp("hyw/pic",1);
				me->set_temp("hyw/name","待定");
				me->set_temp("hyw/where","待定");
				intro(me,ob);
				return 1;
			}
            tell_object(me,HIW"韩员外说道：韩家仇人"+ob->query("name")+"("+ob->query("id")+")"+"据传在『" + TASK_D->place_belong(where) + "』出现过，快去帮我杀了他！\n" NOR);
            me->set_temp("hyw/name",ob->query("name"));
            me->set_temp("hyw/where",TASK_D->place_belong(where));
            intro(me,ob);
			if (ob->query("task_type")==5)
			command("rumor "+ob->query("name")+"已经收到风声，"+me->name()+"被韩员外派出行刺了。");
            return 1;
        }
	}
}

int ask_fail()
{
	object me = this_player(),qiangdao;
	int exp, pot, rep;
	if (me->query_temp("hyw/start")||me->query("hyw/start")) 
	{
		command("disapp");
		if (me->query("hyw/last_reward_exp"))
        {
			exp=(int)me->query("hyw/last_reward_exp");
			pot=(int)me->query("hyw/last_reward_pot");
			rep=(int)me->query("hyw/last_reward_rep");
        }
		else
		{
			exp = (me->query("kar")*2/3 + 50) * (14 + random(6));
			pot = exp / 8;
			rep = 20 * random(2) + 20;
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
			exp = exp * FACTOR/10;
			pot = pot * FACTOR/10;
			if (exp<0)
			exp=1;
			if (pot<0)
			pot=1;
			if (rep<0)
			rep=1;
		}
		exp=exp  * SPEWEEK_D->query_han_bonus()/100;
		pot=pot * SPEWEEK_D->query_han_bonus()/100;    
		rep=rep * SPEWEEK_D->query_han_bonus()/100;
		me->add("combat_exp",-exp);
		if (me->query("combat_exp")<10000)
		{
			me->set("combat_exp",10000);
		}//防止exp被降低到2k以下去
		me->add("exp/hyw", -exp);
		me->add("potential",-pot);
		me->add("pot/hyw", -pot);
		me->add("repute",-rep);
		me->add("rep/hyw", -rep);  // Zine Oct 31 2010 用rewardd控制奖励
		tell_object(me,RED "由于你未能帮助韩员外复仇，被扣除：\n"
				+ chinese_number(exp) + "点实战经验，\n"
				+ chinese_number(pot) + "点潜能，\n"
				+ chinese_number(rep) + "点江湖声望作为惩罚。\n" NOR);            
		if (me->query("combat_exp") < 2000)
		me->set("combat_exp",2000);
		if (me->query("potential") < 0) 
		me->set("potential", 0);
		if (me->query_temp("hyw/pic"))
		{
			me->set("hyw/pic_fail",1);
		}
        me->delete_temp("hyw");
		me->delete("hyw/start");
		me->add("hyw/lianxu_fail",1);
		if (objectp(qiangdao=me->query_temp("hyw/current_qiangdao")))
		qiangdao->leave();
		return 1;
	}
	else
	{
		command("? " + me->query("id"));
		return 1;
	}
}

