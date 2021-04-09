// autosaved.c
// file:                Autosave daemon
// creator:     ken
// date:                98-2-23

// for autosave players data file.
//clean_mud()部分在 的物品回收在mudos已经执行过，清除发呆断线玩家在/clone/user/user.c inherit/char/char.c执行过,所以注释掉 Zine 2014/4/27
#include <ansi.h>
#include <user.h>
#pragma save_binary

#define FORUM_MSG "/adm/etc/forumchange"
#define FORUM_MSG_WIZCHANNEL "/adm/etc/forumchange_wizchannel"
#define FORUM_MSG_TEMP "/adm/etc/forumchangetemp"
#define FORUM_MSG_WIZCHANNEL_TEMP "/adm/etc/forumchange_wizchanneltemp"
#define FORUM_MSG_WIZ "/adm/etc/forumchange_wiz"
#define FORUM_MSG_TEMP_WIZ "/adm/etc/forumchangetemp_wiz"
#define FORUM_MANTIS "/adm/etc/mantischange"
#define FORUM_MANTIS_TEMP "/adm/etc/mantischange_temp"
#define FORUM_MANTIS_NOTE "/adm/etc/mantisnote_change"
#define FORUM_MANTIS_NOTE_TEMP "/adm/etc/mantisnote_change_tep"
#define WIKI_MSG "/adm/etc/wikichange"
#define WIKI_MSG_TEMP "/adm/etc/wikichangetemp"
#define HELPNEW_LST "/log/helpnew/helpnew_lst"
#define HELPNEW_BAD_LST "/log/helpnew/helpnew_bad_lst"
#define HELPNEW_COUNT "/log/helpnew/helpnew_count"
#define HELPNEW_MONTH_LST "/log/helpnew/helpnew_month_list"
#define HELPER_OF_THE_WEEK "/log/helpnew/helper_of_the_week"
#define HELPER_OF_THE_MONTH "/log/helpnew/helper_of_the_month"

inherit F_DBASE;

void auto_save();

mapping *list; //helpnew 投票计数
int destnum = 0;
int max_destnum = 2000;
int add_destnum() { return ++destnum; }
int query_destnum() { return destnum; }
int query_max_destnum() { return max_destnum; }
int is_destnum_limit() {return destnum>=max_destnum?1:0;}
int set_max_destnum(int n) { return max_destnum = n; }

void create()
{
		object npc;
		
        seteuid(ROOT_UID);
        set("channel_id", "内存精灵");
        CHANNEL_D->do_channel( this_object(), "sys", "自动存盘系统已经启动。\n");
        call_out("auto_save", 40);
		set("number",1);
//	    npc = load_object("/d/wizard/npc/god.c");
//	    npc->set("shutdown_time",7200);
//	    npc->move("/d/city/idleroom");
//	    npc->shut_down();		
}
void do_each_save(object user)
{
			object	link_ob;
			if (!objectp(user)) return;
			if (user->query("env/no_autosave")) return;
			link_ob = user->query_temp("link_ob");
			if (objectp(link_ob))
		        if( (int)link_ob->save() && (int)user->save() ) {    
					tell_object(user,"你的档案已由系统自动保存。\n");
				} else tell_object(user,HIR"你的档案保存失败，请与巫师联系查看原因。\n"NOR);
			else tell_object(user,HIR"你不是经由正常连线进入，不能储存。\n"NOR);
}
void auto_save()
{
        int i, mem;
        object *ob, *n, *user, link_ob, where;
        string id;
/*
        seteuid(getuid());
        ob=users();
        i=sizeof(ob);
        reclaim_objects();
        for( i=0;i<sizeof(ob);i++) {
                id = (string) ob[i]->query("id");
                if (!id) continue;
                if(!environment(ob[i]) )        continue;
                if( !objectp(link_ob = ob[i]->query_temp("link_ob")) ) continue;
                if( (int)link_ob->save() && (int)ob[i]->save() )
message("channel:chat", HIG"【存盘】您的档案已经自动存盘。\n"NOR,ob[i]);
                else
message("channel:chat", HIG"【存盘】您的档案已经自动存盘失败，请与巫师联系。\n"NOR,ob[i]);
        }
*/
	//自动存档
         if ((int)(query("number")%6)==0)
	{
        /*user = users();
        message("system", HIR "\n全部玩家自动存档．．．", users());
        for(i=0; i<sizeof(user); i++)
		{
                         call_out("do_each_save",i,user[i]);
		}// do_each_save效用不大，将由玩家自行执行backup。 
		message("system", HIG "．．．存档完毕 \n" NOR, users());
         shout(HIG"建议经常使用save及backup命令保存和备份档案。\n"NOR);	*/ 
	}
	add("number",1);
        remove_call_out("auto_save");
        call_out("auto_save", 600);
        call_out("forum_msg",50);
        call_out("wiki_msg",30);
        call_out("clean_mud",10);

       //检查备份档案是否完成，同时检查helpnew投票结果
	if (file_size("/adm/etc/backupok") != -1)
	{
		rm("/adm/etc/backupok");
                shout(HIW"玩家档案及系统文件备份完成！\n"NOR);
//                call_out("check_helpnew",1);
        }    
}

