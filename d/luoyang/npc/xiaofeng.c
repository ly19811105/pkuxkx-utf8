// File		: xiaofeng.c
// Created By	: iszt@pkuxkx, 2007-03-28
// Last Updated	: iszt@pkuxkx, 2007-04-12

#include <ansi.h>
#include <title.h>
inherit FAMILY_NPC;
#include <cooldown.h>
#include "/d/luoyang/npc/reward.h"
#define LIMIT_LENGTH    108

#define HZK "/d/luoyang/npc/etc/Hzk"
#define ASC "/d/luoyang/npc/etc/Asc"

#define DEFAULT_FILL "*"
#define DEFAULT_FCOLOR ""
#define DEFAULT_BG " "
#define DEFAULT_BGCOLOR ""
#define AUTO_SIZE 12
#include "/d/yingtiansouth/dufu/npc/Pro.h"
//"深红":HIR,"暗红":RED,"深绿":HIG,"暗绿":GRN,"深黄":HIY,"暗黄":YEL,"深蓝":HIB,"暗蓝":BLU,"深紫":MAG,"暗紫":HIM,"天青":HIC,"靛青":CYN,"深白":HIW,"暗白":WHT
int ask_job();
int do_answer(string arg);
int ask_test();
string RandomDigtal();
int ask_finish();
int ask_times();
int ask_title();
void create()
{
	set("Pro_Colors",({"深红","暗红","天青","靛青"}));
	set("Pro_id","XF");
	set_name("萧峰", ({ "xiao feng", "xiao", "feng", }) );
	set("title", "丐帮第八代帮主");
	set("gender", "男性" );
  set("uni_target",1);
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
//                "test" : (: ask_test :),
		"任务" : (: ask_job :),
		"fail" : (: ask_fail :),
		"放弃" : (: ask_fail :),
		"finish" : (: ask_finish :),
		"完成" : (: ask_finish :),
		"times" : (: ask_times :),
		"功劳" : (: ask_times :),
		"头衔" : (: ask_title :)
	]));
	set("no_get", 1);
	set("job_id","萧峰");
	set("job_eid","xiaofeng");
	set_gaibang(this_object(), 400, 0);
	set("shen_type",1);set("score",100000);setup();
	carry_object("/clone/cloth/male2-cloth.c")->wear();
}

void init()
{
        //add_action("do_answer", "answer");
        //add_action("do_answer", "huifu");
}

/*int cal_jiao(int cal_cnt)
{int back_int;
int js_int;
	js_int=10-(int)(cal_cnt/10);
	if (js_int<0)
	{
		js_int=2;
	}

	if (cal_cnt<46)
	{
		back_int=random(js_int-1)+1;
	}
	else
	{
		back_int=random(js_int);
	}
	return back_int;
}

int cal_quan(int cal_cnt,int jiao_cnt)
{
	int js_int,js_zhi;
	js_zhi = random(10);
	js_int = (int)(100-cal_cnt-jiao_cnt*10-js_zhi)/5;
	 if (js_int>10)
	 {
		 js_int=10;
	 }
	 if (js_int<0)
	 {
		 js_int=0;
	 }
	 return js_int;
}

int test()
{
	int jx_quan,jx_jiao,jx_zhi;
		mixed *jiao_idx1,*jiao_idx2;
    mapping jiao_mod1,jiao_mod2;

			jx_quan = cal_quan(jiao_cnt,jx_jiao);
		jx_zhi = 100-jx_jiao*10-jx_quan*5;
		jx_zhi -= jiao_cnt;
		if (jx_zhi<0)
		{
			jx_zhi=0;
		}
		write("计算数值为:"+jx_jiao+","+jx_quan+","+jx_zhi+"\n");
		if (random(2))
		{
			jiao_mod1 = ([ "脚" : jx_jiao, "拳" : jx_quan, "指" : jx_zhi, ]);
			jiao_idx1=keys(jiao_mod1);
			jiao_idx2=values(jiao_mod1);
		}
		else
		{
			jiao_mod2 = ([ "脚" : jx_jiao, "掌" : jx_quan, "指" : jx_zhi, ]);
			jiao_idx1=keys(jiao_mod2);
			jiao_idx2=values(jiao_mod2);
		}
		if (jiao_idx2[0]!=0)
		{
			write("值1:"+chinese_number(jiao_idx2[0])+jiao_idx1[0]+"\n");
			msg = chinese_number(jiao_idx2[0])+jiao_idx1[0];
		}
		if (jiao_idx2[1]!=0)
		{
			write("值2:"+chinese_number(jiao_idx2[1])+jiao_idx1[1]+"\n");
			msg += chinese_number(jiao_idx2[1])+jiao_idx1[1];
		}
		if (jiao_idx2[2]!=0)
		{
			write("值3:"+chinese_number(jiao_idx2[2])+jiao_idx1[2]+"\n");
			msg += chinese_number(jiao_idx2[2])+jiao_idx1[2];
		}
}
*/


