// linzhennan.c 林震南
// modified by Jay 4/7/96
// Modified by iszt@pkuxkx, 2007-03-03
// Modified by whuan@pkuxkx 2007-8-20

#include <ansi.h>
#include <title.h>

inherit NPC;
string* dart_area=({
"/d/pker/dangpu","/d/xiangyang/dangpu","/d/city/qianzhuang","/d/guiyunzhuang/taihujie2","/d/quanzhou/qianzhuang",
"/d/suzhou/jubaozhai","/d/beijing/quanjude2","/d/beijing/baoyuan","/d/beijing/biaoju","/d/quanzhou/dangpu",   
"/d/lingzhou/jiuguan", "/d/huashan/yuquan","/d/dalicheng/dalicheng11","/d/luoyang/qianzhuang","/d/dalunsi/dachedian",
"/d/wudang/sanqing","/d/quanzhen/chongxt","/d/huashan/bieyuan","/d/yideng/yideng/road4","/d/yashan/wansouth3",
"/d/yuewangmu/muqian","/d/quanzhou/dating","/d/hangzhou/qianzhuang"
});
string* dart_short=({
"杀手帮当铺","襄阳当铺","扬州钱庄","归云庄太湖街","嘉兴钱庄",
"苏州聚宝斋","北京全聚德","北京宝源钱庄","北京武胜镖局","泉州当铺",
"灵州酒馆","华山玉泉院","太和居二楼","洛阳四海钱庄","招财大车店",
"武当三清殿","全真玄虚堂","华山别院","桃源驿站","牙山小荒地",
"岳王墓墓前广场","泉州陆家庄大厅","杭州江南钱庄"
});
string* dart_id=({
"dugu meng","shi chunqiu","qian yankai","shang ren","bao fangyuan",
"sun baopi","wu liuqi","huo ji","wang wutong","wang fugui","xixia mingshang",
"fortune teller","song laoban","hu xueyuan","li zhaocai",
"song yuanqiao","ma yu","feng buping","qiu qianren","huangmao gui",
"bao dating","lu liding","jin qier"
});
string* dart_name=({
"独孤梦","史春秋","钱眼开","商人","包方圆",
"孙剥皮","吴六奇","钱庄伙计","王武通","王福贵",
"西夏名商","李铁嘴","宋老板","胡雪源","李招财",
"宋远桥","马钰","封不平","裘千仞","黄毛鬼",
"包打听","陆立鼎","金乞儿"
});
int* dart_value=({8,11,2,8,9,
	10,12,13,11,10,
	11,8,12,14,13,
	13,13,10,9,12,
	11,10,10});

string do_job1();
string do_job2();
string do_job(string arg,object ob);

string do_give();
string do_fail();

int ask_fuwei();
int ask_yuantu();
int rank_me();
int ask_pixie();
int ask_tong();

void create()
{
	set_name("林震南", ({ "lin zhennan", "lin", "zhennan" }));
	set("gender", "男性");
	set("age", 45);
	set("long", "他就是「福威镖局」的总镖头－－林震南。\n");
	set("no_get", 1);

	set("combat_exp", 30000);
	set("shen_type", 1);

	set("max_neili", 500);
	set("neili", 500);
	set("jiali", 10);

	set_skill("force", 40);
	set_skill("sword", 50);
	set_skill("unarmed", 50);
	set_skill("dodge", 50);
	set_skill("parry", 50);

	set("inquiry", ([
		"向阳老宅" : "林震南说道：那是我从前在福建时住的家院，已经破败了。",
		"福威镖局" : (: ask_fuwei :),
		"远图公" : (: ask_yuantu :),
		"林远图" : "林震南大怒：小孩子这么没礼貌，直呼先人名讳！",
		"辟邪剑法" : (: ask_pixie:),
		"铜钱" : (: ask_tong:),
		"铜板" : (: ask_tong:),
    "押镖": (:do_job2:),
    "保镖": (:do_job2:),
    "护镖": (:do_job2:),
    "护重镖": (:do_job2:),
    "押重镖": (:do_job2:),
    "保重镖": (:do_job2:),
    "重镖": (:do_job2:),
    "奖励": (:do_give:),
    "完成": (:do_give:),
    "称号": (:rank_me:),
    "rank": (:rank_me:),
    "title": (:rank_me:),
    "finish": (:do_give:),
    "done": (:do_give:),
    "放弃":(:do_fail:),
    "fail":(:do_fail:),
    "cancel":(:do_fail:),
    "失败":(:do_fail:),
	]) );


	set_temp("apply/attack", 50);
	set_temp("apply/defense", 50);
	set_temp("apply/damage", 15);

	setup();
	carry_object("/clone/weapon/changjian")->wield();
}

