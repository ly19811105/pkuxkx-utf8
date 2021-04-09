
// jobscore.c
//created by boost 9/19/2008
//modified by Zine 7/2/2013 加入新任务，并增加函数接口给出总评价
#include <ansi.h>
#define MAX_S 20000.0 //调节系数

inherit F_CLEAN_UP;

string bar_string = "■■■■■■■■■■■■■■■■■■■■■■■■■";
string blank_string = "□□□□□□□□□□□□□□□□□□□□□□□□□";
                                        //容易度（难=10）        完成时间（长=10）        手动程度 （高=10）  多人受益 (多=1)         连续性(可连续做=1)	total //新加高级任务难度、长度明显超过老任务，可能超过10的评分。Zine
#define XIAOFENG_WEIGHT 2.4             //7                                4                       9				3					1				24      
#define CISHA_WEIGHT    2.0             //5                                4                       5                1					1				13  //2017.10.25 修改护送任务统计为刺杀任务统计 by caijue
#define HUBIAO_WEIGHT   0.8             //3                                8                       1                3					1				16 //护镖自动化程度极高，则权重折半计算
#define TASK_WEIGHT     2.0             //3                                3                       7                3					4				20
#define HUYIDAO_WEIGHT  2.4             //8                                7                       5                3					1				24
#define HYW_WEIGHT		2.6             //5                                6                       9                3					3				26
#define WAT_WEIGHT		1.6             //6                                1                       4                3					2				16//指塔四的难度
#define MURONG_WEIGHT	1.2             //2                                2                       4                3					1				12

#define PYH_WEIGHT		3.0             //6                               10                       5                3					6				30
#define XBH_WEIGHT		2.7             //3                                9                       5                3					7				27
#define HUWEI_WEIGHT	0.55            //2                                3                       2                3					1				11 //自动化程度高，权重折半
#define BXS_WEIGHT		3.0				//7                                9                      10                3					1				30
#define JIAOFEI_WEIGHT  4.3             //10                              10                      10                3				    10				43
#define CJG_WEIGHT		2.7             //6                                6                       8                1					6				27
#define SHENNI_WEIGHT	2.7             //9                               10                       6                1					1				27
#define TMZ_WEIGHT		1.7             //4								   3                       6                3					1				17
#define TQT_WEIGHT		5.5             //6								  30					   8                3					8				55
mapping *JOB_TABLE=
({
	(["job_name":"TASK","user_mark":"jobs/completed/task","weight":TASK_WEIGHT,"daily":1,"color":HIW]),
	(["job_name":"刺杀","user_mark":"jobs/completed/mzj","weight":CISHA_WEIGHT,"daily":1,"color":HIB]),
	(["job_name":"护镖","user_mark":"jobs/completed/hubiao","weight":HUBIAO_WEIGHT,"daily":1,"color":HIC]),
	(["job_name":"胡一刀","user_mark":"jobs/completed/huyidao","weight":HUYIDAO_WEIGHT,"daily":1,"color":HIR]),
	(["job_name":"萧峰","user_mark":"jobs/completed/xiaofeng","weight":XIAOFENG_WEIGHT,"daily":1,"color":HIM]),
	(["job_name":"韩员外","user_mark":"newjobs/completed/hyw","weight":HYW_WEIGHT,"daily":1,"color":HIG]),
	(["job_name":"万安塔","user_mark":"newjobs/completed/wat","weight":WAT_WEIGHT,"daily":1,"color":WHT]),
	(["job_name":"慕容复","user_mark":"jobs/completed/murong","weight":MURONG_WEIGHT,"daily":1,"color":HIY]),
	//以上为最为常规的任务，将计算方差给出综合权重
	(["job_name":"鄱阳湖","user_mark":"newjobs/completed/pyh","weight":PYH_WEIGHT,"shreshold":1000.0,"bonus_weight":0.1]),
	(["job_name":"萧半和","user_mark":"newjobs/completed/xiaobanhe","weight":XBH_WEIGHT,"shreshold":250.0,"bonus_weight":0.15]),
	(["job_name":"灵鹫护卫","user_mark":"jobs/completed/lingjiu_huwei","weight":HUWEI_WEIGHT,"shreshold":200.0,"bonus_weight":0.05]),
	(["job_name":"剿匪","user_mark":"newjobs/completed/jiaofei","weight":JIAOFEI_WEIGHT,"shreshold":30.0,"bonus_weight":0.12]),
	(["job_name":"藏经阁","user_mark":"newjobs/completed/cjg","weight":CJG_WEIGHT,"shreshold":500.0,"bonus_weight":0.12]),
	(["job_name":"南海神尼","user_mark":"newjobs/completed/shenni","weight":SHENNI_WEIGHT,"shreshold":35.0,"bonus_weight":0.15]),
	(["job_name":"投名状","user_mark":"newjobs/completed/tmz","weight":TMZ_WEIGHT,"shreshold":1500.0,"bonus_weight":0.08]),
	(["job_name":"铜雀台","user_mark":"newjobs/completed/safari","weight":TQT_WEIGHT,"shreshold":50.0,"bonus_weight":0.2]),
	(["job_name":"百晓生","user_mark":"newjobs/completed/bxs","weight":BXS_WEIGHT,"shreshold":1500.0,"bonus_weight":0.1]),
	//以下几种将视为bonus选项
});
int show_score(object user);
int show_all_score();