//清理物件和断线、发呆超时以及无环境玩家
void clean_mud()
{
	object  *ob_list, *users;
	int old_size,i,room_number=0,item_number=0;
	
    // reset物品数量统计
    if (destnum>0)
    {
        CHANNEL_D->do_channel(this_object(), "sys", sprintf("上一次reset共清除 %d 个物件。", destnum));
        destnum = 0;
    }
    return;
/*    
    //cleanupmud
    //清除变数
    CHANNEL_D->do_channel( this_object(), "sys",
    sprintf("系统自动清除 " + reclaim_objects() + " 个变数。"));

    ob_list = objects();
    old_size = sizeof(ob_list);
    reset_eval_cost();
    for(i=old_size-1; i>=0; i--)
    {
        if( ob_list[i] && inherits(ITEM, ob_list[i]))
        {
            item_number++;
        }
        else if( ob_list[i] && inherits(ROOM, ob_list[i]))
        {
            room_number++;
        }
        if( ob_list[i] &&( inherits(ITEM, ob_list[i])||inherits(NPC, ob_list[i])) && clonep(ob_list[i]) && !environment(ob_list[i]) )
                        destruct(ob_list[i]);
    }
    ob_list -= ({ 0 });
    CHANNEL_D->do_channel(this_object(), "sys", sprintf("共有%d个房间，%d个活物(%d个心跳物)，%d个item，清除 %d 个物件 of %d。", room_number, sizeof(livings()), sizeof(heart_beats()), item_number, old_size - sizeof(ob_list), old_size));

	//清理断线、发呆超时以及无环境玩家
	users = children(USER_OB);
	old_size = sizeof(users);
	for (i=old_size-1;i>=0;i--)
	{
		if (!environment(users[i])&&clonep(users[i]))
		{
			CHANNEL_D->do_channel(this_object(), "sys", "清理无环境玩家" + users[i]->name()+"("+users[i]->query("id")+")\n");
			if (users[i]->query_temp("link_ob"))
				destruct(users[i]->query_temp("link_ob"));
			destruct(users[i]);
		} else
		if( interactive(users[i]) && !wizardp(users[i]) && 
		    ( ( query_idle(users[i]) > IDLE_TIMEOUT && 
		        users[i]->query("noDeadNetnoIdle") != "Pkuxkx" ) ||
		      ( query_idle(users[i]) > FOREVER_TIME && 
		        users[i]->query("noDeadNetnoIdle") == "Pkuxkx" ) ) )
		{
			CHANNEL_D->do_channel(this_object(), "sys", "清理发呆超时玩家" + users[i]->name()+"("+users[i]->query("id")+")\n");
			log_file("wiz/clean_user", sprintf("%s清理发呆超时%d秒玩家%s(%s)\n",
			ctime(time()),query_idle(users[i]),users[i]->name(),users[i]->query("id")));
			users[i]->start_busy(0);
			users[i]->user_dump(DUMP_IDLE);
			if (users[i])
			{
				if (users[i]->query_temp("link_ob"))
					destruct(users[i]->query_temp("link_ob"));
				destruct(users[i]);
			}
		} else
		if (users[i]->query_temp("netdead"))
			if ( ( ( time()-users[i]->query_temp("netdead") > NET_DEAD_TIMEOUT &&
				       users[i]->query("noDeadNetnoIdle") != "Pkuxkx" ) || 
				     ( time()-users[i]->query_temp("netdead") > FOREVER_TIME &&
				       users[i]->query("noDeadNetnoIdle") == "Pkuxkx" ) ) && !wizardp(users[i]))
		{
			CHANNEL_D->do_channel(this_object(), "sys", "清理断线超时玩家" + users[i]->name()+"("+users[i]->query("id")+")\n");
			log_file("wiz/clean_user", sprintf("%s清理断线超时%d秒玩家%s(%s)\n",
			ctime(time()),(time()-users[i]->query_temp("netdead")),users[i]->name(),users[i]->query("id")));
			users[i]->start_busy(0);
			users[i]->user_dump(DUMP_NET_DEAD);
			if (users[i])
			{
				if (users[i]->query_temp("link_ob"))
					destruct(users[i]->query_temp("link_ob"));
				destruct(users[i]);
			}			
		}
	}
    users -= ({ 0 });
    CHANNEL_D->do_channel(this_object(), "sys", sprintf("清除 %d 个发呆、断线超时未退出的玩家。\n", old_size - sizeof(users)));
    return;*/
}