int ask_fuwei()
{
	say("林震南炫耀地说：我们林家三代走镖，一来仗着先祖远图公当年闯下的威名，二\n"
	"来靠著我们林家家传的玩艺儿不算含糊，这才有今日的局面，成为大江以南首屈\n"
	"一指的大镖局。江湖上提到『福威镖局』四字，谁都要翘起大拇指，说一声：『\n"
	"好福气！好威风！』哈哈，哈哈！\n");
	this_player()->set_temp("marks/林1", 1);
	return 1;
}

int ask_yuantu()
{
	if ((int)this_player()->query_temp("marks/林1")) {
		say("林震南磕一磕烟斗，说道：远图公是我的祖父，福威镖局是他一手创办的。当年\n"
		"祖父以七十二路辟邪剑法开创镖局，当真是打遍黑道无敌手。其时白道上英雄见\n"
		"他太过威风，也有去找他比试武艺的，青城派掌门余观主的师父长青子少年之时\n"
		"便在他辟邪剑法下输了几招。\n");
		this_player()->set_temp("marks/林2", 1);
		return 1;
	}
	else {
		say("林震南说道：远图公是我的祖父。\n");
		return 1;
	}
}

int ask_pixie()
{
	int p1, p2, p3, p4;
	
	if ((int)this_player()->query("passwd"))
	{
		say("林震南不悦地说道：我不是都告诉你了吗？我的剑法不及先祖。\n");
	}
	else if ((int)this_player()->query_temp("marks/林2"))
	{
		say("林震南一惊，说道：你怎么知道的？噢，我刚才说露嘴了。嗨，在下的功夫外人\n"
		"不知底细，其实及不上先祖。。\n");
		write("林震南顿一顿，接着对你低声说：先祖去世前，曾给家父留下");
		p1=random(4)+1;
		p2=random(4)+1;
		p3=random(4)+1;
		p4=random(4)+1;
		this_player()->set("passwd",p1*1000+p2*100+p3*10+p4);
		write(CHINESE_D->chinese_number(p1)+"千"+CHINESE_D->chinese_number(p2)+
		"百"+CHINESE_D->chinese_number(p3)+"十"+CHINESE_D->chinese_number(p4));
		write("个\n铜钱，我一直未解其中奥秘。\n");
	}
	else {
		message("vision",HIY "林震南勃然大怒，喝道：你也窥视我们林家的辟邪剑谱？！我跟你拼了！\n"
		NOR, environment(), this_object() );
		kill_ob(this_player());
	}
	this_player()->delete_temp("marks/林1");
	this_player()->delete_temp("marks/林2");
	return 1;
}

int ask_tong()
{
	int p, p1, p2, p3, p4;
	
	if (!(p=(int)this_player()->query("passwd"))) {
		say("林震南一脸讥笑的样子，说：怎么混到这一步了到处要钱？\n");
	}
	else {
		write("林震南低声说：先祖去世前，曾给家父留下");
		p1=(int)p/1000;
		p2=(int)(p-p1*1000)/100;
		p3=(int)(p-p1*1000-p2*100)/10;
		p4=(int)(p-p1*1000-p2*100-p3*10);
		write(CHINESE_D->chinese_number(p1)+"千"+CHINESE_D->chinese_number(p2)+
		"百"+CHINESE_D->chinese_number(p3)+"十"+CHINESE_D->chinese_number(p4));
		write("个\n铜钱，我一直未解其中奥秘。\n");
	}
	
	return 1;
}

