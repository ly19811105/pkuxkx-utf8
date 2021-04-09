//控制比武大会
//Designed by Jason@pkuxkx
//加入一些log信息by yhzzyahoo

inherit F_DBASE;
inherit F_SAVE;

#include <ansi.h>
#include <localtime.h>

#include <family.h>

#define TIMES_PER_DAY 5
#define STEP_TIME_SPAN 1

nosave int* schedule_time = ({2,8,16,20,22});

nosave int debug = 0;

nosave string basedir;
nosave int* expstage = ({5,20,50,100,400,0});

void checkstarttime();
void stop_task();
void finish_call_back();
int checkplayersinmap();
void preload_map();
void add_record(string log);
void truncate_records();

string query_save_file()
{
	return "/data/biwud";
}

void create()
{
	seteuid(getuid());
	set("channel_id",HIY"比武大会主持人"NOR);
	basedir = "/biwu/";
	restore();
	checkstarttime();
	preload_map();
}

void announce(string msg)
{
	CHANNEL_D->do_channel(this_object(), "rw", msg);
}

int checkplayersinmap()
{
	string* rooms;
	object room;
	object* invs;
	

	int i,j;
	int num = 0;

 //	log_file("biwu.log","调试开始：\n");

	if(query_temp("absolute_mapdir"))
	{
		rooms = get_dir(query_temp("absolute_mapdir")+"*");
		for(i=0;i<sizeof(rooms);i++)
		{
			if(rooms[i] == "." || rooms[i] == "..") continue;
			room = find_object(query_temp("absolute_mapdir")+rooms[i]);
			if(objectp(room) && room->isentryroom() == 1) 
			{
				invs = all_inventory(room);
				for(j=0;j<sizeof(invs);j++)
				{
					if(userp(invs[j]) && member_array(invs[j]->query("family/family_name"),query_temp("family_names")) != -1)
					{
						num++;
					}
				}
			}
		}
	}	
	return num;
}

void clearmap()
{
	string* rooms;
	object room;
	object* invs;
	int i,j;
 	
 	log_file("biwu.log","调试clear\n");
	if(query_temp("absolute_mapdir"))
	{
		rooms = get_dir(query_temp("absolute_mapdir")+"*");
		for(i=0;i<sizeof(rooms);i++)
		{
			if(rooms[i] == "." || rooms[i] == "..") continue;
			room = find_object(query_temp("absolute_mapdir")+rooms[i]);
			if(objectp(room)) 
			{
				invs = all_inventory(room);
				for(j=0;j<sizeof(invs);j++)
				{
					if(userp(invs[j]))
					{
						invs[j]->move(basedir+"gate");
					}
				}
				destruct(room);
			}
		}
	}	
}
//装载地图
mapping loadmap()
{
	string mapdir;
	string* mapdirs;
	object map;
 	mapping mapdata = ([]);	
 	mapdirs = get_dir(basedir+"*");

	log_file("biwu.log","调试load\n");
	if(arrayp(mapdirs))
	{
		mapdirs = filter_array(mapdirs,"filter_dir",this_object());

		printf("%d",sizeof(mapdirs));

		mapdir = mapdirs[random(sizeof(mapdirs))];
		map = find_object(basedir+mapdir+"/map.c");
		if(objectp(map))
		{
			destruct(map);
		}
		if(catch(map = load_object(basedir+mapdir+"/map.c")) != 0 || !objectp(map))		
		{
	//		log_file("biwu.log","调试mark0\n");

			log_file("biwu.log","装载地图"+mapdir+"失败\n");
		}
		else
		{
	//		log_file("biwu.log","调试mark1\n");
			mapdata["family_numbers"] = sizeof(map->query("family_entries"));
  			mapdata["family_entries"] = map->query("family_entries");
			mapdata["flag_numbers"] = map->query("flag_numbers");
			mapdata["absolute_mapdir"] = basedir+mapdir+"/";
			mapdata["mapname"] = map->query("name");	
            if(map->query("reward_factor"))
            {
                mapdata["reward_factor"] = map->query("reward_factor");			
            }
            else
            {
                mapdata["reward_factor"] = 1;			
            }
            if(map->query("duration"))
            {
                mapdata["duration"] = map->query("duration");			
            }
            else
            {
                mapdata["duration"] = 600;			
            }       
	//		log_file("biwu.log","调试mark2\n");			
  			log_file("biwu.log","装载地图"+mapdir+"成功\n");
		}
	}
	else
	{
	// 	log_file("biwu.log","调试mark3\n");
		log_file("biwu.log","尚未创建任何比武地图\n");
	}
	return mapdata;
}