//读取论坛发贴回贴信息
void forum_msg()
{
		string lines,msg;
		int i,j;
		string *line;
		object imd;
		mapping note;
		
		if (file_size(FORUM_MSG) != -1)	 //文件不存在，间隔时间内无人发贴
		{
				
				if (rename(FORUM_MSG,FORUM_MSG_TEMP)) //文件改名失败
				{
						CHANNEL_D->do_channel( this_object(), "sys", "论坛更新信息文件" + FORUM_MSG + "重命名失败。\n");
						return;
				}
				
				lines = read_file(FORUM_MSG_TEMP);
				if (lines)
				{
		           line = explode(lines, "\n");
		           i = 0;
		           msg = "";
		           while ((i+1)<sizeof(line))
		           {
		           			if (line[i]=="" || line[i+1] == "")
		           				return;
		           			msg += "听说" + sprintf("%|14s",line[i]) + "在北侠论坛发表了一篇名为『" + line[i+1] + "』的大作！\n";
		           			i = i + 2;
		           }
					set("channel_id", "论坛精灵");
			        imd = load_object("/adm/daemons/im_d");
			        imd->set("channel_id","QQ精灵");
		    		CHANNEL_D->do_channel( this_object(), "qq",msg);
					//论坛信息不再转发至qq
		    		//imd->process_send_msg(imd,"mud",msg);
			        set("channel_id", "内存精灵");
				}
				if (!rm(FORUM_MSG_TEMP)) //文件删除失败
				{
						CHANNEL_D->do_channel( this_object(), "sys", "论坛更新信息临时文件" + FORUM_MSG_TEMP + "删除失败。\n");
						return;
				}				
		}

		if (file_size(FORUM_MSG_WIZCHANNEL) != -1)	 //wizboard文件不存在，间隔时间内无人发贴
		{
				
				if (rename(FORUM_MSG_WIZCHANNEL,FORUM_MSG_WIZCHANNEL_TEMP)) //文件改名失败
				{
						CHANNEL_D->do_channel( this_object(), "sys", "论坛更新信息文件" + FORUM_MSG + "重命名失败。\n");
						return;
				}
				
				lines = read_file(FORUM_MSG_WIZCHANNEL_TEMP);
				if (lines)
				{
		           line = explode(lines, "\n");
		           i = 0;
		           msg = "";
		           while ((i+1)<sizeof(line))
		           {
		           			if (line[i]=="" || line[i+1] == "")
		           				return;
		           			msg += "听说" + sprintf("%|14s",line[i]) + "在北侠论坛发表了一篇名为『" + line[i+1] + "』的大作！\n";
		           			i = i + 2;
		           }
					set("channel_id", "论坛精灵");
		    		CHANNEL_D->do_channel( this_object(), "wiz",msg);
			        set("channel_id", "内存精灵");
				}
				if (!rm(FORUM_MSG_WIZCHANNEL_TEMP)) //文件删除失败
				{
						CHANNEL_D->do_channel( this_object(), "sys", "论坛更新信息临时文件" + FORUM_MSG_WIZCHANNEL_TEMP + "删除失败。\n");
						return;
				}				
		}

		if (file_size(FORUM_MANTIS) != -1)	 //mantischange文件不存在，间隔时间内无人修改mantis
		{
				
				if (rename(FORUM_MANTIS,FORUM_MANTIS_TEMP)) //文件改名失败
				{
						CHANNEL_D->do_channel( this_object(), "sys", "MANTIS更新信息文件" + FORUM_MANTIS + "重命名失败。\n");
						return;
				}
				
				lines = read_file(FORUM_MANTIS_TEMP);
				if (lines)
				{
		           line = explode(lines, "\n");
		           i = 0;
		           msg = "";
		           while ((i+1)<sizeof(line))
		           {
		           			if (line[i]=="" || line[i+1] == "")
		           				return;
		           			msg += "听说" + sprintf("%|14s",line[i]) + "在MANTIS提交了名为『" + line[i+1] + "』的计划！\n";
		           			i = i + 2;
		           }
					set("channel_id", "MANTIS精灵");
		    		CHANNEL_D->do_channel( this_object(), "wiz",msg);
			        set("channel_id", "内存精灵");
				}
				if (!rm(FORUM_MANTIS_TEMP)) //文件删除失败
				{
						CHANNEL_D->do_channel( this_object(), "sys", "MANTIS更新信息临时文件" + FORUM_MANTIS_TEMP + "删除失败。\n");
						return;
				}				
		}
		if (file_size(FORUM_MANTIS_NOTE) != -1)	 //mantisnote_change  文件不存在，间隔时间内无人添加mantisnote
		{
				
				if (rename(FORUM_MANTIS_NOTE,FORUM_MANTIS_NOTE_TEMP)) //文件改名失败
				{
						CHANNEL_D->do_channel( this_object(), "sys", "MANTIS更新信息文件" + FORUM_MANTIS_NOTE + "重命名失败。\n");
						return;
				}
				
				lines = read_file(FORUM_MANTIS_NOTE_TEMP);
				if (lines)
				{
		           line = explode(lines, "\n");
		           i = 0;
		           msg = "";
		           while ((i+1)<sizeof(line))
		           {
		           			if (line[i]=="" || line[i+1] == "")
		           				return;
		           			msg += "听说" + sprintf("%|14s",line[i]) + "在MANTIS为名为『" + line[i+1] + "』的计划提交了新备注！\n";
		           			i = i + 2;
		           }
					set("channel_id", "MANTIS精灵");
		    		CHANNEL_D->do_channel( this_object(), "wiz",msg);
			        set("channel_id", "内存精灵");
				}
				if (!rm(FORUM_MANTIS_NOTE_TEMP)) //文件删除失败
				{
						CHANNEL_D->do_channel( this_object(), "sys", "MANTIS更新信息临时文件" + FORUM_MANTIS_NOTE_TEMP + "删除失败。\n");
						return;
				}				
		}

				
		//如果巫师园地和巫师讨论区有更新，转帖至巫师留言板
		if (file_size(FORUM_MSG_WIZ) == -1)	 //文件不存在，间隔时间内无人发贴
				return;
		
		if (rename(FORUM_MSG_WIZ,FORUM_MSG_TEMP_WIZ)) //文件改名失败
		{
				CHANNEL_D->do_channel( this_object(), "sys", "论坛巫师版更新信息文件" + FORUM_MSG_WIZ + "重命名失败。\n");
				return;
		}
		
		lines = read_file(FORUM_MSG_TEMP_WIZ);
		note = allocate_mapping(6);
		if (lines)
		{
           line = explode(lines, "\n");
           i = 0;
           while ((i+1)<sizeof(line))
           {
				note["title"] = line[i+2];
				note["author"] = load_object(F_NAME)->replace_color(line[i+1]);
				note["authorid"] = line[i];
				note["time"] = time()+i;
				note["fid"] = line[i+3];
				note["tid"] = line[i+4];
				j = i + 6;
				msg = "";
				while (line[j] != "帖子内容结束标记")
				{
					msg += line[j] + "\n";
					j++;
				}
				load_object("/clone/board/wiz_b")->done_post(this_object(),note,msg);
       			i = j+1;
       			note = ([]);	//这里不重置mapping下次done_post时mapping内容不变，可能被mudos缓存了？
           }
		}
		if (!rm(FORUM_MSG_TEMP_WIZ)) //文件删除失败
		{
				CHANNEL_D->do_channel( this_object(), "sys", "论坛巫师版更新信息临时文件" + FORUM_MSG_TEMP_WIZ + "删除失败。\n");
				return;
		}				

}
//读取wiki修订信息
void wiki_msg()
{
		string lines,msg;
		int i;
		string *line;
		object imd;
		
		if (file_size(WIKI_MSG) == -1)	 //文件不存在，间隔时间内无人修订
				return;
		
		if (rename(WIKI_MSG,WIKI_MSG_TEMP)) //文件改名失败
		{
				CHANNEL_D->do_channel( this_object(), "sys", "WIKI修订信息文件" + WIKI_MSG + "重命名失败。\n");
				return;
		}
		
		lines = read_file(WIKI_MSG_TEMP);
		if (lines)
		{
           line = explode(lines, "\n");
           i = 0;
           msg = "";
           while ((i+1)<sizeof(line))
           {
           			if (line[i]=="" || line[i+1] == "")
           				return;
				    set("channel_id", "WIKI精灵");
				    imd = load_object("/adm/daemons/im_d");
				    imd->set("channel_id","QQ精灵");
           			msg += "通告：" + sprintf("%|14s",line[i]) + "在北侠百科(wiki.pkuxkx.net)修订了名为『" + line[i+1] + "』的主题，让我们对其贡献表示感谢！\n";
           			i = i + 2;
           }
           msg += "参与修订WIKI贡献较多的玩家，可以去论坛发贴请求奖励，巫师根据修改的质量给予相应的奖励！";
           CHANNEL_D->do_channel( this_object(), "jh", msg, -1);
           //wiki信息不再转发至qq
           //imd->process_send_msg(imd,"mud",msg);
			set("channel_id", "内存精灵");
		}
		if (!rm(WIKI_MSG_TEMP)) //文件删除失败
		{
				CHANNEL_D->do_channel( this_object(), "sys", "WIKI修订信息临时文件" + WIKI_MSG_TEMP + "删除失败。\n");
				return;
		}				
}

