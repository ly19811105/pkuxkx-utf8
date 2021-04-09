//用以记录导师流派的一些信息以及一些功能实现
//Created by Zine@pkuxkx 2013/1/27

inherit F_DBASE;
inherit F_SAVE;

#include <ansi.h>
#include <math.h>
string query_save_file()
{
    return "/data/guide";
}
string *access_list()
{
	string* list=({"/d/wizard/guider_room.c",});
	return list;
}
int add_app(object guider,string student,int init,int graduate);
void create()
{
    seteuid(getuid());
    restore();
}

int data_create(object guider)//导师数据由最初的写在玩家身上转移到这里
{
	string *list;
	if (!query(guider->query("id")))
	{
		if (arrayp(list=guider->query("guider/apps")))
		{
			for (int i=0;i<sizeof(list);i++)
			add_app(guider,list[i],1,0);
		}
		if (arrayp(list=guider->query("guider/old_apps")))
		{
			for (int i=0;i<sizeof(list);i++)
			add_app(guider,list[i],1,1);
		}
		set(guider->query("id"),guider->query("guider"));
		save();
	}
	return 1;
}
int add_app(object guider,string student,int init,int graduate)//init 为1表示老数据转为新数据格式，则query(guider->query("id"))已经更新
{
	string * guider_data=({});
	if (!graduate)
	set("apps/"+student,guider->query("id"));
	else
	set("old_apps/"+student,guider->query("id"));
	if (init)
	return 1;
	if (!graduate)
	{
		if (arrayp(query(guider->query("id")+"/apps")))
		guider_data=query(guider->query("id")+"/apps");
		if (member_array(student,guider_data)==-1)
		guider_data+=({student});
		set(guider->query("id")+"/apps",guider_data);
	}
	else
	{
		if (arrayp(query(guider->query("id")+"/old_apps")))
		guider_data=query(guider->query("id")+"/old_apps");
		if (member_array(student,guider_data)==-1)
		guider_data+=({student});
		set(guider->query("id")+"/old_apps",guider_data);
	}
	save();
	return 1;
}
int del_app(string student)
{
	string guider,* guider_data=({});
	if (!stringp(guider=query("apps/"+student)))
	return 0;
	delete("apps/"+student);
	save();
	if (!query(guider))
	return 0;
	if (member_array(student,query(guider+"/apps"))==-1)
	return -1;
	if (arrayp(query(guider+"/apps")))
	guider_data=query(guider+"/apps");
	if (member_array(student,guider_data)!=-1)
	guider_data-=({student});
	set(guider+"/apps",guider_data);
	save();
	return 1;
}
int del_oldapp(string student)
{
	string guider,* guider_data=({});
	if (!stringp(guider=query("old_apps/"+student)))
	return 0;
	delete("old_apps/"+student);
	save();
	if (!query(guider))
	return 0;
	if (member_array(student,query(guider+"/old_apps"))==-1)
	return -1;
	if (arrayp(query(guider+"/old_apps")))
	guider_data=query(guider+"/old_apps");
	if (member_array(student,guider_data)!=-1)
	guider_data-=({student});
	set(guider+"/old_apps",guider_data);
	save();
	return 1;
}
int check_valid(object guider,int score_cost)//检查导师命令的积分消耗是否够
{
	if (!query(guider->query("id")))
	return 0;
	if (query(guider->query("id")+"/score")<score_cost)
	return 0;
    return 1;
}

int finish(object guider,int score_cost)//导师命令的积分扣除
{
	if (!query(guider->query("id")))
	return 0;
    add(guider->query("id")+"/score",-score_cost);
	save();
	tell_object(guider,sprintf("因为此项操作，你使用了%d点新手导师信誉度，还有%d点。\n",score_cost,GUIDER_D->guider_score(guider->query("id"))));
	return 1;
}

int check_apprentice(object guider,object app)//检查师徒关系,10M-学生返回1，10M+学生返回2，出师学生返回3
{
	if (SECURITY_D->get_status(guider->query("id")) != "(guider)")
	return 0;
	if (!query(guider->query("id")))
	return 0;
	if (!arrayp(query(guider->query("id")+"/apps")))
	return 0;
	else if (arrayp(query(guider->query("id")+"/apps"))&&member_array(app->query("id"),query(guider->query("id")+"/apps"))!=-1)
	{
		if (app->query("combat_exp")<10000000)
		return 1;
		return 2;
	}
	else if (arrayp(query(guider->query("id")+"/old_apps"))&&member_array(app->query("id"),query(guider->query("id")+"/old_apps"))!=-1)
	return 3;
	else
	return 0;
}