string do_job1()
{
	return do_job("0",this_player());
}
string do_job2()
{
	return do_job("1",this_player());
}

string do_job(string arg, object ob)
{
	int n,exp;
	object cart,target,owner;
	n=random(sizeof(dart_area));   
	
	if (ob->is_busy())
		return "你正忙着呢！";
		
	if ( ob->query("in_dart"))
	{
		if(!ob->query_temp("over_dart")&&(int)ob->query_condition("dart_limit" ) <= 0)
		{
			if (ob->query("combat_exp") < 500000)
			{
				ob->delete("in_dart");
				ob->delete("yunbiao/last_reward");
				return "你没有领过什么任务吧？";
			}
			return do_fail();
		}
		else
		{
			//限制机器人狂问刷屏
			ob->start_busy(10);
			return "你不是才要了任务吗？";
		}
	}

	if ( (int)ob->query_condition("dart_limit" ) > 0 )
		return "你好象没完成任务吧。";

	if ( ob->is_busy() || ob->query_temp("pending/exercising"))
		return "你现在正忙着呢。";
	if ( (int)ob->query("combat_exp") < 500000 )
		return "护镖是件危险工作，我看"+RANK_D->query_respect(ob)+"似乎没有这能力！";
/*
	if ( (int)ob->query("exp/hubiao") < -300000 )
		return RANK_D->query_respect(ob)+"已经让我损失了这么多镖，我怎么还可以相信你呢？";
*/
        if ( (int)ob->query("repute") < -400000 )
		return RANK_D->query_respect(ob)+"在江湖上混得灰头土脸，我怎么放心将镖交给你呢？";

	if ( (int)ob->query_skill("force", 1) < 50 )
		return "护镖是件危险工作，我看"+RANK_D->query_respect(ob)+"的基本内功不足！";

//	if(time()-ob->query("last_yunbiao_time")<60)
	if(time()-ob->query("last_yunbiao_time")<180)
	{	
		ob->start_busy(10);
		return "你上次运镖太辛苦了，下去休息休息吧。";
	}
	
  if (ob->query("antirobot/deactivity") > 2) message("vision",HIR"林震南狠狠的对你说到：“怎么总是你！我看你是机器人吧。”\n"NOR,ob);
	
	if (arg == "1")
		ob->set_temp("yunbiao/high_value",1);	//高级镖
	else {
		ob->set_temp("yunbiao/high_value",0);
		tell_object(ob,"林震南对你说道：我这里有一批重镖，如果下次你想护可以跟我说。\n");
	}
	ob->set("in_dart",1);
	ob->set_temp("dart_area",dart_area[n]);
	target = new("/d/city/npc/cart_target");
	target->start_leave();
	target->move(dart_area[n]);
	if (objectp(owner=present(dart_id[n],environment(target))))
	{
		message_vision(dart_name[n] + "对伙计" + target->name() + "说道：最近要有一批镖运到，你出去接应一下，早些回来！\n",target);
		message_vision("$N说道：遵命！\n",target);
	}
	target->set("dart_id",ob->query("id"));
	target->set("dart_name",ob->query("name"));
	target->set("gender",this_player()->query("gender"));
	target->random_move();
	target->random_move();
	target->random_move();
	target->random_move();
	ob->set_temp("dart_id",dart_id[n]);
	ob->set_temp("dart_name",dart_name[n]);
	ob->set_temp("dart_value",dart_value[n]);
	ob->set("in_dart",dart_value[n]);
	ob->set_temp("yunbiao/bonus",dart_value[n]);
	ob->set_temp("yunbiao/killed_num",0);
	ob->set_temp("dart_target",target);
	ob->apply_condition("dart_limit", 60);
	ob->set_temp("huoji_name",target->name());
	ob->set_temp("huoji_where",environment(target)->query("short"));
	
	cart=new("/d/city/npc/obj/cart");
	cart->set("master",ob->query("name"));
	cart->set("masterid",ob->query("id"));
	cart->set("long", replace_string(cart->query("long"), "镖旗", "镖旗，上书一个「"+ob->query("name")[0..0]+"」字"));
	cart->move("/d/city/zhengting");
	command("nod");
	message_vision(CYN "几个伙计将镖推了出来。\n" NOR,ob); 
	ob->set_temp("yunbiao/can_go",1);
	ob->set("last_yunbiao_time",time());
	CHANNEL_D->do_channel(this_object(), "sys_misc",sprintf("%s接到一个护镖任务，地点在%s，等级为%d。", ob->name(),dart_short[n],ob->query_temp("yunbiao/lianxu")));
	return ob->query("name")+"把这批红货送到"+dart_short[n]+dart_name[n]+"那里，他已经派了个伙计名叫"+target->name()+"到"+environment(target)->query("short")+"附近接你，把镖车送到他那里就行了。\n";
    
}