int ask_job()
{
	object me = this_player();
	object ob, ob1, where, where1;
	string msg, job_msg;
	string respect = RANK_D->query_respect(me);
	string name1, name2;
	int level;
	int f_target_bit=0;
	int jx_shi,jx_ge,jiao_cnt,jiao_f_cnt;
	string *jiao_idx1,*jiao_idx2;
	//mixed *jiao_idx1,*jiao_idx2;
  //  mapping jiao_mod1,jiao_mod2;

	if (time()-me->query_temp("askjob")-me->query_temp("askjobtimes")<=0)
	{
		me->add_temp("askjobtimes",1);
		tell_object(me,"过"+(me->query_temp("askjob")-time()+me->query_temp("askjobtimes"))+"秒再来问吧。\n");
		return 1;
	}
	else
	{
		me->set_temp("askjob",time());
		me->delete_temp("askjobtimes");
	}
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
	if(IfInCoolDown(me,1))
	return 1;
	if(me->query_combatgrade() < 30)
	{
		command("haha");
		command("say 小兄弟，这可不是闹着玩的，你还是先去练练武艺吧。");
		return 1;
	}
	me->set("xiaofeng/on_job", 1);
	set("last_give_time", time());
	me->set_temp("task_stat/xiaofeng/xiaofeng_starttime",time());
	command("ok");
	ob = new(__DIR__"target");
	switch(random(5))
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
		job_msg = "此人于中原武林颇为有用，你去将他擒回这里交给我。打晕其之后若他再醒来，可直接"+HIR+"点晕(dian)"+CYN+"他。";
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
	case 4:
		ob->set("job_type", "教");
		me->set_temp("xiaofeng/job_type", "教");
		me->set_temp("xiaofeng/job", "教训杀手");
		jiao_cnt = random(61)+20;
		jiao_idx2=({"弄","打","搞",});
		//write("教训数值为:"+jiao_cnt+"\n");
		job_msg = "此人良心未泯，尚有羞耻之心，你去教训(jiao)一下他吧。\n          将他";
		if (random(2)==0)
		{
		//“到，成”模式
			jx_shi = (int)(jiao_cnt/10);
			jx_ge = (int)(jiao_cnt%10);
			jiao_idx1=({"到","成","剩",});
		}
		else
		{
		//“没”，“掉”模式
			jiao_f_cnt=100-jiao_cnt;
			jx_shi = (int)(jiao_f_cnt/10);
			jx_ge = (int)(jiao_f_cnt%10);
			jiao_idx1=({"没","掉","去",});
		}
		if (random(2)==0)
		{//十成制
			if (jx_ge != 0)
			{
				msg = jiao_idx2[random(3)]+jiao_idx1[random(3)]+chinese_number(jx_shi)+"成"+chinese_number(jx_ge);
			}
			else
			{
				msg = jiao_idx2[random(3)]+jiao_idx1[random(3)]+chinese_number(jx_shi)+"成";
			}
		}
		else
		{//百分制
			if (jx_ge != 0)
			{
				msg =  jiao_idx2[random(3)]+jiao_idx1[random(3)]+"百之"+chinese_number(jx_shi)+"十"+chinese_number(jx_ge);
			}
			else
			{
				msg = jiao_idx2[random(3)]+jiao_idx1[random(3)]+"百之"+chinese_number(jx_shi)+"十";
			}
		}	
		job_msg += msg+"气血以后，再行教训。\n";
		ob->set("xiaofeng/jiao_cnt",jiao_cnt);
		ob->set("xiaofeng/jiao_cishu",0);

	//	chinese_number
		//me->set_temp("xiaofeng/jiao_cnt", jiao_cnt);
		break;
	}
	ob->set("job_level", random(5)+1);
	me->set_temp("xiaofeng/job_level", ob->query("job_level"));
	ob->do_copy(me);
	sscanf(NAME_D->create_name(), "%s@%s", name1, name2);
	me->set_temp("xiaofeng/target_name", name1);
	me->set_temp("xiaofeng/target_id", name2);
//过滤非法任务地点和不明区域 by segate@pkuxkx
   while (!objectp(where) || 
          !where->isroom()||
          TASK_D->place_belong(where)=="不明区域"||
          base_name(where) == "/adm/daemons/taskd")
   {
     where = TASK_D->random_place();
   }