int check_offline_apprentice(object guider,string app)//离线检查师徒关系，学成学生返回2，当前学生返回1.
{
	if (!query(guider->query("id")))
	return 0;
	else if (member_array(app,query(guider->query("id")+"/apps"))==-1&&member_array(app,query(guider->query("id")+"/old_apps"))==-1)
	return 0;
	else if (member_array(app,query(guider->query("id")+"/old_apps"))!=-1)
	return 2;
	else
	return 1;
}

int check_offline_guider(object app,string guider)//离线检查师徒关系，学成学生返回2，当前学生返回1.
{
	if (!query(guider))
	return 0;
	else if (member_array(app->query("id"),query(guider+"/apps"))==-1&&member_array(app->query("id"),query(guider+"/old_apps"))==-1)
	return 0;
	else if (member_array(app->query("id"),query(guider+"/old_apps"))!=-1)
	return 2;
	else
	return 1;
}

int guider_score(string guider)//返回导师现有积分
{
	if (!query(guider))
	return 0;
	return query(guider+"/score");
}

string * app_list(string guider)
{
	if (!arrayp(query(guider+"/apps")))
	return ({});
	return query(guider+"/apps");
}

string * oldapp_list(string guider)
{
	if (!arrayp(query(guider+"/old_apps")))
	return ({});
	return query(guider+"/old_apps");
}

object get_base(object me)
{
	object base;
	object real;
    mapping *ent;
	string owner="";
	mapping app_list;
	if (SECURITY_D->get_status(me->query("id")) == "(guider)")
	owner=me->query("id");
	else if (stringp(me->query("group_owner")))
	owner=me->query("group_owner");
	else
	{
		if (stringp(query("apps/"+me->query("id"))))
		owner=query("apps/"+me->query("id"));
		if (owner=="")
		if (stringp(query("old_apps/"+me->query("id"))))
		owner=query("old_apps/"+me->query("id"));
	}
	if (owner!="")
	{
		real=load_object("/d/parties/public/obj/real");
		ent=real->real_estate();
		for (int i=0;i<sizeof(ent);i++)
		{
			if (ent[i]["owner"]==owner)
			{
				base=load_object(ent[i]["entry"]);
				break;
			}
		}
	}
	return base;
}
object get_base_by_id(string me)
{
	object pl=find_player(me);
	return get_base(pl);
}
int set_group_name(object guider,string group_name)
{
	set(guider->query("id")+"/group_name",group_name);
	return 1;
}

string is_app(string app)
{
	string result="";
	mapping app_list;
	if (SECURITY_D->get_status(app) == "(guider)")
	result="is_GUIDER";
	else
	{
		app_list=query("apps");
		if (stringp(app_list[app]))
		result=app_list[app];
		if (result=="")
		app_list=query("old_apps");
		if (stringp(app_list[app]))
		result=app_list[app];
	}
	return result;
}

int group_level(object guider)
{
	object ob;
	if (SECURITY_D->get_status(guider->query("id")) != "(guider)")
	return -1;
	if (!ob=get_base(guider))
	return -1;
	return ob->query("group_level");
}

int same_group(object ppa,object ppb)
{
	if (ppa==ppb&&(is_app(ppa->query("id"))||SECURITY_D->get_status(ppa->query("id")) == "(guider)"))	return 1;//同人
	if (SECURITY_D->get_status(ppb->query("id")) == "(guider)")
	{
		if (check_apprentice(ppb,ppa)!=0)
		return 1;
	}
	else
	{
		if (is_app(ppb->query("id"))==ppa->query("id"))
		return 1;
	}
	if (is_app(ppa->query("id"))==is_app(ppb->query("id"))&&is_app(ppa->query("id"))!=""&&is_app(ppa->query("id"))!="is_GUIDER")	return 1;//同门师兄弟
	if (get_base(ppa)==get_base(ppb)&&objectp(get_base(ppa)))	return 1;//同门客卿和学生
	return 0;
}