string do_give()
{
	int grward; //金钱奖励
  int bonus, cost_time;
  int creward,preward,rreward,mreward;
  int deactivity_rate;
  object ob,mx;
// int max_pot;

  ob=this_player();
//   max_pot=(int)this_player()->query("max_pot");

  if ( !ob->query("in_dart"))
    return "我没让你走镖啊？";

  if ( !ob->query_temp("over_dart") )
    return "镖车没有送到地头，莫非是你吞了！？";

	//加入reward_d管理后，antirobot由reward负责
	deactivity_rate = 100;
if (ob->query("hbisrobot"))
{
    ob->add("hbisrobot",1);
}
if (ob->query("combat_exp") > 10000000)
{
    
    if(ob->query_temp("yunbiao/lianxu")==5 || ob->query("hbisrobot")>=6)//暂时测试巫师
    {
        message("vision",HIC"林震南沉吟着，护了这么多趟镖，你是值得信赖的，也许你可以再帮我一个忙？\n"NOR,ob);
        mx=new(__DIR__"obj/mixin");
        if (mx)
        {
            mx->set("owner",ob->query("id"));
            tell_object(ob,"林震南递给你一封密信。\n");
            mx->move(ob);
            tell_object(ob,"\n林震南告诉你：这封信用特殊药水写就，你把它显形后，按照指示去做就可以了。\n");
            if(!ANTIROBOT_D->stopped())  //先把运镖连续奖励随机到0-4轮，40%过关，如果完成后续任务，判断为人工，再恢复到4，即每轮检查一次。 By Zine Nov 11 2010
            {
               ob->add("hbisrobot",1);
            }
        }

    }
    ob->add_temp("yunbiao/lianxu",1);
    creward=(random(15)+5)*ob->query_temp("yunbiao/bonus")*deactivity_rate/100;
    preward=(random(4)+3)*ob->query_temp("yunbiao/bonus")*deactivity_rate/100;
    rreward=(1+random(2))*ob->query_temp("yunbiao/bonus")*deactivity_rate/100;
    creward=ceil(creward*ob->query_temp("yunbiao/lianxu")*(ob->query_temp("yunbiao/high_value")*2.5));
    preward=ceil(preward*ob->query_temp("yunbiao/lianxu")*(ob->query_temp("yunbiao/high_value")*2.5));
    rreward=ceil(rreward*ob->query_temp("yunbiao/lianxu")*(ob->query_temp("yunbiao/high_value")*2.5));
    grward=(int)ob->query_temp("yunbiao/lianxu");
//特殊周效果    
    creward = creward*SPEWEEK_D->query_hubiao_bonus()/100;
    preward = preward*SPEWEEK_D->query_hubiao_bonus()/100;
    rreward = rreward*SPEWEEK_D->query_hubiao_bonus()/100; 
    creward = REWARD_D->add_exp(ob,creward);
    ob->add("exp/hubiao",creward);
    preward = REWARD_D->add_pot(ob,preward);
    
    if(ob->query_temp("yunbiao/lianxu")>9) 
    {
    	  CHANNEL_D->do_channel(this_object(), "bd", "admire "+ob->query("id"), 1);
	      ob->set_temp("yunbiao/lianxu",5);
        message("vision",HIC"由于你的辛勤劳动，你额外获得"+chinese_number(preward)+"潜能的奖励！\n"NOR,ob);
        ob->add("potential",preward);
        preward = preward * 2;
    }

    ob->add("pot/hubiao",preward);

    rreward = REWARD_D->add_rep(ob,rreward);
		mreward=random(grward)*20000+20000;
		mreward = REWARD_D->add_money(ob,mreward);

    message("vision",HIW"你一共被奖励了：\n"+chinese_number(creward)+"点经验；\n"+
    chinese_number(preward)+"点潜能；\n"+chinese_number(rreward)+"点江湖声望。\n"NOR,ob);
    message_vision(CYN"$N吩咐了旁边的镖头几句，转头对$n道：「辛苦了，有几两银子略表心意，已经吩咐人存入你的钱庄账户。」\n"NOR, this_object(), ob);
    
}
    else 
{
    
    if(ob->query_temp("yunbiao/lianxu")==5 || ob->query("hbisrobot")>=6)//暂时测试巫师
    {
        message("vision",HIC"林震南沉吟着，护了这么多趟镖，你是值得信赖的，也许你可以再帮我一个忙？\n"NOR,ob);
        mx=new(__DIR__"obj/mixin");
        if (mx)
        {
            mx->set("owner",ob->query("id"));
            tell_object(ob,"林震南递给你一封密信。\n");
            mx->move(ob);
            tell_object(ob,"\n林震南告诉你：这封信用特殊药水写就，你把它显形后，按照指示去做就可以了。\n");
            if(!ANTIROBOT_D->stopped())  //先把运镖连续奖励随机到0-4轮，40%过关，如果完成后续任务，判断为人工，再恢复到4，即每轮检查一次。 By Zine Nov 11 2010
            {
               ob->add("hbisrobot",1);
            }
           
        }

    }
    ob->add_temp("yunbiao/lianxu",1);
    creward=(random(15)+10)*ob->query_temp("yunbiao/bonus")*deactivity_rate/100;
    preward=(random(4)+6)*ob->query_temp("yunbiao/bonus")*deactivity_rate/100;
    rreward=(2+random(3))*ob->query_temp("yunbiao/bonus")*deactivity_rate/100;
    creward=ceil(creward*ob->query_temp("yunbiao/lianxu")*(ob->query_temp("yunbiao/high_value")*2.5));
    preward=ceil(preward*ob->query_temp("yunbiao/lianxu")*(ob->query_temp("yunbiao/high_value")*2.5));
    rreward=ceil(rreward*ob->query_temp("yunbiao/lianxu")*(ob->query_temp("yunbiao/high_value")*2.5));
    grward=(int)ob->query_temp("yunbiao/lianxu");
//特殊周效果    
    creward = creward*SPEWEEK_D->query_hubiao_bonus()/100;
    preward = preward*SPEWEEK_D->query_hubiao_bonus()/100;
    rreward = rreward*SPEWEEK_D->query_hubiao_bonus()/100; 
    if ( (int)ob->query("combat_exp") < 1100000 )  //加入500k-1.1M的额外20%奖励，配合cut护卫，引导玩家尝试各种任务 by Zine Nov 11 2010
    {
        creward=creward*6/5;
        preward=preward*6/5;
        rreward=rreward*6/5;
    }
    if (ob->query("hbisrobot")>2) //打击机器人的任务奖励到正常1/4 By Zine Nov 24 2010
    {
        creward=creward/(int)ob->query("hbisrobot");
        preward=preward/(int)ob->query("hbisrobot");
        rreward=rreward/(int)ob->query("hbisrobot");
    }
    creward = REWARD_D->add_exp(ob,creward);
    ob->add("exp/hubiao",creward);
    preward = REWARD_D->add_pot(ob,preward);
    if(ob->query_temp("yunbiao/lianxu")>7) 
    {
    	  CHANNEL_D->do_channel(this_object(), "bd", "admire "+ob->query("id"), 1);
	      ob->set_temp("yunbiao/lianxu",3);
        message("vision",HIC"由于你的辛勤劳动，你额外获得"+chinese_number(preward)+"潜能的奖励！\n"NOR,ob);
        ob->add("potential",preward);
        preward = preward * 2;
    }
    ob->add("pot/hubiao",preward);
    rreward = REWARD_D->add_rep(ob,rreward);
		mreward=random(grward)*20000+20000;
		mreward = REWARD_D->add_money(ob,mreward);    
    message("vision",HIW"你一共被奖励了：\n"+chinese_number(creward)+"点经验；\n"+
    chinese_number(preward)+"点潜能；\n"+chinese_number(rreward)+"点江湖声望。\n"NOR,ob);
    message_vision(CYN"$N吩咐了旁边的镖头几句，转头对$n道：「辛苦了，有几两银子略表心意，已经吩咐人存入你的钱庄账户。」\n"NOR, this_object(), ob);
    
}
    ob->add("jobs/completed/hubiao",1);
    CHANNEL_D->do_channel(this_object(), "sys_misc",sprintf("%s护镖获得经验%d，潜能%d，声望%d。", ob->name(),creward,preward,rreward));
    
	//加入任务统计系统 by icer
	cost_time = time()-ob->query("last_yunbiao_time");
	if (cost_time < 1000)
	{
		COMBAT_D->add("task_stat/hubiao/complete_times",1);
		COMBAT_D->add("task_stat/hubiao/cost_time",cost_time);
		COMBAT_D->add("task_stat/hubiao/exp",creward);
		COMBAT_D->add("task_stat/hubiao/pot",preward);
		COMBAT_D->add("task_stat/hubiao/repute",rreward);
		COMBAT_D->add("task_stat/hubiao/expratio",to_float(creward)/ob->query("combat_exp"));
	}
	
    ob->set("yunbiao/last_reward",creward/2);
    ob->add_temp("yunbiao/lianxunum",1);
    command("pat "+ob->query("id"));
    ob->delete("in_dart");
    ob->delete("yunbiao/fail_num");
    ob->delete_temp("over_dart");
    ob->delete_temp("dart_name");
    ob->delete_temp("dart_id");
    ob->delete_temp("dart_area");
    ob->delete_temp("dart_value");
    ob->delete_temp("yunbiao/bonus");
    ob->delete_temp("yunbiao/high_value");  
    ob->save();
    if (ob->query("hbisrobot"))
    {
        ob->set_temp("yunbiao/lianxu",1+random(2));
        ob->delete_temp("yb_addi");
    }
    return RANK_D->query_respect(ob)+"果然是栋梁之才！";
}