void initmap(string* sels,mixed* family_entries)
{
	object gate;
	object entry;
	int i;
 	log_file("biwu.log","调试init\n");
	if(sizeof(sels) != sizeof(family_entries))
	{
  		log_file("biwu.log","地图初始化失败，门派数量不一致。\n");
		return;
	}

	
	if(catch(gate = load_object(basedir+"gate.c")) != 0 || !objectp(gate))
	{
		log_file("biwu.log","装载比武大门失败\n");
	}
	gate->delete("exits");
	gate->set("exits/south","/d/luoyang/ximen");		
	for(i=0;i<sizeof(family_entries);i++)
	{
 //	log_file("biwu.log","调试mark5\n");

		//set gate exits
		gate->set("exits/"+sels[i],query_temp("absolute_mapdir")+family_entries[i]["entry"]);
		//load and init the entries
		if(catch(entry = load_object(query_temp("absolute_mapdir")+family_entries[i]["entry"])) != 0 || !objectp(entry))		
		{	
			//这里开始屏蔽
 /*	log_file("biwu.log","调试mark6\n");

			log_file("biwu.log","1:"+query_temp("absolute_mapdir")+"\n");
			log_file("biwu.log","2:"+family_entries[i]["entry"]+"\n");
			log_file("biwu.log","3:"+query_temp("absolute_mapdir")+family_entries[i]["entry"]+"\n");
			log_file("biwu.log","4:"+entry+"\n");//到这里截至
*/
			log_file("biwu.log","门派入口装入失败。\n");
			return;
		}
		else
		{
			//这里开始屏蔽

 /*	log_file("biwu.log","调试mark7\n");

			log_file("biwu.log","1:"+query_temp("absolute_mapdir")+"\n");
			log_file("biwu.log","2:"+family_entries[i]["entry"]+"\n");
			log_file("biwu.log","3:"+query_temp("absolute_mapdir")+family_entries[i]["entry"]+"\n");
			log_file("biwu.log","4:"+entry+"\n");//到这里截至
*/
			entry->set("family_name",families[sels[i]][0]);
			if(query_temp("step") < sizeof(expstage))
			{
				entry->set("expstage",expstage[query_temp("step")-1]);				
			}
			else
			{
				//不限经验
				entry->set("expstage",-1);				
			}
			entry->set("exits/out",basedir+"gate.c");
			entry->set("no_reset",1);
			entry->set("no_cleanup",1);
			entry->set("no_cleanup",1);
		    entry->set("max_user",family_entries[i]["number"]);    
		}
	}	
}

void get_map_family_inschedule()
{
	mixed* maps;
	log_file("biwu.log","调试getmap\n");

	if(!query("map_queue"))
	{
		preload_map();
	}

	maps = query("map_queue");

	set_temp("family_numbers",maps[0][0]["family_numbers"]);
	set_temp("family_entries",maps[0][0]["family_entries"]);
	set_temp("flag_numbers",maps[0][0]["flag_numbers"]);
	set_temp("absolute_mapdir",maps[0][0]["absolute_mapdir"]);
	set_temp("mapname",maps[0][0]["mapname"]);
  	set_temp("reward_factor",maps[0][0]["reward_factor"]);
    if(query_temp("reward_factor") < 1) set_temp("reward_factor",1);    
    set_temp("duration",maps[0][0]["duration"]);
    if(query_temp("duration") < 60) set_temp("duration",60);    
    if(query_temp("duration") > 60*30) set_temp("duration",60*30);    

	set_temp("family_selected",maps[0][1]);

	maps -= ({maps[0]});

	set("map_queue",maps);
 	log_file("biwu.log","调试getmap over\n");

	preload_map();

}