//helpnew投票排行
void helpnew_paihang()
{
        string msg;
        string *line;
        int vote_number;
        string lines, my_id, ip_list, victim_id, cname,victim_ip;
        int i, j, k, m;
        mapping *data;
                
//  将HELPNEW_LST里的数据读入数组data, 并统计投票者和票数
        lines = read_file(HELPNEW_LST);
        if(lines)
        {
           line = explode(lines, "\n");
           j = 0;
           data = ({});
           for(j=0,m=0;m<sizeof(line);)
           {
              for(i=m;i<sizeof(line);i++)
              {
                 sscanf(line[i],"%s,%s,%s,%s,%s", my_id, ip_list, victim_id, cname,victim_ip);
                 if(i == m) 
                 {
                    for(k=j-1;k>=0;k--) 
                    {
                       if(data[k]["id"] == victim_id) break;
                    }         
                    if(k<0)
                    {
                       data += ({ allocate_mapping(3) });
                       data[j]["id"] = (string)victim_id;
                       data[j]["name"] = (string)cname;
                       data[j]["num"] = 0;
                    }
                    else break;
                 }
                 if(victim_id == data[j]["id"] )  data[j]["num"] = data[j]["num"] + 1;
              }
              m++;
              if(i==sizeof(line)) j++;
           } 
        }
//   投票读数完成


//   将数组data里的内容按票数由大到小排序，并取出前十名放入数组list内
        list = ({});
        k=sizeof(data);
        for(j=0;j<k && j<10;j++)
        {
           for(i=0,m=0,vote_number=0;i<sizeof(data);i++)
           {
              if(data[i]["num"]>vote_number) 
              {
                 vote_number = data[i]["num"];
                 m=i;
              }
           }
           list += ({ allocate_mapping(3) });
           list[j]["id"]=data[m]["id"];
           list[j]["num"]=data[m]["num"];
           list[j]["name"]=data[m]["name"];
           data -= ({ data[m]});
        }
//   排序完成

//   显示列表
        msg = HIR"                  "HIG "◎" + MUD_NAME + HIG "◎" + HIW + "乐于助人排行榜\n"NOR;
        msg +="────────────────────────────────────────────\n\n";
        msg += sprintf("%-20s%-20s%-15s\n","英文名","中文名","票数");
        msg +="────────────────────────────────────────────\n\n";
        for(i=0;i<sizeof(list);i++)
        msg += sprintf("%-20s%-20s%-15d\n",list[i]["id"],list[i]["name"],list[i]["num"]);
        msg +="────────────────────────────────────────────\n\n";                                              
        shout(msg);
//完成

        return;
}
void check_helpnew()
{
        int i,j,money,exp,intVotecount,FindInMonth,MonthCount;
        string lines, my_id, ip_list, victim_id, cname,victim_ip,blist;
        string *line,*badlist;
        object voter,victim,ct_board;
	mapping note;

		//检查helpnew投票结果
		lines = read_file(HELPNEW_BAD_LST);
		if (lines)
			badlist = explode(lines,"\n");
		else
			badlist = ({""});
		lines = read_file(HELPNEW_LST);
		if (lines)
			line = explode(lines,"\n");
		else
			line = ({""});
		for(i=0;i<sizeof(line);i++)
		for(j=0;j<sizeof(badlist);j++)
		{
	                sscanf(line[i],"%s,%s,%s,%s,%s", my_id, ip_list, victim_id, cname,victim_ip);
	                sscanf(badlist[j],"%svote_target:%s %s",ip_list,my_id,victim_ip);
	                if (victim_id == my_id)
	                	line[i] = "";
	        }
	        rm(HELPNEW_LST);
		for(i=0;i<sizeof(line);i++)
		{
			if (line[i] != "")
				write_file(HELPNEW_LST,line[i] + "\n");
            }
		helpnew_paihang();
		lines = read_file(HELPNEW_MONTH_LST);
		if (lines)
			line = explode(lines,"\n");
		else
			line = ({""});
		for(i=0;i<sizeof(list);i++)
		{
			FindInMonth = 0;
			for(j=0;j<sizeof(line);j++)
			{
		                sscanf(line[j],"%s,%d", victim_id, MonthCount);
		                if (victim_id == list[i]["id"])
		                {
		                	FindInMonth = 1;
		                	MonthCount = MonthCount + list[i]["num"];
		                	line[j] = victim_id + "," + MonthCount;
		                	break;
		                }
			}	        
	                if (FindInMonth == 0)
	                	line = line + ({list[i]["id"] + "," + list[i]["num"]});
		}
		rm(HELPNEW_MONTH_LST);
		for(i=0;i<sizeof(line);i++)
				write_file(HELPNEW_MONTH_LST,line[i] + "\n");

		lines = read_file(HELPNEW_COUNT);
	        if(lines)
	        {
		        line = explode(lines, "\n");
                        sscanf(line[0],"%d",intVotecount);
                        write_file(HELPNEW_COUNT,(intVotecount+1) + "\n",1);
		}

		if (sizeof(list) == 0)
			shout(HIW"【投票】本周无人参加最受新手欢迎玩家评选！\n"NOR);
		else
		{
                        shout(HIW"【投票】本周最受新手欢迎玩家为："+HIR+BNK+list[0]["name"]+"("+list[0]["id"]+")"+NOR+HIW+"!\n"+NOR);
                        rename(HELPNEW_LST,HELPNEW_LST+"."+intVotecount);
			blist = read_file(HELPNEW_BAD_LST);
			if (blist)
				rename(HELPNEW_BAD_LST,HELPNEW_BAD_LST+"."+intVotecount);
			write_file(HELPER_OF_THE_WEEK,list[0]["id"],1);
			shout(HIW"请在一周内到正气山庄龙华天处领取奖励！(ask long about 奖励)过期不候！\n"NOR);
			note = allocate_mapping(4);
                                                 note["title"] = "/feature/name.c"->replace_color("$HIR$本周最受新手欢迎的玩家为：$HIR$$BNK$"+list[0]["id"]+"$NOR$");
			note["author"] = "投票精灵";
			note["authorid"] = "vote system";
			note["time"] = time();
			ct_board = load_object("/clone/board/ct_b");
			ct_board->done_post(this_object(),note,"请在一周内到正气山庄龙华天处领取奖励(ask long about 奖励)，过期不候！");
		}
		if (intVotecount%4 == 0) //月度排行
		{
			lines = read_file(HELPNEW_MONTH_LST);
			my_id = "";
			if (lines)
			{
				line = explode(lines,"\n");
				MonthCount = 0;
				for(i=0;i<sizeof(line);i++)
				{
			                sscanf(line[i],"%s,%d", victim_id, j);
			                if (j > MonthCount)
			                {
			                	my_id = victim_id;
			                	MonthCount = j;
			                }
			         }
			 }
			 if (my_id == "")
			 	shout(HIW"【投票】本月无人参加最受新手欢迎玩家评选！\n"NOR);
			 else
			 {
                                shout(HIW"【投票】本月最受新手欢迎玩家为：" + HIR+BNK+my_id+NOR+HIW+"!\n"+NOR);
                                rename(HELPNEW_MONTH_LST,HELPNEW_MONTH_LST+"."+intVotecount/4);
			 	write_file(HELPER_OF_THE_MONTH,my_id,1);
				shout(HIW"请在一月内到正气山庄龙华天处领取奖励！(ask long about 月度奖励)过期不候！\n"NOR);
				note = allocate_mapping(4);
                              	note["title"] = "/feature/name.c"->replace_color("$HIR$本月最受新手欢迎的玩家为：$HIR$$BNK$"+my_id+"$NOR$");
	                        note["author"] = "投票精灵";
				note["authorid"] = "vote system";
				note["time"] = time();
				ct_board = load_object("/clone/board/ct_b");
				ct_board->done_post(this_object(),note,"请在一月内到正气山庄龙华天处领取奖励(ask long about 月度奖励)，过期不候！");
			 }
		}              
}