void create() { seteuid(ROOT_UID); }


int main(object me, string arg)
{
    object ob;

    if(!arg)
        ob = me;
    else if (wizardp(me)||file_name(this_player())=="/adm/daemons/toptend.c") 
    {
        if (arg == "all")
            return show_all_score();

        ob = present(arg, environment(me));
        if (!ob) ob = find_player(arg);
        if (!ob) ob = find_living(arg);
        if (!ob || !me->visible(ob)) return notify_fail("你要察看谁的状态？\n");
    }
    else
        return notify_fail("只有巫师能察看别人的状态。\n");

    return show_score(ob);

}

int show_all_score()
{
    //待写。。。
    return 1;
}
float general_weight(object user)//综合权重基于玩家完成任务的复杂程度以及任务的重要程度而设定
{
	float weight=1.0,times;
	for (int i=0;i<sizeof(JOB_TABLE);i++)
	{
		if (JOB_TABLE[i]["shreshold"]>0)
		{
			times=to_float(user->query(JOB_TABLE[i]["user_mark"]));
			if (times>JOB_TABLE[i]["shreshold"])
			times=JOB_TABLE[i]["shreshold"];
			weight*=(1.0+times/JOB_TABLE[i]["shreshold"]*JOB_TABLE[i]["bonus_weight"]);
		}
	}
	return weight;
}
float variance(float ave,float *scores)
{
	float s=0.0;
	int pass=0;
	if (sizeof(scores)==1)//以防只做一种任务，方差为0的情况。
	scores+=({0,0,0,0,0,0,0});
	for (int i=0;i<sizeof(scores);i++)
	{
		if (scores[i]>ave*3.0/5.0)
		pass+=1;
		s+=((ave-scores[i])*(ave-scores[i]));
	}
	if (pass>=4)//至少3种任务达到平均值3/5以上
	{
		if (s<4000000.0)
		return 0.0;
		return (MAX_S*2/5>sqrt(s))?sqrt(s):MAX_S*2/5;
	}
	if (pass>=3)//至少3种任务达到平均值3/5以上
	{
		if (s<1000000.0)
		return 0.0;
		return (MAX_S/2>sqrt(s))?sqrt(s):MAX_S/2;
	}
	if (pass>=2)
	return (MAX_S*2/3>sqrt(s))?sqrt(s):MAX_S*2/3;
	return sqrt(s);
}
int cal_score(object user)      
{
	int i;
	float bonus_weight,score=0.0,daily_score=0.0,types=0.0,*scores=({}),average,s=0.0;
	for (i=0;i<sizeof(JOB_TABLE);i++)
	if (user->query(JOB_TABLE[i]["user_mark"])>0)
	{
		score+=to_float(user->query(JOB_TABLE[i]["user_mark"]))*JOB_TABLE[i]["weight"];
		if (JOB_TABLE[i]["daily"])
		{
			daily_score+=to_float(user->query(JOB_TABLE[i]["user_mark"]))*JOB_TABLE[i]["weight"];
			types+=1.0;
			scores+=({to_float(user->query(JOB_TABLE[i]["user_mark"]))*JOB_TABLE[i]["weight"]});
		}
	}
	if (types==0.0)
	types=1.0;//常规任务完成次数为0，则daily_score为0，这里设定为1为防止分母为0的情况报错。
	average=daily_score/types;
	
	/*int xiaofeng    = user->query("jobs/completed/xiaofeng") * XIAOFENG_WEIGHT;
    int cisha      = user->query("jobs/completed/mzj") * CISHA_WEIGHT;
    int hubiao      = user->query("jobs/completed/hubiao") * HUBIAO_WEIGHT;
    int task        = user->query("jobs/completed/task") * TASK_WEIGHT;
    int huyidao     = user->query("jobs/completed/huyidao") * HUYIDAO_WEIGHT;


    int score = xiaofeng + cisha + hubiao + task + huyidao;
    //      int score_cost = user->query("jobs/score_cost");                                //已经花掉的score
    int average = score / 5;
    int s = (average - xiaofeng) * (average - xiaofeng) + (average - cisha) * (average - cisha) + (average - hubiao) * (average - hubiao) +
        (average - task) * (average - task) + (average - huyidao) * (average - huyidao);
    int max_s = 1000;*/ //用mapping结构来找出数据计算，否则任务再增加，还要重新修改。Zine
    s = variance(average,scores);
	if (wizardp(this_player()))
	tell_object(this_player(),user->query("id")+"'s VARIANCE is:"+s+".\n");
    if (s > MAX_S)
        s = MAX_S;
    score = score * (MAX_S - s * 4 / 5) / MAX_S;    //偏差越大，对socre的系数越小，最小为 1/5，最大为 1
	bonus_weight=general_weight(user);
	score = to_int(score*bonus_weight);
	if (wizardp(this_player()))
	tell_object(this_player(),user->query("id")+"'s BONUS_WEIGHT is:"+bonus_weight+".\n");
	return score;
}