//选择参与比武的门派
string* select_family(int number)
{
	int i,j;
	int n;
	string* fams = keys(families);
	string* sels = ({});
	for(i=0;i<number;i++)
	{
		n = random(sizeof(fams));
		//跳过一些门派
		if(families[fams[n]][1] != 1) 
		{
		  i--;
		  continue;
        }
		for(j=0;j<sizeof(sels);j++)
		{
			if(strcmp(fams[n],sels[j]) == 0)
			{
				break;
			}
			if((FAMILY_D->get_family_order(families[fams[n]][0]) - FAMILY_D->get_family_order(families[sels[j]][0]) > 10) || (FAMILY_D->get_family_order(families[fams[n]][0]) - FAMILY_D->get_family_order(families[sels[j]][0]) < -10))
			{
				break;
			}
		}
		if(j==sizeof(sels))
		{
			sels += ({fams[n]});
		}
		else
		{
			i--;
		}
	}

	if (debug)
	{
		for(j=0;j<sizeof(sels);j++)
		{
			write(sels[j]+"\r\n");
		}
	}

	return sels;
}

void preload_map()
{
    mapping data;
    string* fams;
    mixed* schedule;
    
//	log_file("biwu.log","调试 proload\n");
    if(!query("map_queue") || sizeof(query("map_queue")) < TIMES_PER_DAY*3)
    {
        if(query("map_queue"))
        {
            schedule = query("map_queue");
        }
        else
        {
            schedule = ({});
        }

		while(sizeof(query("map_queue")) < TIMES_PER_DAY*3)
		{
			data = loadmap();
			if(sizeof(data) == 0) continue;
						
			fams = select_family(data["family_numbers"]);
			schedule += ({({data,fams})});
			set("map_queue",schedule);
		}
    }
 //	log_file("biwu.log","调试proload over\n");

	save();
}

int* get_schedule_time()
{
	return schedule_time;
}
string* get_schedule()
{
    int i,j;
    mixed* schedule;
	string tmp;
    string* result = ({});

	mixed* timeinfos;
	int hour;
    int day = 0;
    string* daystr = ({"今日","明日","后日","外后日"});

	timeinfos = localtime(time());

	hour = timeinfos[LT_HOUR];
 //	log_file("biwu.log","调试get_schedu\n");

    for(i=0;i<sizeof(schedule_time);i++)
    {
        if(hour >= schedule_time[i]) continue;
        break;
    }
    if(i == sizeof(schedule_time)) 
    {
        i = 0;
        day = 1;
    }
    hour = i;

    if(!query("map_queue"))
    {
        result += ({"暂时没有比武安排。\n"});
    }
    else
    {
        schedule = query("map_queue");
        for(i=0;i<sizeof(schedule);i++)
        {
			tmp = "天下争霸第"+chinese_number(i+1)+"场,比武地点：" + schedule[i][0]["mapname"]+"。";
			tmp += "对阵门派：";
			for(j=0;j<sizeof(schedule[i][1]);j++) 
			{
				tmp += families[schedule[i][1][j]][0];
				tmp += ",";
			}
            if(hour >= sizeof(schedule_time)) 
            {
                hour = 0;
                day++;
            }
			tmp += daystr[day];
            tmp += chinese_number(schedule_time[hour]);
            tmp += "时。";

            hour++;

			result += ({tmp});
		}
    }
	return result;
}
//fam1,fam2 is for wizard to call this function directly to appoint family manually.
void prepare_task(string fam1,string fam2)
{    
	string* sels;
	string msg;
	string* familynames = ({});
	int i;

	mixed* timeinfos;
	int minute;

	timeinfos = localtime(time());

	minute = timeinfos[LT_MIN];
	

	get_map_family_inschedule();
	
	clearmap();
	
	delete_temp("family_names");
 	log_file("biwu.log","调试prepare_task"+timeinfos[LT_MDAY]+","+timeinfos[LT_HOUR]+","+timeinfos[LT_MIN]+"\n");
	if(!fam1 || !fam2 || fam1 == "" || fam2 == "")
	{
		sels = query_temp("family_selected");
	}
	else
	{	
	    printf("???\n");
		sels = ({fam1,fam2});
	}
	
	msg = "本次门派较技对阵方为：";
	for(i=0;i<sizeof(sels);i++)
	{
		msg += families[sels[i]][0];
		msg += " ("+chinese_number(query_temp("family_entries")[i]["number"])+"人)";
		msg += ",";
		familynames += ({families[sels[i]][0]});
	}
	set_temp("family_names",familynames);
// 	log_file("biwu.log","调试prepare1\n");
	msg = msg[0..<2];
	announce(msg);
 //	log_file("biwu.log","调试prepare2\n");
	
	add_record("\n");
	add_record(ctime(time())+"\n");
 	log_file("biwu.log","调试record\n");

	add_record(msg);
 //	log_file("biwu.log","调试prepare4\n");
	add_record("比武在"+query_temp("mapname")+"举行。\n");
// 	log_file("biwu.log","调试prepare5\n");

	announce("比武在"+query_temp("mapname")+"举行。");
	announce("请各派英雄一刻钟内到洛阳西门的武门聚集。");

	set_temp("gameplayers",sels);
	set_temp("step",1);

	initmap(sels,query_temp("family_entries"));

	set_temp("next_cycle_time",time()+60*10);
}

