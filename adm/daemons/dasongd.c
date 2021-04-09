inherit "/d/song/config/promotion.c";
#include <localtime.h>
string dasong_positions="",cmd,parameter,*commands = ({});
int caution=0;
void rehash();
void get_dasong_positions();
int get_time();
void create()
{
	rehash();
	get_dasong_positions();
	get_time();
}
void rehash()
{
	string *cmds,dir="/d/song/commands/",filename;
	cmds = get_dir(dir);
	for (int i=0;i<sizeof(cmds);i++ )
	{
		if(file_size("/d/song/commands/"+cmds[i])>0&&strsrch(cmds[i],".c")!=-1)
		commands+=({replace_string(cmds[i],".c","")});
	}
}
string find_command(string arg)
{
	string *para;
	caution=0;
	for (int i=0;i<sizeof(commands);i++)
	{
		if (strsrch(arg,commands[i])!=-1)
		{
			cmd=commands[i];
			if (arg==cmd)
			{
				parameter="";
				return "";
			}
			para=explode(arg,cmd);
			parameter=replace_string(para[0]," ","",1);
			if (member_array(para[0],commands)!=-1)
			caution=1;
			break;
		}
	}
}
void get_dasong_positions()
{
    dasong_positions="/d/song/record/positions"->get_dasong_positions();
    return;
}

string *all_command()
{
	return commands;
}
string get_cmd()
{
	if (file_size("/d/song/commands/"+cmd+".c")>0)
	return "/d/song/commands/"+cmd;
	return "/d/song/commands/query";
}
string get_parameter()
{
	return parameter;
}
int warning()
{
	return caution;
}
string positions()
{
	if (dasong_positions="")
	get_dasong_positions();
	return dasong_positions;
}
int reset_positions()
{
	dasong_positions="";
}
//计时操作内容

object *song_players()
{
	object *ob;
	ob = filter_array(children(USER_OB), (: userp :));
    ob = filter_array(ob, (: environment :));
    ob = filter_array(ob, (: $1->query("song/pro"):) );
    ob = filter_array(ob, (: living :));
	for (int i=0;i<sizeof(ob);i++)
	{
		if (ob[i]->query("env/NoSongList")&&wizardp(ob[i]))
			ob-=({ob[i]});
	}
	return ob;
}
int get_guanyin_from_players()
{
    return "/d/song/record/other"->get_guanyin_from_players();
}
int promote_list(object me)
{
	return "/d/song/record/other"->promote_list(me);
}
int multi_record(object me,int salary,string type,int flag)
{
	return "/d/song/record/other"->multi_record(me,salary,type,flag);
}
int record_npc(object npc,string mark)
{
	if (environment(npc))
	{
		this_object()->set("song_npcs/"+mark,npc);
		save();
	}
}
int task_finish(object me,int reward)
{
	int n;
	if (reward>=0)
	{
		if (get_my_pin(me)!=1)
		n=reward;
		else
		n=reward*3/2;
		tell_object(me,"你的大宋功勋度增加了"+chinese_number(n)+"点。\n");
	}
	else
	{
		n=reward;
		tell_object(me,"你的大宋功勋度损失了"+chinese_number(-n)+"点。\n");
	}
	me->add("song/credit",n);
	me->delete_temp("songtasks");
	return 1;
}

int get_time()
{
	mixed* timeinfos= localtime(time());
	int hour,minute,wday;
	hour = timeinfos[LT_HOUR];
	minute = timeinfos[LT_MIN];
	wday= timeinfos[LT_WDAY];
	//"/d/song/record/other"->guanyin_players();
	"/d/song/record/other"->syn_record_daemon();
	"/clone/board/dasong_jianyuan_b.c"->give_players_credit();
	if (hour%2==0)
	"/d/song/record/other"->salary_me();
	if (minute>31 && minute<=41)
	"/d/song/record/other"->tell_promote();
	if (hour%6==0&&minute>41 && minute<=51)
	"/d/song/record/other"->get_officer();
	//if (wday==5&&hour==21&&minute>0 && minute<=10)
	//"/d/song/tasks/nanzheng"->start();
	remove_call_out("get_time");
	call_out("get_time",600);
	return 1;
}

int cdtime(object me)
{
	int cdtime=7200,times=me->query("song/task_times");
	mapping discount=([0:0.5,1:0.75,]);
	if(me->query("class") == "officer"||!get_my_pin(me))
	cdtime+=9999;
	else
	cdtime+=1800*get_my_pin(me);
	if (me->query("song/pro")=="宦")
	cdtime-=1800;
	if ((times==0||times==1)&&get_my_pin(me)!=1)
	cdtime=to_int(to_float(cdtime)*discount[times]);
	return cdtime;
}

void save_time(string type)//保存某事件的时间节点
{
	object other=load_object("/d/song/record/other");
	if (!stringp(type))
	return;
	other->set("time_records/"+type,time());
	other->save();
}
int load_time(string type)
{
	object other=load_object("/d/song/record/other");
	if (other->query("time_records/"+type))
	return other->query("time_records/"+type);
	return -1;
}
int title_pursued(object me,string title)
{
	if (!me||!title)
	return 1;
	if (me->query("song/title")&&strsrch(me->query("song/title"),title)!=-1)
	return 1;
	me->set_temp("song/hor_promote",3);
	me->set_temp("song/hor_promote_title",title);
	position_me(me);
	return 1;
}
int title_pursue(object me,string title)
{
	int time=7200;
	if (jilu_pin(me)<=7)
	time=3600;
	if (query("fast_track"))
	time=10;
	call_out("title_pursued",time,me,title);
	return 1;
}
int check_in(object me,int flag)
{
	mapping *online_users=({}),new_user=(["name":"","pro":"","title":"","pin":"","deco":"","jue":"","player":0,"credit":0]);
	if (!me->query("song/pro"))
	return 1;
	if (arrayp(query("online_users")))
	online_users=query("online_users");
	new_user="/d/song/commands/players"->record_newuser(me);
	online_users+=({new_user});
	set("online_users",online_users);
	if (flag==-1)
	return 1;
	return "/d/song/record/other"->guanyin_player(me);
}
mapping *get_online_users()
{
	mapping *online_users=({});
	if (arrayp(query("online_users")))
	online_users=query("online_users");
	for (int i=0;i<sizeof(online_users);i++)
	{
		if (!online_users[i]["player"])
		online_users-=({online_users[i]});
	}
	set("online_users",online_users);
	if (sizeof(online_users))
	return online_users;
	return ({});
}