int dest(object caiwu)
{
	if(caiwu)
	destruct(caiwu);
	return 1;
}

int destxin(object caiwu,object me)
{
    object xin=new(__DIR__"obj/mixin");
    if (caiwu)
    {destruct(caiwu);}
    if (me)
    {
        command("say 这么点小麻烦你都克服不了？好吧好吧，我再给你一次机会。");
        tell_object(me,"林镇南又给了你一封信。\n");
        xin->set("owner",me->query("id"));
        xin->move(me);
        me->set("secondxin",1);
    }
    return 1;
}

int accept_object(object me, object caiwu)
{
    int i,exp,pot;
	string gem;
    object baoshi;
    object lin=this_object();
	
	if( caiwu->query("id") == "cai wu" && caiwu->query("owner") == me->query("id"))
		{   
            if (random(me->query("combat_exp"))>random(20000000))
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
                baoshi = new("/obj/gem/gem");
                baoshi->set_level(5001,9999,gem);    //忽略地
                baoshi->move(me);
                CHANNEL_D->do_channel(this_object(), "rw", me->name(1) +"在帮助林震南追回财物后，获得"+baoshi->name()+"一枚!");
                CHANNEL_D->do_channel(this_object(), "sys_misc", me->name(1) +"在帮助林震南追回财物后，获得"+baoshi->name()+"一枚!"); 
                log_file("static/skf",sprintf("%s(%s) 在%s帮林震南追回财物任务中获得"+baoshi->name()+"一枚！\n",  
                me->query("name"),me->query("id"),ctime(time()))); 
                me->set_temp("yunbiao/lianxu",6);
                me->set_temp("yb_addi",1);
                me->delete("secondxin");
                me->add_busy(1);
                call_out("dest",1,caiwu);
                tell_object(me,"林震南道：哇，你太厉害了，这么快就把这些财物追回，我有重谢！\n");
                return 1;
            }
            else
            {
                exp=(random(800)+me->query("yunbiao/last_reward"))*10;
                if (exp>25000)
                {
                    exp=25000;
                }
                pot=exp/2;
                exp = REWARD_D->add_exp(me,exp);
                me->add("exp/hubiao",exp);
                message("vision",HIC"你帮林震南追回财物，额外获得"+chinese_number(exp)+"点经验的奖励！\n"NOR,me);
                pot = REWARD_D->add_pot(me,pot);
                me->add("pot/hubiao",pot);
                message("vision",HIC"你帮林震南追回财物，额外获得"+chinese_number(pot)+"点潜能的奖励！\n"NOR,me);
                me->set_temp("yunbiao/lianxu",6);
                me->set_temp("yb_addi",1);
                me->delete("secondxin");
                me->add_busy(1);
                call_out("dest",1,caiwu);
                tell_object(me,"林震南道：哇，你太厉害了，这么快就把这些财物追回，我有重谢！\n");
                return 1;
            }
		}
    if (lin->is_busy())
		{
			return notify_fail("林震南正忙着呢！\n");
        }
    if (caiwu->query("id")=="lin's mixin" && caiwu->query("owner")==me->query("id"))
    {
        if (!caiwu->query_temp("xinread"))
        {
            call_out("destxin",1,caiwu);
            lin->add_busy(1);
            command("say 看都没看就还给我？好吧，不帮忙就算了。");
            return 1;
        }
        if (me->query("secondxin"))
        {
            call_out("destxin",1,caiwu);
            lin->add_busy(1);
            command("say 你上次就偷懒，这次还来这套？");
            return 1;
        }
        call_out("destxin",1,caiwu,me);
        lin->add_busy(1);
        me->add_busy(1);
        return 1;
    }
    else
    {
        return notify_fail("林震南一言不发，默默看着你。\n");
    }
}


