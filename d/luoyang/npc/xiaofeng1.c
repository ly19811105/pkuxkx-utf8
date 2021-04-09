// File		: xiaofeng.c
// Created By	: iszt@pkuxkx, 2007-03-28
// Last Updated	: iszt@pkuxkx, 2007-04-12

#include <ansi.h>

inherit FAMILY_NPC;

#define LIMIT_LENGTH    108

#define HZK "/d/luoyang/npc/etc/Hzk"
#define ASC "/d/luoyang/npc/etc/Asc"

#define DEFAULT_FILL "*"
#define DEFAULT_FCOLOR ""
#define DEFAULT_BG " "
#define DEFAULT_BGCOLOR ""
#define AUTO_SIZE 12
int ask_job();
int do_answer(string arg);
int ask_test();
int ask_test1();
string RandomDigtal();
int ask_fail();
int ask_finish();
int ask_times();
int give_reward(object me);

void create()
{
	set_name("萧峰", ({ "xiao feng", "xiao", "feng", }) );
	set("title", "丐帮第八代帮主");
	set("gender", "男性" );
	set("age", 32);
	set("str", 99);
	set("long", "他的身材甚是魁伟，三十来岁年纪，身穿灰色旧布袍，已微有破烂，浓眉大眼，\n"
		"高鼻阔口，一张四方的国字脸，颇有风霜之色，顾盼之际，极有威势。\n");
	set("combat_exp", 10000000);
        set("attitude", "peaceful");
	set("rank_info/respect", "英雄");
	add("inquiry", ([
		"name" : "在下萧峰。",
		"rumors" : "传闻西夏一品堂搜罗了一批武功好手来我中原捣乱……",
		"job" : (: ask_job :),
                "test" : (: ask_test :),
                "test1" : (: ask_test1 :),
		"任务" : (: ask_job :),
		"fail" : (: ask_fail :),
		"放弃" : (: ask_fail :),
		"finish" : (: ask_finish :),
		"完成" : (: ask_finish :),
		"times" : (: ask_times :),
		"功劳" : (: ask_times :),
	]));
	set("no_get", 1);
	set_gaibang(this_object(), 400, 0);
	setup();
	carry_object("/clone/cloth/male2-cloth.c")->wear();
}

