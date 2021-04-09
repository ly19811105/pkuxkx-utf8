//用来给玩家投票的。具备保存功能
//open 投票标题
//输入投票描述

//l npc查看投票描述。如果是投票开启人，可以看到投票结果
//vote
//开始投票，显示描述，进入输入界面。每行是一个投票选项。

//将来有空可以仿照bbs做全面的投票系统

inherit NPC;
inherit F_SAVE;
#include <ansi.h>

mapping votes = ([]);
string topic;
string desc;
string starter;

string query_save_file()
{
	if(!query("startroom")) return "";
	return "/data/vote/npc_"+crypt(query("startroom"),"vote")+".o";
}

void create()
{
	set_name("小刀",({"lzkd npc"}));
    set("title",HIW"活动"HIR"之"HIY"虎"NOR);
	set("long",
	"这是北侠的活动之虎，精华之王，技术高手，小刀。\n"
	);

    set("gender","男性");
    set("age",25);
    set("per",30);
    set("no_steal",1);
    set("no_beg",1);
	//tbd
    carry_object("/clone/cloth/male7-cloth")->wear();    
	setup();    
    set("allowed",({"lzkd","howoldareyou"}));        
	restore();
}

void init()
{
    if(member_array(this_player()->query("id"),query("allowed")) != -1 || wizardp(this_player()))
    {        
		add_action("do_open","open");
		add_action("do_close","close");
    }
    add_action("do_look","look");
	add_action("do_vote","vote");
}

int sort_votes(mixed* item1, mixed* item2)
{
	string candidate1 = (string)item1;
	string candidate2 = (string)item2;
	if(votes[candidate1] > votes[candidate2]) return 1;
	if(votes[candidate1] < votes[candidate2]) return -1;
	return 0;
}
int do_look(string arg)
{
	object pl;
	string* candidate;
	int* number;
	int i;
	
	if(!id(arg)) return 0;
	"/cmds/std/look.c"->mudlook_living(this_player(),this_object());
	pl = this_player();
	if(sizeof(topic) > 0)
	{
		write("目前正在进行的投票是:\n");
		write(topic+"\n");
		write(desc+"\n");
		write("发起者是:"+starter+"\n");
		write("请使用vote命令开始投票。每行是一个投票选项。每个人只能投一次，不能修改，请珍惜机会。\n");
	}
	else
	{
		write("目前没有任何投票进行中。\n");
		return 1;
	}
	if(member_array(this_player()->query("id"),query("allowed")) != -1 || wizardp(this_player()))
	{
		write("目前票数统计如下：\n");
		candidate = keys(votes);
		number = values(votes);
		candidate = sort_array(candidate,(:sort_votes:));
		for(i=0;i<sizeof(candidate);i++)
		{
			printf("%20s - %5d\n",candidate[i],votes[candidate[i]]);
		}
	}
	return 1;
}

int do_vote()
{
	write("请输入您认可的玩家id。每行一个，不超过十个。\n");
	this_player()->edit( (: call_other, __FILE__, "vote_user",this_player() :) );
	return 1;
}

void vote_user(object me, string str)
{
	 string* candidates = explode(str,"\n");
	 int i =0;
	 string id;
	 object ob;
	 int fail = 0;
	 
	 for(i=0;i<sizeof(candidates);i++)
	 {	 
		if(i==10) break;
		id = candidates[i];
        ob = new(LOGIN_OB);
        ob->set("id", id);
        if( !ob->restore() ) 
		{
			write(id+"不存在！\n");
			fail = 1;
			break;
		}		
	 }
	 if(fail == 1)
	 {
		write("请检查你的输入\n");
		return;
	 }
	 for(i=0;i<sizeof(candidates);i++)
	 {	 
		if(i==10) break;		
		id = candidates[i];
		if(undefinedp(votes[id])) votes[id] = 1;
		else votes[id] = votes[id] + 1;
	 }	 
	 write("谢谢，你已经投票成功。\n");
	 save();
}

int do_open(string arg)
{
	if(sizeof(topic) > 0)
	{
		write("目前尚有投票进行中！请先close投票\n");
		return 1;
	}
	topic = arg;
	starter = this_player()->query("id");
	write("请输入对这次投票的描述。\n");
	this_player()->edit( (: call_other, __FILE__, "input_desc", this_player() :) );
	return 1;
}

int do_close()
{
	topic = "";
	desc = "";
	votes = ([]);
	write("投票已经关闭\n");
	return 1;
}

void input_desc(object me, string str)
{
	 seteuid(getuid());	
	 desc = str;
	 write(desc);
	 write(desc);
	 write("谢谢，投票开启成功\n");
	 save();
}

void unconcious()
{
   fullme();
   return;
}

void die()
{
   fullme();
   return;
}