string tribar_graph(int val, int eff, int max,string color)
{
    return color+ bar_string[0..(val*25/max)*2-1]
    + ((eff > val) ? blank_string[(val*25/max)*2..(eff*25/max)*2-1] : "") + NOR;
}
int show_score(object user)
{
    string line,pronoun;
	int i,max_score = 1,score = cal_score(user);
	mapping *jobs=({});
	for (i=0;i<sizeof(JOB_TABLE);i++)
	{
		if (max_score<user->query(JOB_TABLE[i]["user_mark"])*JOB_TABLE[i]["weight"])
		max_score=to_int(user->query(JOB_TABLE[i]["user_mark"])*JOB_TABLE[i]["weight"]);
		if (JOB_TABLE[i]["daily"])
		jobs+=({(["job_name":JOB_TABLE[i]["job_name"],"score":user->query(JOB_TABLE[i]["user_mark"])*JOB_TABLE[i]["weight"],"color":JOB_TABLE[i]["color"]])});
	}
	if (user==this_player())
	pronoun="你";
	else
	pronoun=(user->query("gender")=="女性")?"她":"他";
	line = HIG"≡━◎综合评价◎━━━━━━━━━━━━━━━━━━━━━━━━≡\n\n"NOR;

    line += pronoun+"的任务综合评价为：" + to_int(score) + "\n";
    line += pronoun+"的各项任务对综合评价的贡献为：\n";
	for (i=0;i<sizeof(jobs);i++)
	line+="<"+sprintf("%|8s",jobs[i]["job_name"])+">"+tribar_graph(to_int(jobs[i]["score"]), max_score, max_score,jobs[i]["color"]) + "\n";
	line += sprintf(HIG"≡━━━━━━━━━━━━━━━━━━━━━━◎北大侠客行◎━━≡\n"NOR);
    write(line);
    return 1;
}


int help(object me)
{
    write(@HELP
指令格式 : jobscore
jobscore <对象名称>                   (巫师专用)

这个指令可以显示你或指定对象的综合任务评价资料。
HELP
       );
    return 1;
}

