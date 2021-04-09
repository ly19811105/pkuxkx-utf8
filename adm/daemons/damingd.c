#include <ansi.h>
string daming_positions="",cmd,parameter,*commands = ({});
int caution=0;
string *yingtian_places=({});

void rehash();
void get_daming_positions();

void create()
{
	rehash();
	get_daming_positions();
}
void rehash()
{
	string *cmds,dir="/d/yingtianfu/neicheng/commands/",filename;
	cmds = get_dir(dir);
	for (int i=0;i<sizeof(cmds);i++ )
	{
		if(file_size("/d/yingtianfu/neicheng/commands/"+cmds[i])>0&&strsrch(cmds[i],".c")!=-1)
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
void get_daming_positions()
{
	object ob,pl;
    mapping *titles;
    string line=HIG"--------------------------------------------------------------------------------------------------\n"NOR;
	string col=HIG"|"NOR,msg=sprintf("\n%|122s%s%s",HBRED+HIW+"大明高级官员列表\n"+NOR,"\n",line),*msg_wen=({}),*msg_wu=({});
    int i;
    if (!ob=load_object("/d/yingtianfu/neicheng/shengzhi"))
    {
        daming_positions="吏部的人正忙着年末岁考，暂时无法受理你的查询。\n";
		return;
    }
    ob->restore();
    titles=ob->query("give_titles");
    if (!titles)
    {
        daming_positions="吏部的人正忙着年末岁考，暂时无法受理你的查询。\n";
		return;
    }
    for (i=0;i<sizeof(titles);i++)
    {
        if (titles[i]["owner"]!="")
        {
            if (titles[i]["pro"]=="文")
            {
                msg_wen+=({sprintf("%s%-50s%s",col,HIB+titles[i]["title"]+NOR,col)+sprintf("%|12s%s",titles[i]["owner"],col)});
            }
            else
            {
                msg_wu+=({sprintf("%s%-50s%s",col,HIR+titles[i]["title"]+NOR,col)+sprintf("%|12s%s",titles[i]["owner"],col)});
            }
        }
    }
	if (sizeof(msg_wen)>sizeof(msg_wu))
	{
		for (i=0;i<sizeof(msg_wu);i++)
		{
			msg+=msg_wen[i]+msg_wu[i]+"\n";
		}
		for (i=sizeof(msg_wu);i<sizeof(msg_wen);i++)
		{
			msg+=msg_wen[i]+sprintf("%s%-50s%s%|12s%s",col,HIR+""+NOR,col,"",col)+"\n";
		}
	}
	else if (sizeof(msg_wu)>sizeof(msg_wen))
	{
		for (i=0;i<sizeof(msg_wen);i++)
		{
			msg+=msg_wen[i]+msg_wu[i]+"\n";
		}
		for (i=sizeof(msg_wen);i<sizeof(msg_wu);i++)
		{
			msg+=sprintf("%s%|48s",col," ")+msg_wu[i]+"\n";
		}
	}
	else
	{
		for (i=0;i<sizeof(msg_wen);i++)
		{
			msg+=msg_wen[i]+msg_wu[i]+"\n";
		}
	}
	msg+=line;
    daming_positions=msg;
    return;
}
void gene_places()
{
	string *dir,filename;
	int tmp;
	object where,ob=load_object("/d/yingtianfu/neicheng/shengzhi");
	dir=get_dir("/d/yingtianfu/neicheng/");
	if (sizeof(yingtian_places) > 0)
	{
		printf("%d\n",sizeof(yingtian_places));
		return;
	}
	ob->restore();
	if (arrayp(ob->query("ytf_task_place")))
	{
		yingtian_places=ob->query("ytf_task_place");
	}
	else
	{
		for(int i=0;i<sizeof(dir);i++)
		{
			if(file_size("/d/yingtianfu/neicheng/"+dir[i])<=0||sscanf(dir[i],"%s.c",filename)!=1)
			continue;
			tmp = sizeof(dir[i])-1;
			if (dir[i][tmp-1..tmp] != ".c") continue;
			if(catch(call_other("/d/yingtianfu/neicheng/"+dir[i],"??"))) continue;
			where = load_object("/d/yingtianfu/neicheng/"+dir[i]);
			if (!objectp(where)) continue;
			if (!where->isroom()) continue;
			if (where->query("no_task")) continue;
			if (where->query("real_dark")) continue;
			if (!where->is_yingshan()) continue;      
			yingtian_places+=({base_name(where)});                   
		}
		ob->set("ytf_task_place",yingtian_places);
		ob->save();
	}
}

string *all_command()
{
	return commands;
}
string get_cmd()
{
	return "/d/yingtianfu/neicheng/commands/"+cmd;
}
string get_parameter()
{
	return parameter;
}
int warning()
{
	return caution;
}
string *ytf_task_place()
{
	if (sizeof(yingtian_places) == 0)
	gene_places();
	return yingtian_places;
}
string positions()
{
	if (daming_positions="")
	get_daming_positions();
	return daming_positions;
}
int reset_positions()
{
	daming_positions="";
}