void init()
{
        add_action("do_answer", "answer");
        add_action("do_answer", "huifu");
}
int ask_job()
{
	object me = this_player();
	object ob, where;
	string msg, job_msg;
	string respect = RANK_D->query_respect(me);
	string name1, name2;
	int level;

	if(me->is_busy())
	{
		command("say 你先忙完你的事情吧。");
		return 1;
	}
	if(me->is_fighting())
	{
		command("say 你先打完架吧。");
		return 1;
	}
	if(me->query_temp("xiaofeng/job"))
	{
		command("say 这位"+respect+"，不是已经叫你去"+me->query_temp("xiaofeng/job")+"了么？");
		return 1;
	}
	if(me->query("xiaofeng/on_job"))
	{
		command("say 这位"+respect+"，上次交给你的任务还没有完成么？");
		return 1;
	}
	if(!wizardp(me) && time() - query("last_give_time") < 10)
	{
		command("say 刚刚已经有人前去了，多谢"+respect+"好意。");
		return 1;
	}
	if(!wizardp(me) && time() - me->query("xiaofeng/last_fail") < 450)
	{
		command("say "+respect+"先去在江湖中历练一番吧。");
		return 1;
	}
	if(!wizardp(me) && time() - me->query("xiaofeng/last_job") < 200)
	{
		command("say "+respect+"先下去休息休息吧。");
		return 1;
	}
	if(me->query("combat_exp") < 1000000)
	{
		command("haha");
		command("say 小兄弟，这可不是闹着玩的，你还是先去练练武艺吧。");
		return 1;
	}

	me->set("xiaofeng/on_job", 1);
	set("last_give_time", time());

	command("ok");
	ob = new(__DIR__"target");
	switch(random(4))
	{
	case 0:
		ob->set("job_type", "杀");
		me->set_temp("xiaofeng/job_type", "杀");
		me->set_temp("xiaofeng/job", "除掉杀手");
		job_msg = "此人为非作歹，早已恶贯满盈。你去将他除掉，取其首级回来。";
		break;
	case 1:
		ob->set("job_type", "擒");
		me->set_temp("xiaofeng/job_type", "擒");
		me->set_temp("xiaofeng/job", "擒回杀手");
		job_msg = "此人于中原武林颇为有用，你去将他擒回这里交给我。";
		break;
	case 2:
		ob->set("job_type", "劝");
		me->set_temp("xiaofeng/job_type", "劝");
		me->set_temp("xiaofeng/job", "劝服杀手");
		job_msg = "此人加入西夏一品堂不久，尚可教化，你去劝劝(quan)他吧。";
		break;
	case 3:
		ob->set("job_type", "降");
		me->set_temp("xiaofeng/job_type", "降");
		me->set_temp("xiaofeng/job", "战胜杀手");
		job_msg = "此人气焰甚是嚣张，你去给他点颜色瞧瞧，让他认输就好。";
		break;
	}
	ob->set("job_level", random(5)+1);
	me->set_temp("xiaofeng/job_level", ob->query("job_level"));
	ob->do_copy(me);
	sscanf(NAME_D->create_name(), "%s@%s", name1, name2);
	me->set_temp("xiaofeng/target_name", name1);
	me->set_temp("xiaofeng/target_id", name2);
	where = TASK_D->random_place();
	msg = CYN"$n道：「传闻西夏一品堂派出了若干蒙面杀手，最近出现在"
		+TASK_D->place_belong(where)+"附近的"+where->query("short")+NOR+CYN"。\n          ";
	msg += job_msg+"\n          ";
	me->set_temp("xiaofeng/target_place", TASK_D->place_belong(where));
	switch(ob->query("job_level"))
	{
	case 1: msg += HIG"此人武功应该和你相仿，但务必不可掉以轻心。"NOR; break;
	case 2: msg += HIW"此人武功不弱，不少英雄好汉都折在他的手上。"NOR; break;
	case 3: msg += HIY"此人武功颇强，务须准备周全。"NOR; break;
	case 4: msg += RED"此人武功应是你我之大敌，应以智取，不可硬拼。"NOR; break;
	case 5: msg += HIR"此人武功深不可测，千万小心！"NOR; break;
	default:
	}
	msg += NOR+CYN"」\n$n拍拍$N的肩，说道：「好兄弟，就交给你了！珍重！」\n"NOR;
	message_vision(msg, me, this_object());
	ob->move(where);
	ob->random_move();//whuan 随机走动一次，避免岳王墓地道和丐帮升袋室之类的地方
        ob->random_move();
        ob->random_move();
	return 1;
}

int ask_fail()
{
	object me = this_player();
	string msg;

	if(!me->query("xiaofeng/on_job"))
	{
		command("say 你又没有任务，如何轻言放弃！\n");
		return 1;
	}
	msg = CYN"$n叹了口气，说道：「好吧，这也是有些难为你了。」\n";
	msg += "$n记了些什么，对$N挥了挥手，示意让$N退下。\n"NOR;
	message_vision(msg, me, this_object());
	me->add("combat_exp", -8000);
	me->add("exp/xiaofeng", -8000);
	me->add("potential", -3000);
	me->add("pot/xiaofeng", -3000);
	if(me->query("combat_exp") < 2000)
		me->set("combat_exp", 2000);
	me->delete_temp("xiaofeng");
	me->delete("xiaofeng/on_job");
	me->set("xiaofeng/last_fail", time());
	return 1;
}

int ask_finish()
{
	object me = this_player();
	mapping skills = me->query_skills();
	string* sname;
	string skill;

	if(!me->query_temp("xiaofeng/finish") || me->query_temp("xiaofeng/fail"))
	{
		command("heng");
		message_vision(CYN"$N冷冷的盯着$n道：「你以为如此弄虚作假能瞒得过我么？」\n"NOR, this_object(), me);
		return 1;
	}
	if(me->query_temp("xiaofeng/job_type") == "杀")
	{
		command("say 叫你去杀人，那人的首级何在？\n");
		return 1;
	}
	if(me->query_temp("xiaofeng/job_type") == "擒")
	{
		command("say 叫你去将人擒回来，那人何在？\n");
		return 1;
	}

	command("say 很好。"+me->query("name")[0..1]+"兄弟，辛苦你了！");
	give_reward(me);

	return 1;
}