string do_fail()
{
	object ppl=this_player();
	int exp;
	
	if(!ppl->query("in_dart"))
		return "你没有领过什么任务吧？";
    else
  {
    if (ppl->query("balance")<100000)
    	{
    	return "你弄丢了我的镖，得赔偿我的损失，只是你的存款不够，你想想办法再来吧！";	
    	}
    ppl->apply_condition("dart_limit",-1);
    //赔偿5gold    
    if (ppl->query_temp("yunbiao/fail_num"))
    {
	      ppl->add("yunbiao/fail_num",ppl->query_temp("yunbiao/fail_num"));
	      ppl->delete_temp("yunbiao/fail_num");
    }    
    ppl->add("yunbiao/fail_num",1);
    if (ppl->query("yunbiao/fail_num") > 9)
    	{ 
    	 command("slap "+ppl->query("id"));
    	 command("say 你已经连续丢了我这么多趟镖，得赔偿我10倍的损失。");
    	 ppl->add("balance",-500000);
    	 ppl->add("repute",-10000);
    	}
    else
    	{
       command("heng");
       command("say 你弄丢了我的镖，得赔偿我的损失，哼！");    		
       ppl->add("balance",-50000);
       ppl->add("repute",-300);    		    
      }

	  ppl->set_temp("yunbiao/lianxu",0);
    ppl->set_temp("yunbiao/lianxunum",0);
    ppl->delete("in_dart");
    ppl->delete("yunbiao/last_reward"); 
    ppl->save();   
    		
/* 改成金钱惩罚
	if (ppl->query("combat_exp") < 500000)
	  {
		ppl->delete("in_dart");
		ppl->delete("yunbiao/last_reward");
		return "你没有领过什么任务吧？";
	  }
    command("heng "+ppl->query("id",1));
    exp = ppl->query("yunbiao/last_reward");
    if (exp == 0)
	    exp = 1000;
    if (ppl->query_temp("yunbiao/fail_num"))
    {
	ppl->add("yunbiao/fail_num",ppl->query_temp("yunbiao/fail_num"));
	ppl->delete_temp("yunbiao/fail_num");
    }
    ppl->add("yunbiao/fail_num",1);
    if (ppl->query("yunbiao/fail_num") > 19)     //恶意rob，惩罚平方
	exp = exp * ppl->query("yunbiao/fail_num") * ppl->query("yunbiao/fail_num");
    else
	exp = exp * ppl->query("yunbiao/fail_num");
    ppl->add("combat_exp",-exp);
    ppl->add("exp/hubiao",-exp);
    ppl->add("potential",-exp/5);
    ppl->add("pot/hubiao",-exp/5);
    if (ppl->query("potential")<ppl->query("learned_points"))
	    ppl->set("potential",ppl->query("learned_points"));
    ppl->add("repute",-exp);
	  ppl->set_temp("yunbiao/lianxu",0);
    ppl->set_temp("yunbiao/lianxunum",0);
    ppl->delete("in_dart");
    ppl->delete("yunbiao/last_reward");
    message_vision("$N的经验下降了。\n$N的潜能下降了。\n$N的武林声望下降了。\n",ppl);
    }
    if(ppl->query("combat_exp") < 2000)
    {
//功夫等级检查
	float exper = to_float((ppl->query("combat_exp")>0)?ppl->query("combat_exp"):0);

		mapping skill_status;
		string *sname;
		int level,i;
	if ( !(skill_status = ppl->query_skills()) ) {}
	else
	{
		sname  = keys(skill_status);

		for(i=0; i<sizeof(skill_status); i++) 
		{
			level = skill_status[sname[i]];
		      if( pow(to_float(level-2), 3.0) / 10.0 > exper 
			&& exper > 100.0
			&& SKILL_D(sname[i])->type() != "knowledge") 
			{
				level = ceil( pow( exper*10.0, 0.333333) );
				ppl->set_skill(sname[i], level+1);
				  write(HIR+BNK+"你的" + sname[i] + "等级超出经验支持的能力范围，已经恢复到" + (level+1) + "级。\n"+NOR);
			}
		}
		}
	ppl->set("combat_exp", 2000);
*/
  }    
    return "这点小事你都办不好，还能指望你作些什么呢？";
}
int rank_me()
{
    object me=this_player();
    int exp;
    string title;
    
    exp=(int)me->query("exp/hubiao");
		if (exp<=2000000)
    {
    	command("say 你对本镖局贡献太小，不能给你什么称号。\n"); 
    	return 1;
    }
    
    if( exp <= 3000000 )
      title=HIR"福威镖局"HIY"见习镖师"NOR;
    else if(exp <= 5000000 )
      title=HIR"福威镖局"HIY"镖师"NOR;
    else if(exp < 10000000 )
      title=HIR"福威镖局"HIY"少镖头"NOR;
    else if(exp < 15000000 )
      title=HIR"福威镖局"HIY"总镖头"NOR; 
    else 
      title=HIR"天下第一镖"NOR;
    
    me->set("title", title);
		//title系统记录玩家title by seagate@pkuxkx
		if ( !me->get_title(TITLE_MJOB1) || 
			   strsrch(me->get_title(TITLE_MJOB1), "福威镖局")>=0  )
			me->set_title(TITLE_MJOB1, title);
		else if ( !me->get_title(TITLE_MJOB2) || 
			   strsrch(me->get_title(TITLE_MJOB2), "福威镖局")>=0 )
			me->set_title(TITLE_MJOB2, title);
		else
			me->set_title(TITLE_MJOB3, title);
    tell_object(me, "林震南对你说：你可以做"+me->query("title")+"。\n");
    me->save();  
    return 1;
}



