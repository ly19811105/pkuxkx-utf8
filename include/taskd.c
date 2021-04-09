//taskd.c 
//Made by jason for pkuxkx 2000/12/7

inherit F_DBASE;
#include <ansi.h>
#include <mudlib.h>

int start_task(object);
int dump_task();
string locate_obj(object,string);

mapping task_list=([
	"/task/obj/baojia":10,
	"/task/obj/guihun_miji":20,
]);

object *task_items=({});
void create()
{
	set("channel_id","任务精灵");
	seteuid(getuid());
	start_task(this_object());
}

int start_task(object me)
{
	//be sure all the task_item ,task_locate is ok
	//make this code in hurry ,so no much bug fix
	object where,who,task_item,*all_user,task_room;
	string file1,file2,*wr,describe,*key,*item_list,room;
	int j=0,d_size,d_begin;
	if(task_room=find_object("/task/task_room"))
		destruct(task_room);	
	task_room=load_object("/task/task_room");
	task_items=({});
	CHANNEL_D->do_channel(this_object(),"chat","系统即将分配任务！\n");
	/*for(int i=0;i<sizeof(all_user);i++)
	{
		all_user[i]->remove_all_enemy();
		all_user[i]->start_busy(2);
	}
	*/
	file1=read_file("/task/task_location.dat");
	
	//file2=read_file("/task/task_npc.dat");
	wr=explode(file1,"\n");
	item_list=keys(task_list);
	for(int i=0;i<sizeof(task_list);i++)
	{
		
		if(!task_item=new(item_list[i])) {
		write("new error\n");
		continue;
		}
		room=wr[random(sizeof(wr))];
		if(!where=load_object(room+".c")) {
			write("load room error\n");
			continue;
		}
			
		if(!task_item->move(where)) {
	 		write("move error\n");
	 		continue;
	 	}
	 	
	 	//task_items[i]=task_item;
	 	
	}
	CHANNEL_D->do_channel(this_object(),"chat","系统分配任务完成！\n");
	remove_call_out("start_task");
	call_out("start_task",1800,this_object());
	return 1;
}

int dump_task()
{
	object task;
	write(HIB"\t\t\t"+CHINESE_MUD_NAME+"任务榜\n\n\n"NOR);
	for(int i=0;i<sizeof(task_list);i++)
	{
		if(!task=load_object(keys(task_list)[i]+".c")) {
			write("load error\n");
			continue;
		}
		
		write("\t\t\t"+task->name()+"");
		//write("\t\t\t"+task->query("owner/name")+"的"+task->name()+"");
		if(task->query("done"))
			write("(已完成)\n");
		else
			write("\n");
	}
	return 1;
}

string locate_obj(object me,string str)
{
	string *task_items=keys(task_list),des;
	object item;
	int flag=0,size;
	str+="/d/task/obj/";
	for(int i=0;i<sizeof(task_items);i++)
	{
		if(str=task_items[i]) break;
		flag=1;
	}
	if(!flag) {
		write("定位错误！\n");
		return "";
	}
	if(!item=load_object(str+".c")) {
		write("error\n");
		return "";
	}
	if(item->query("done")) {
		write(item->name()+"的任务已经完成了。\n");
		return "";
	}
	des=item->query("long");
	size=sizeof(des);
	des=des[size/2..size/4];
	des=item->name()+"目前在有如下描述的地方：\n"+des;
	return des+"\n";
	
}



	
	