int accept_object(object who, object ob)
{
	if(who->query_temp("xiaofeng/job_type") == "杀")
	{
		if(ob->is_charcter() && !ob->is_corpse())
		{
			command("faint "+who->query("id"));
			command("say 让你去杀人，给我活的做什么？");
			return 0;
		}
		if(ob->is_corpse())
		{
			command("walkby "+who->query("id"));
			command("say 给我首级就可以了，亏你还把尸体千里迢迢的背回来。");
			return 0;
		}
		if(!ob->is_head())
		{
			command("scowl");
			command("say "+who->query("name")[0..1]+"兄弟，你给我这个却是什么意思？");
			return 0;
		}
		if(ob->query("victim_name")!=who->query_temp("xiaofeng/target_name")
			|| ob->query("victim_id")!=who->query_temp("xiaofeng/target_id"))
		{
			command("heng");
			command("say 这不是我派你去杀的那个人罢？");
			return 0;
		}
		command("sigh");
		command("say 好吧，这也是他自取灭亡，须怪不得你我下手不容情。");
		command("say "+who->query("name")[0..1]+"兄弟，感谢你为武林除去了一害！");
		give_reward(who);
		return 1;
	}
	if(who->query_temp("xiaofeng/job_type") == "擒")
	{
		if(ob->is_corpse() || ob->is_head())
		{
			command("kick4 "+who->query("id"));
			command("say 此人尚未恶贯满盈，是故只让你生擒回来，却给我这个！");
			return 0;
		}
		if(!ob->is_character())
		{
			command("? "+who->query("id"));
			command("say 让你去把人擒回来，给我这个作甚？");
			return 0;
		}
		if(!ob->query("uni_target") || ob->query("uni_target") != who
			|| ob->query("name") != who->query_temp("xiaofeng/target_name")
			|| ob->query("id") != who->query_temp("xiaofeng/target_id"))
		{
			command("heng");
			command("say 这不是我派你去擒的那个人罢？");
			return 0;
		}
		command("touch "+who->query("id"));
		command("say "+who->query("name")[0..1]+"兄弟，真是辛苦你了！");
		give_reward(who);
		call_out("do_dest", 1, ob);
		return 1;
	}
}