//开始比武
void start_task(int step)
{
  string familys;
  int i;
  string* records;
  string log;

	if(query_temp("started")) return;
 	log_file("biwu.log","调试start_task\n");

	familys = "";
	for(i=0;i<sizeof(query_temp("family_names"));i++)
	{
	    familys += query_temp("family_names")[i];
	    familys += ",";
	}
	delete_temp("next_cycle_time");
	//检查是否有人准备入场，如果一个人没有，直接开始下一轮
	if(checkplayersinmap() <= 0)
	{
		announce("比武大会第"+chinese_number(step)+"轮，"+familys+"都没有派出弟子参战，自动取消。");
		add_record("比武大会第"+chinese_number(step)+"轮，"+familys+"都没有派出弟子参战，自动取消。");

		stop_task();
	}
	else
	{
		if(step < sizeof(expstage))
		{
			announce("比武大会第"+chinese_number(step)+"轮，现在开始，请"+familys+chinese_number(expstage[step-1])+"M以下者入场比武！");
		}
		else
		{
			announce("比武大会第"+chinese_number(step)+"轮，现在开始，本轮不限经验，自由比试！");
		}
		set_temp("started",1);
		remove_call_out("check_biwu_completed");
		//默认10分钟必须分出胜负，否则判平局
        
		call_out("check_biwu_completed",query_temp("duration"));
	}
}

void stop_task()
{
	announce("比武大会第"+chinese_number(query_temp("step"))+"轮结束！");
	
	delete_temp("started");
	delete_temp("flags");
	
	remove_call_out("check_biwu_completed");
		
	if(query_temp("step") >= sizeof(expstage))
	{
		announce("本届比武大会全部结束！");
		remove_call_out("checkstarttime");
	    call_out("checkstarttime",60);
	    clearmap();
		delete_temp("step");
		delete_temp("absolute_mapdir");		
		add_record("本届比武大会全部结束！\n");
    }		
    else
    {
    	//continue next step
    	add_temp("step",1);
    	clearmap();
    	initmap(query_temp("gameplayers"),query_temp("family_entries"));
    	if(query_temp("step") < sizeof(expstage))
    	{
			announce("下一轮"+chinese_number(expstage[query_temp("step")-1])+"M以下，"+chinese_number(STEP_TIME_SPAN)+"分钟后开始！");    	
		}
		else
		{
			announce("下一轮无限制组，"+chinese_number(STEP_TIME_SPAN)+"分钟后开始！");    	
		}

		set_temp("next_cycle_time",time()+STEP_TIME_SPAN*60);
    	remove_call_out("start_task");
    	call_out("start_task",STEP_TIME_SPAN*60,query_temp("step"));    
	}
	save();
}