//以下内容为admin以上级别巫师操作
string add_score(string guider,int score)
{
	object pl;
	if (SECURITY_D->get_status(guider) != "(guider)") return guider+" is not a valid guider.\n";
	if (!pl=find_player(guider))	return guider+" has not been found in the current PKU world.\n";
	if (!query(guider))	return guider+"'s data saving file has not been created.\n";
	add(guider+"/score",score);
	log_file("wiz/guider",sprintf("%s(%s) gave %s(%s) %d guider credit(s) on %s\n",this_player()->name(1), geteuid(this_player()), pl->name(1), geteuid(pl), score,ctime(time()) ) );
	save();
	return sprintf("%s(%s) give %s(%s) %d guider credit(s) on %s\n",this_player()->name(1), geteuid(this_player()), pl->name(1), geteuid(pl), score,ctime(time()) );
}

int manual_data_create(string guider)//导师数据由最初的写在玩家身上转移到这里
{
	string *list;
	object pl=present(guider,environment(this_player()));
	if (!query(pl->query("id")))
	{
		if (arrayp(list=pl->query("guider/apps")))
		{
			for (int i=0;i<sizeof(list);i++)
			add_app(pl,list[i],1,0);
		}
		if (arrayp(list=pl->query("guider/old_apps")))
		{
			for (int i=0;i<sizeof(list);i++)
			add_app(pl,list[i],1,1);
		}
		set(pl->query("id"),pl->query("guider"));
		save();
	}
	return 1;
}

string show_group_detail(string guider,int authority)
{
	string msg="",*app_list,*oldapp_list;
	object pl,*apps=({}),*old_apps=({});
	int i,*app_exps=({}),*oldapp_exps=({});
	if (!query(guider))
	{
		return msg;
	}
	app_list=app_list(guider);
	oldapp_list=oldapp_list(guider);
	for (i=0;i<sizeof(app_list);i++)
	{
		if (pl=find_player(app_list[i]))
		{
			apps+=({pl});
			app_exps+=({pl->query("combat_exp")});
		}
	}
	for (i=0;i<sizeof(oldapp_list);i++)
	{
		if (pl=find_player(oldapp_list[i]))
		{
			old_apps+=({pl});
			oldapp_exps+=({pl->query("combat_exp")});
		}
	}
	if (sizeof(apps)>0)
	{
		if (authority==1)
			msg+="当前学生共有"+sizeof(apps)+"人，平均经验为"+ave(app_exps)+"点。其中经验最高为"+max(app_exps)+"，经验最低为"+min(app_exps)+"。\n";
		else
			msg+="当前学生共有"+sizeof(apps)+"人，平均经验为"+ave(app_exps)+"点。\n";
	}
	else
		msg+="当前没有学生在线。\n";
	if (sizeof(old_apps)>0)
	{
		if (authority==1)
			msg+="出师学生共有"+sizeof(old_apps)+"人，平均经验为"+ave(oldapp_exps)+"点。其中经验最高为"+max(oldapp_exps)+"，经验最低为"+min(oldapp_exps)+"。\n";
		else
			msg+="出师学生共有"+sizeof(old_apps)+"人，平均经验为"+ave(oldapp_exps)+"点。\n";
	}
	else
		msg+="当前没有出师学生在线。\n";
	return msg;
}

int delete_guider(string guider)
{
	int i;
	string *apps=({});
	object real=load_object("/d/parties/public/obj/real");
    mapping *ent;
	if (!query(guider))
	return notify_fail("无此人导师数据。\n");
	apps=app_list(guider);
	if (sizeof(apps))
	{
		for (i=0;i<sizeof(apps);i++)
		del_app(apps[i]);
	}
	apps=oldapp_list(guider);
	if (sizeof(apps))
	{
		for (i=0;i<sizeof(apps);i++)
		del_oldapp(apps[i]);
	}
	delete(guider);
	save();
	real=load_object("/d/parties/public/obj/real");
	ent=real->real_estate();
	for (i=0;i<sizeof(ent);i++)
	{
		if (ent[i]["owner"]==guider)
		{
			ent[i]["owner"]="N/A";
			ent[i]["entry_code"]="N/A";
			real->save_entry(ent);
			real->save();
			break;
		}
	}
	return 1;
}