int give_reward(object me)
{
        string msg;
	int reward, i;
	string respect = RANK_D->query_respect(me);
	mapping skills = me->query_skills();
	string* sname;
	string skill;
	string job_type = me->query_temp("xiaofeng/job_type");
	string system_msg = me->query("name")+"在萧峰任务中获得奖励";
	string channel_msg = me->query("name")+me->query_temp("xiaofeng/job")+"，被奖励了";

	if(!random(4))
		CHANNEL_D->do_channel(this_object(), "bd", "goodman "+me->query("id"), 1);
	write(HIW"你被奖励了：\n");
	reward = 6000+me->query_temp("xiaofeng/job_level")*2000;
	reward += me->query_skill("force");
	reward += me->query_skill("dodge");
	reward += me->query_skill("parry");
	reward += me->query_skill("literate", 1) * 2;
	reward += me->query_temp("xiaofeng/bonus");
	if(me->query("combat_exp") > 50000000)
		reward = reward / 3 * 2;
        if(me->query("combat_exp") > 300000000)
		reward = reward / 10;
	reward = reward / 2 + random(reward);
	write("\t"+chinese_number(reward)+"点经验；\n");
	system_msg += reward+"点经验，";
	channel_msg += chinese_number(reward)+"点经验、";
	me->add("combat_exp", reward);
	me->add("exp/xiaofeng", reward);

	reward = random(reward)/2 + reward/5;
	write("\t"+chinese_number(reward)+"点潜能；\n");
	system_msg += reward+"点潜能，";
	channel_msg += chinese_number(reward)+"点潜能、";
	me->add("potential", reward);
	me->add("pot/xiaofeng", reward);

	reward = 200 + random(reward)/1000*100;
	write("\t"+chinese_number(reward)+"点江湖声望。\n");
	system_msg += reward+"点江湖声望";
	channel_msg += chinese_number(reward)+"点江湖声望";
	me->add("repute", reward);

	me->add("xiaofeng/"+job_type, 1);
	write("你已经完成了"+chinese_number(me->query("xiaofeng/"+job_type))+"次"
		+me->query_temp("xiaofeng/job")+"的工作。\n"NOR);

	if(wizardp(me) || !random(2+me->query_kar()/4) && sizeof(skills)>10)
	{
		command("say 武功本身并无善恶，端在人之为用。行善则武功愈强愈善，肆恶则愈强愈恶。");
		message_vision(YEL"$N指点了$n几招，$n只觉脑中豁然开朗！\n"NOR, this_object(), me);
		sname = keys(skills);
		i = random(sizeof(sname));
		skill = sname[i];
                if(SKILL_D(skill)->valid_enable("force") && !random(3))
			skill = "force";
		write(HIC"你的「"+CHINESE_D->chinese(skill)+"」进步了！\n"NOR);
		system_msg += "，一级"+skill;
		channel_msg += "，一级"+CHINESE_D->chinese(skill);
		me->set_skill(skill, me->query_skill(skill, 1)+1);
		channel_msg += "！\n";
		CHANNEL_D->do_channel(this_object(), "chat", channel_msg);
	}

	system_msg += "。";
	CHANNEL_D->do_channel(this_object(), "sys_misc", system_msg);
	me->delete_temp("xiaofeng");
	me->delete("xiaofeng/on_job");
	me->set("xiaofeng/last_job", time());
        me->set_temp("xiaofeng/randomcode",RandomDigtal());
        command("say 如果想请减少等待时间，请做一道测试题（ask xiao about test）。");
/*
        msg=Display((string)me->query_temp("xiaofeng/randomcode"));
        printf("%s",msg);
*/
	return 1;
}

int ask_times()
{
	object me = this_player();
	command("say 你现在劝服杀手"+chinese_number(me->query("xiaofeng/劝"))+"名；"
		"擒回杀手"+chinese_number(me->query("xiaofeng/擒"))+"名；"
		"战胜杀手"+chinese_number(me->query("xiaofeng/降"))+"名；"
		"除掉杀手"+chinese_number(me->query("xiaofeng/杀"))+"名。");
	return 1;
}

void do_dest(object ob)
{
	if(!objectp(ob))
		return;
	destruct(ob);
}
void unconcious()
{
        die();
}