//比武开始时间控制
void checkstarttime()
{
	mixed* timeinfos;
	int hour;
	int minute;
	int mday;
	

	timeinfos = localtime(time());

	hour = timeinfos[LT_HOUR];
	minute = timeinfos[LT_MIN];
	mday = timeinfos[LT_MDAY];

	if(member_array(hour,schedule_time) != -1 && query_temp("prepare_task") == 1)
	{
			remove_call_out("checkstarttime");			
			start_task(query_temp("step"));
			delete_temp("prepare_task");
	}
	else
    {    
		if(member_array(hour+1,schedule_time) != -1 && minute >= 50 && !query_temp("prepare_task"))
		{			
			announce(HIR"比武大会将在"+chinese_number(60-minute)+"分钟后开始。");
			prepare_task("","");
			set_temp("prepare_task",1);
		}
     	remove_call_out("checkstarttime");
     	call_out("checkstarttime",60);
    }
}

void check_biwu_completed()
{
	if(query_temp("started") == 1)
	{
		announce("比武耗时太久，不分胜负。");
		add_record("比武大会第"+chinese_number(query_temp("step"))+"轮,耗时太久，不分胜负。\n");
		stop_task();
	}
}

void give_reward(string winfamily,string* failfamily)
{	
	string* rooms;
	object room;
	object* invs;
	int i,j;
	int exp,pot,score,rep;
 	
 		
	//修改门派威望
	announce(winfamily+"在武林中的威望上升一点！");	
	FAMILY_D->add_repute(winfamily,1);
	for(i=0;i<sizeof(failfamily);i++)
	{
        FAMILY_D->add_repute(failfamily[i],-1);			
		announce(failfamily[i]+"在武林中的威望下挫一点！");		
	}	
	//给获胜门派每个活着的参与者奖励


	if(query_temp("absolute_mapdir"))
	{
		rooms = get_dir(query_temp("absolute_mapdir")+"*");
		for(i=0;i<sizeof(rooms);i++)
		{
			if(rooms[i] == "." || rooms[i] == "..") continue;
			room = find_object(query_temp("absolute_mapdir")+rooms[i]);
			if(objectp(room) && room->isentryroom() != 1) 
			{
				invs = all_inventory(room);
				for(j=0;j<sizeof(invs);j++)
				{
					if(userp(invs[j]) && invs[j]->query("family/family_name") == winfamily)
					{
						tell_object(invs[j],"由于你为师门在江湖上的威望提高做出了贡献，你获得了：");
						score = query_temp("reward_factor") * (query_temp("step")*30 + random(30));
						rep = query_temp("reward_factor") * (query_temp("step")*2000 + random(2000));
						if ((invs[j]->query("exp/biwu") > (invs[j]->query("combat_exp")/10))&&invs[j]->query("combat_exp")<30000000)
						{
							exp=0;
							pot=0;
						}
						else
						{
			                exp = query_temp("reward_factor") * (query_temp("step")*10000 + random(10000));
				            pot = query_temp("reward_factor") * (query_temp("step")*10000 + random(10000));
                        }
						if (invs[j]->query("combat_exp") < 2000000)
						{
							exp/=2;
							pot/=2;
						}

                        score = REWARD_D->add_score(invs[j],score);

                        rep = REWARD_D->add_rep(invs[j],rep);
                        exp = REWARD_D->add_exp(invs[j],exp);
                        invs[j]->add("exp/biwu", exp);
                        pot = REWARD_D->add_pot(invs[j],pot);
                        invs[j]->add("pot/biwu", pot);
                        
                        tell_object(invs[j],sprintf("%d点师门忠诚度,%d点江湖声望,%d点经验和%d潜能的奖励！\n",score,rep,exp,pot));
                        
					}
				}
			}
		}
	}	
		
}