//	where = TASK_D->random_place();
//	if (!objectp(where)||!where->isroom()||TASK_D->place_belong(where)=="不明区域")
//		where = TASK_D->random_place();
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
	me->set_temp("xiaofeng/target_ob",ob); //加一个判断
	ob->move(where);
	ob->random_move();
	ob->random_move();
	if (!ob)
	{
		message_vision("$n对$N说道：『此人可能出了点意外，已经不在人世了，你可以再要一个任务重新来过。』\n",ob,me);
		me->delete_temp("xiaofeng/job");
		me->delete_temp("xiaofeng/on_job");
		return 1;
	}

	if ( me->query("hsz_auto") || ((me->query_temp("shilian/start") || me->query("baixiaosheng/tiaozhan")) && random(8)==0) || random(15)==0)
	{
		ob1 = new(__DIR__"target");
		ob1->set("job_level", ob->query("job_level"));
		ob1->do_copy_f(me);
		if (me->query("hsz_auto"))
		{
			where1 = where;
		}
		else
		{
			where1 = TASK_D->random_room(where->query_location(),0);
		}
	/*	if (random(8))
		{
			where1 = TASK_D->random_room(where->query_location(),0);
		}
		else
			
		{
			where1 = where;
		}
		write("真假目标在："+where1->query("short")+"\n");*/
		ob1->move(where1);
	}
	me->set("xiaofeng/last_job", time());
/* 暂时去掉四次random_move 注意：如果要再加入此设置请参照胡一刀任务，每次move之前判断target是否还存在
	ob->random_move();//whuan 随机走动一次，避免岳王墓地道和丐帮升袋室之类的地方
        ob->random_move();
        ob->random_move();
*/
	return 1;
}

int ask_finish()
{
	object me = this_player();
	mapping skills = me->query_skills();
	string* sname;
	string skill;

	if( !me->query_temp("xiaofeng/finish") || 
		  me->query_temp("xiaofeng/fail") || 
		  !me->query("xiaofeng/on_job") )
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
	if (!me->query("biography/jobs/xiaofeng"))
	{
		me->set("biography/jobs/xiaofeng",time());//个人传记记录第一次完成任务时间ZINE
	}
	give_reward(me);

	return 1;
}

int destletter(object ob)
{
	if(ob)
	destruct(ob);
	return 1;
}

int accept_object(object who, object ob)
{
    if( ob->query("letterback")==2&&ob->query("owner")==who->query("id"))
    {
        call_out("destletter", 1, ob);
        message_vision("$N接过$n手里的家信，感动的热泪盈眶：这是老婆写给我的信，我，我不会亏待你的！",this_object(),who);
	    who->set_temp("extrajob/xf",1);
        return 1;
    }
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
	  who->set_temp("xiaofeng/hard", ob->query_temp("advanced_quest") );
		give_reward(who);
		call_out("do_dest", 1, ob);
		return 1;
	}
}

int ask_times()
{
	object me = this_player();
	command("say 你现在劝服杀手"+chinese_number(me->query("xiaofeng/劝"))+"名；"
		"教训杀手"+chinese_number(me->query("xiaofeng/教"))+"名；"
		"擒回杀手"+chinese_number(me->query("xiaofeng/擒"))+"名；"
		"战胜杀手"+chinese_number(me->query("xiaofeng/降"))+"名；"
		"除掉杀手"+chinese_number(me->query("xiaofeng/杀"))+"名。");
	return 1;
}

int ask_title()
{
	string title;
	int times;
	times=this_player()->query("xiaofeng/劝")+this_player()->query("xiaofeng/擒")+this_player()->query("xiaofeng/教")+
	      this_player()->query("xiaofeng/降")+this_player()->query("xiaofeng/杀");
	
	if ( times<500 )
	{
		command("say 你还没有完全掌握追缉蒙面杀手的诀窍。\n");
		return 1;
	}
	else if ( times <=1000 )
		title=YEL"十里"MAG"缉凶"NOR;
	else if ( times <=2000 )
		title=HIY"百里"HIM"荡魔"NOR;
	else if ( times <=3000 )
		title=CYN"千里"RED"追魂"NOR;
	else
		title=HIC"万里"HIR"绝命"NOR;
	
	this_player()->set_title(({TITLE_MJOB1, TITLE_MJOB2, TITLE_MJOB3}), title, ({"十里","百里","千里","万里"}));
	command("say 你已经达到"+title+"的境界。\n");
	return 1;
}

void do_dest(object ob)
{
	if(!objectp(ob))
		return;
        ob->move("/clone/misc/void");
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
                                bg = "*";
                                }
                                else {
                                 fill = HIW+"*"+NOR;
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
     printf("%s","/d/luoyang/npc/display.c"->Display((string)this_player()->query_temp("xiaofeng/randomcode")));
        printf("%s","\n");  
        command("say 请在30秒内回答(answer/huifu)出字符串的内容。");
        command("say 如果没看清，请ask xiao feng about test再问一次。");
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