void die()
{
        message("vision","萧峰默运玄功，片刻之间就恢复如常。\n",environment(this_object()));
        this_object()->set("eff_qi",this_object()->query("max_qi"));
        this_object()->set("qi",this_object()->query("max_qi"));
        this_object()->set("eff_jing",this_object()->query("max_jing"));
        this_object()->set("jing",this_object()->query("max_jing"));
        return;
}
varargs string Display(string str, int size, string fill, string bg, string fcolor, string bgcolor)
{
        int offset;
        int *mask = ({0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1});
        int scale;
        int r,z,leafy;
        string char;
        string *out;
        
        if(!size)
#ifdef AUTO_SIZE
                size = AUTO_SIZE;
#else
                error("TEXT to PIC need size\n");
#endif
        out = allocate(16);
        out = map_array(out, (: $1 = "" :));
        size *= 2;

        if(!fill) fill = DEFAULT_FILL;
        if(!fcolor) fcolor = DEFAULT_FCOLOR;
        if(!bg) bg = DEFAULT_BG;
        if(sizeof(fill) != sizeof(bg)) {
                fill = DEFAULT_FILL;
                bg = DEFAULT_BG;
        }
        if(!bgcolor) bgcolor = DEFAULT_BGCOLOR;

        for(int k = 0; k < sizeof(str); k++) {
                                leafy = random(2);
                                r = random(10);
                                z = random(3);
                                if(z == 1)
                                size = 24;
                                else if(z == 2)
                                size = 32;
                                else size = 28;
                                 if(leafy) { fill = HIR+"@"+NOR;
                                bg = "@";
                                }
                                else {
                                 fill = HIW+"@"+NOR;
                                bg = " ";
                                }
                                                if(mask[0] & str[k]) {
                        offset = size*( (atoi(sprintf("%d", str[k]))-0xA1)*94 + atoi(sprintf("%d", str[k+1])) - 0xA1 );
                        char = read_bytes(HZK + (size/2), offset, size);
                        k++;
                        scale = 2;
                } else {
                        offset = str[k] * (size/2);
                        char = read_bytes(ASC + (size/2), offset, (size/2));
                        scale = 1;
                }

                if(!sizeof(char)) error("TEXT to PIC can't read bytes from character lib\n");

                for(int i = 0; i < sizeof(char); i++) {
                        for(int j = 0; j < 8; j++) {
                                if(mask[j] & char[i]) 
                                        out[i/scale] += fcolor + fill;
                                else 
                                        out[i/scale] += bgcolor + bg;
                        }
                }

                 for(int i = 0; i < sizeof(out); i++) {
                 if(!leafy) {
                    out[i] = replace_string(out[i], fcolor + fill, fill );
                    //  out[i] = replace_string(out[i], bg + bgcolor + bg, bg + bg);
                         }
                      }
                            }
        
        return implode(out, "\n") + NOR;
}
int ask_test()
{
        if (this_player()->query_temp("xiaofeng/randomcode")==0 && this_player()->query("huifu_test")==0)
        {
       message("vision","萧峰说道：“这事儿跟你有关系么？”\n",this_player());
       return 1;}
     printf("%s",Display((string)this_player()->query_temp("xiaofeng/randomcode")));
        printf("%s","\n");  
        command("say 请在30秒内回答(answer/huifu)出字符串的内容。");
        command("say 如果没看不清，请ask xiao feng about test再问一次。");
        return 1;
}
string RandomDigtal()
{
   string *ABC=({"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"});
   string *DIG=({"0","1","2","3","4","5","6","7","8","9"});
   string MyCode;
   MyCode=ABC[random(sizeof(ABC))]+DIG[random(sizeof(DIG))]+DIG[random(sizeof(DIG))]+DIG[random(sizeof(DIG))];
   return MyCode;
}
int do_answer(string arg)
{
    object me=this_player();
    int last_job_time;
    int answer_time;
    int time_gap;
    int time_wait;
    if ((int)me->query_temp("xiaofeng/randomcode")==0)
       return 0;
    if (!me->query("xiaofeng/last_job")) 
       return 0;

    if (me->query("xiaofeng/on_job"))
       return 0;
    else
       last_job_time=me->query("xiaofeng/last_job");
       message("vision",me->name()+"回答道：“是"HIR+arg+NOR"么?”\n",environment(me));
    if (arg==(string)me->query_temp("xiaofeng/randomcode"))
    	{
       message("vision","萧峰微微颔首道：“正是！”\n",environment(me));
       answer_time=time();
       time_gap=answer_time-last_job_time;
       me->delete_temp("xiaofeng/randomcode");
       if (time_gap>=30)
          message("vision","萧峰皱了皱眉头：“花了这么久，猜出来也没用啦。”\n",environment(me));
       else
       	{
          time_wait=70-time_gap;
          if (time_wait>=70) time_wait=70;
          if (time_wait<=0) time_wait=0;
          me->add("xiaofeng/last_job",-time_wait);
          message("vision","萧峰说道：“你的等待时间减少了"+chinese_number(time_wait)+"秒。”\n",environment(me));
        }       
     }
    else
       message("vision","萧峰摇摇头说道：“不对！”\n",environment(me));
    
    return 1;
}
int ask_test1()
{
        if (this_player()->query("huifu_test")==0)
        {
            message("vision","萧峰说道：“这事儿跟你有关系么？”\n",this_player());
            return 1;
        }
        printf("%s",Display(RandomDigtal()),20+random(5));
        printf("%s","\n");  
        return 1;
}