void finish_task(string winfamily)
{
	string log;
	string* lost_family;
	string* records;
	int i;

	truncate_records();

	records = query("records");
	if(!arrayp(records)) records = ({});

	lost_family = query_temp("family_names") - ({winfamily});
	announce(winfamily+"获得本次比武大会第"+chinese_number(query_temp("step"))+"轮的胜利！");
	give_reward(winfamily,lost_family);
	finish_call_back();

	log = "比武大会第"+chinese_number(query_temp("step"))+"轮,"+winfamily+"战胜";
	for(i=0;i<sizeof(lost_family);i++)
	{
		log += lost_family[i] + ",";
	}
	log += HIR"笑傲江湖。\n"NOR;
	
	add_record(log);

	stop_task();
}

void finish_call_back()
{
	string* rooms;
	object room;
	object* invs;
	int i,j;
	object map;

	if(query_temp("absolute_mapdir"))
	{
		map = load_object(query_temp("absolute_mapdir")+"/map.c");		
		
		rooms = get_dir(query_temp("absolute_mapdir")+"*");
		for(i=0;i<sizeof(rooms);i++)
		{
			if(rooms[i] == "." || rooms[i] == "..") continue;
			room = find_object(query_temp("absolute_mapdir")+rooms[i]);
			if(objectp(room) && room->isentryroom() != 1) 
			{
				invs = all_inventory(room);
				for(j=0;j<sizeof(invs);j++)
				{
					if(userp(invs[j]))
					{
						//by default, clear the busy status of every user
						invs[j]->start_busy(0);
                        if(objectp(map)) map->finish_task_call_back(invs[j]);
					}
				}
			}
		}
	}	
			
}
void catchflag(object pl,string name)
{
	int i,j;
	string* tmp;
	int finish = 1;
	if(!userp(pl)) return;

	if(member_array(pl->query("family/family_name"),query_temp("family_names")) == -1) return;

	if(!query_temp("flags/"+name) || query_temp("flags/"+name) != pl->query("family/family_name") )
	{
		set_temp("flags/"+name,pl->query("family/family_name"));
		announce(pl->query("family/family_name")+pl->query("title")+pl->query("name")+"夺取"+name+"！");
		pl->add_busy(2);
	}

	if(sizeof(query_temp("flags")) == query_temp("flag_numbers"))
	{
		tmp = values(query_temp("flags"));

		for(i=0;i<sizeof(tmp)-1;i++)
		{
			for(j=i+1;j<sizeof(tmp);j++)
			{
				if(tmp[i] != tmp[j])
				{
					finish = 0;
					break;
				}
			}
		}		
		if(finish == 1)
		{
			//done
			finish_task(pl->query("family/family_name"));
		}
	}
}


//query function

int taskstarted()
{
	if(query_temp("started")) return 1;
	return 0;
}

int getnextcycletimespan()
{
	if(query_temp("next_cycle_time"))
	{
		return query_temp("next_cycle_time") - time();
	}
	else
	{
		return -1;
	}
}

string* getrecords()
{
	if(arrayp(query("records"))) return query("records");
	return ({});
}

//protected function
int filter_dir(mixed item)
{
	if(stringp(item) && item != "." && item != ".." && item[0] != '_'  && item[0] != '.')
	{
		//it's dir
		if(file_size(basedir+item) == -2) return 1;
	}
	return 0;
}

void add_record(string log)
{
	string* records;

	truncate_records();
	records = query("records");
	if(!arrayp(records)) records = ({});
	records += ({log});
	set("records",records);

	save();

}
void truncate_records()
{
	int i;
	string* records;
	string log;

	records = query("records");
	if(!arrayp(records)) records = ({});

	if(sizeof(records) > 10*30)
	{
		for(i=0;i<sizeof(records) - 30;i++)
		{
			records[i] = "";
		}
		records -= ({""});
	}
}