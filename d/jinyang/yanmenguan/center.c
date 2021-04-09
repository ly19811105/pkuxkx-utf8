#include <ansi.h>
#include <localtime.h>
inherit __DIR__"yanmenguan.c";
object ob=this_object();
void create()
{
	set("short", "演播室");
	set("long", @LONG
这里是雁门关战役的演播室。
LONG
	);
	setup();
    call_out("get_time",1);
}

void init()
{
    add_action("do_start","start");
}

int rewarding()
{
    object *all_users;
    int reward;
	all_users=users();
    
    for(int i=0;i<sizeof(all_users);i++)
    {
        if (all_users[i]->query_temp("yanmen"))
        {
            reward=(int)all_users[i]->query_temp("yanmen/credit")+10000*(int)all_users[i]->query_temp("yanmen/event");
            tell_object(all_users[i],reward+"\n");
            all_users[i]->delete_temp("yanmen");
        }
    }
}

int end()
{
    string *room=({}),*dir,filename;
    int i,tmp;
    object the_room,ob=this_object();
    object ctrl=load_object("/d/jinyang/yanmenguan/yanmenguan");
    object xiao,mrs_xiao,guanjia,jiading,yahuan;
    ob->delete("is_on");
    dir=get_dir("/d/jinyang/yanmenguan/");
    if (ob->query("yanmen/success"))
    {
        rewarding();
    }
    xiao=ctrl->query("yanmen/xiao");
    mrs_xiao=ctrl->query("yanmen/mrs_xiao");
    guanjia=ctrl->query("yanmen/guanjia");
    jiading=ctrl->query("yanmen/jiading");
    yahuan=ctrl->query("yanmen/yahuan");
    if (xiao)
    {
        destruct(xiao);
    }
    if (mrs_xiao)
    {
        destruct(mrs_xiao);
    }
    if (guanjia)
    {
        destruct(guanjia);
    }
    if (jiading)
    {
        destruct(jiading);
    }
    if (yahuan)
    {
        destruct(yahuan);
    }
    for(i=0;i<sizeof(dir);i++)
	{
		if(file_size("/d/jinyang/yanmenguan/"+dir[i])<=0||sscanf(dir[i],"%s.c",filename)!=1)
		continue;
        tmp = sizeof(dir[i])-1;
        if (dir[i][tmp-1..tmp] != ".c") 
        continue;
		the_room=load_object("/d/jinyang/yanmenguan/"+dir[i]);
        if (the_room->query("road_no"))
        {
            the_room->delete("yanmen");
            the_room->delete("no_reset");
            the_room->delete("no_clean_up");
        }
	}
    return 1;
}

int checking_start_ymg()
{
    object ctrl=load_object("/d/jinyang/yanmenguan/center");
    string *list=ctrl->query("list");
    object xiao=ctrl->query("yanmen/xiao");
    object *all_user;
    int i,rollcall=0;
    object ob=this_object();
    if (!xiao)
    {
        ob->delete("is_on");
        return 1;
    }
    all_user=all_inventory(environment(xiao));
    ob->delete("is_on");
    for (i=0;i<sizeof(all_user);i++)
    {
        if (userp(all_user[i]))
        {
            rollcall+=1;
        }
    }
    if (rollcall<8)
    {
        xiao->goodbye();
        return 1;
    }
}

int start()
{
    string *room=({}),*dir,filename;
    int i,j,tmp;
    object *user,the_room;
    object ob=this_object();
    object xiao,mrs_xiao,guanjia,jiading,yahuan,guandao,yanmenguan;
   // message("chat",HIR"【江湖传闻】萧远山夫妇将路过雁门关，丐帮帮主与少林方丈等一众武林高手决定在路上伏击。\n"NOR,users());
    ob->set("bonus",30);
    ob->set("is_on",1);
    dir=get_dir("/d/jinyang/yanmenguan/");
    for(i=0;i<sizeof(dir);i++)
	{
		if(file_size("/d/jinyang/yanmenguan/"+dir[i])<=0||sscanf(dir[i],"%s.c",filename)!=1)
		continue;
        tmp = sizeof(dir[i])-1;
        if (dir[i][tmp-1..tmp] != ".c") 
        continue;
		the_room=load_object("/d/jinyang/yanmenguan/"+dir[i]);
        if (the_room->query("road_no"))
        {
            the_room->delete("yanmen");
            the_room->set("no_reset",1);
            the_room->set("no_clean_up", 1);
        }
        if (the_room->query("road_no")==18)
        {
            the_room->gene_path();
        }
        
	}
    /*for (i=0;i<sizeof(room);i++)
    {
        the_room=load_object(room[i]);
        if (the_room->query("road_no"))
        {
            the_room->delete("yanmen");
            the_room->set("no_reset",1);
            the_room->set("no_clean_up", 1);
            user=all_inventory(the_room);
            for (j=0;j<sizeof(user);j++)
            {
                if (userp(user[j]))
                {
                    user[j]->delete_temp("yanmen");
                    user[j]->move(__DIR__"guandao");
                    tell_object(user[j],"雁门关战役马上就要开始了，你被转移到安全区域。\n");
                }
            }
        }
        if (the_room->query("road_no")==18)
        {
            the_room->gene_path();
        }
    }*/
    xiao=new(__DIR__"npc/xiaoyuanshan");
    mrs_xiao=new(__DIR__"npc/xiaofuren");
    guanjia=new(__DIR__"npc/guanjia");
    jiading=new(__DIR__"npc/jiading");
    yahuan=new(__DIR__"npc/yahuan");
    guandao=load_object(__DIR__"guandao");
    yanmenguan=load_object(__DIR__"yanmenguan");
    xiao->move(guandao);
    mrs_xiao->move(guandao);
    guanjia->move(guandao);
    jiading->move(guandao);
    yahuan->move(guandao);
    yanmenguan->record_npc(xiao,mrs_xiao,guanjia,jiading,yahuan);
    remove_call_out("checking_start_ymg");
    call_out("checking_start_ymg",600);
    return 1;
}


int get_time()
{
    mixed* timeinfos;
    int hour,minute;
    timeinfos = localtime(time());
    hour = timeinfos[LT_HOUR];
    minute = timeinfos[LT_MIN];
    if (minute>1 && minute<=11)
    {
        //start();
    }
    remove_call_out("get_time");
    call_out("get_time",600);
    return 1;
}

int is_on()
{
    if (ob->query("is_on"))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}



