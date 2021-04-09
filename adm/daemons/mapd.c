//掌管侠客行的地图。各个任务使用这里的接口分配随机的地点。
#include <map.h>

object random_room(string,int);
object random_place();
object random_place_ex(object);
string place_belong(object);

//cache the rooms. So that we dont need to go through all the rooms to find out the valid rooms
//use memory to save time
// "/d/lingxiao/":({"/d/lingxiao/room1","/d/lingxiao/room2"})
mapping map_cache = ([]);
mapping area_complexity=([]);//区域的复杂程度，like "/d/city/":150,记录区域内房间数量。
nosave mapping quest_reg;     //匿名任务区域注册表
nosave int qreg_serial;       //匿名任务区域注册最大序列号

int dbg()
{
    printf("map_cache size:%d\n",sizeof(map_cache));
    return 1;
}

//注册匿名任务区域
//匿名任务区域统一归属于QUESTREG（任务区域）大区域
//玩家级别统一设定为USER_LEVEL5
int set_quest_reg(string path)
{
  if ( !mapp(quest_reg) )
  {  
    quest_reg=([]);
    qreg_serial=0;
  }
  
  if ( !stringp(quest_reg[path]) )
  {
    quest_reg[path]=sprintf("匿名任务区域%d",qreg_serial);
    qreg_serial++;
    return 1;
  }
  else 
    return 0;
}

//提取匿名任务区域的区域名称
string query_quest_reg(string path)
{
  if ( stringp(quest_reg[path]) )
    return quest_reg[path];
  else
    return "未知区域";
}

int query_region_level(string path)
{
    if(sizeof(path) == 0) return 0;
    if(strsrch(path,"/",-1) != (sizeof(path) - 1))
    {
        path = path + "/";
    }
    if(undefinedp(ok_dir[path]))
    {
        return 0;
    }
    return ok_dir[path][2];
}
int obtain_area_complexity(string main_dir)
{
	if (undefinedp(area_complexity[main_dir]))
	log_file( "wiz/area_complexity", sprintf("\n%s\n随机地图[%s]区域房间未记录！\n", ctime(time()), main_dir ) );
	if (area_complexity[main_dir]<1)
	log_file( "wiz/area_complexity", sprintf("\n%s\n随机地图[%s]区域房间数为0！\n", ctime(time()), main_dir ) );  	
	return area_complexity[main_dir];
}
object random_room(string main_dir,int newbie)
{
	string *place=({}),*dir,filename;
	string *config_files=({"/d/hangzhou/song_room"});//房间配置文件，不是真的房间文件，不参与分配任务
	object output;
    
	int tmp,complexity;
   

    if(undefinedp(map_cache[main_dir]))
    {
        dir=get_dir(main_dir);
        for(int i=0;i<sizeof(dir);i++)
        {
            if(file_size(main_dir+dir[i])<=0||sscanf(dir[i],"%s.c",filename)!=1||member_array(main_dir+filename,config_files)!=-1)
            continue;
            tmp = sizeof(dir[i])-1;
            if (dir[i][tmp-1..tmp] != ".c") continue;
            if(catch(call_other(main_dir+dir[i],"??")) || !(output = load_object(main_dir+dir[i]))) continue;
            if (output->query("no_task") || ((output->query("no_newbie_task") || output->query("shegu")) && newbie == 1)) continue;            
            place+=({dir[i]});                   
        }  
        map_cache[main_dir] = place;
		if (undefinedp(area_complexity[main_dir]))
		area_complexity[main_dir] =sizeof(place);
    }
    
    if(!undefinedp(map_cache[main_dir]))
    {
        place = map_cache[main_dir];
        if(sizeof(place) == 0)
        {
            log_file( "wiz/map", sprintf("\n%s\n随机地图[%s]分配出错：无合适的房间！\n", ctime(time()), main_dir ) );  
            return load_object("/adm/daemons/taskd");
        }
        filename = place[random(sizeof(place))];
        if(catch(call_other(main_dir+filename,"??")) || !(output = load_object(main_dir+filename)))
        {
            log_file( "wiz/map", sprintf("\n%s\n随机地图[%s]分配出错：房间[%O]载入出错！\n", ctime(time()), main_dir,  filename) );
            return load_object("/adm/daemons/taskd");
        }
        output->set("main_dir",main_dir);
        return output;
    }   

    //lots of code check the basename of taskd. So return the taskd object here
	return load_object("/adm/daemons/taskd");
}

//assign a random place. if user is not null, the assigned region will not cross big region
object random_place()
{
	string main_dir,*dirs;

	dirs=keys(ok_dir);
	while(1)
	{
		main_dir=dirs[random(sizeof(dirs))];
        if(ok_dir[main_dir][2] > USER_LEVEL4) continue;
		break;
	}
    if(objectp(this_player()))
    {
        return random_room(main_dir,this_player()->query("combat_exp") < 3000000);
    }
    else
    {
        return random_room(main_dir,0);
    }
}

object random_place_ex(object user)
{
	string main_dir,*dirs;
	object env;
    string cur_main_dir;
    string* parts;

    int i = 0;
    int userlevel = USER_LEVEL0;

    if(user->query("combat_exp") < 60000) userlevel = USER_LEVEL0;
    else if (user->query("combat_exp") < 100000) userlevel = USER_LEVEL1;
    else if (user->query("combat_exp") < 300000) userlevel = USER_LEVEL2;
    else if (user->query("combat_exp") < 1000000) userlevel = USER_LEVEL3;
    else userlevel = USER_LEVEL4;

	dirs=keys(ok_dir);
   	main_dir=dirs[random(sizeof(dirs))];

    if(objectp(user) && userp(user))
    {
		env = environment(user);
		if(!objectp(env)) return this_object();
		if(!env->query("main_dir"))
		{
			parts = explode(base_name(env),"/");
			if(sizeof(parts) > 2)
			{
				cur_main_dir = "/"+parts[0]+"/"+parts[1]+"/";
				env->set("main_dir",cur_main_dir);
			}    
		}
		else
		{
			cur_main_dir = env->query("main_dir");
		}
        //map/keepsameregion, it's for some tasks like: 胡一刀，avoid to generate the next npc in far away region.
		while((!undefinedp(ok_dir[cur_main_dir]) && ok_dir[main_dir][1] != ok_dir[cur_main_dir][1] && (user->query_temp("map/keepsameregion") && random(100) < 99)) 
			|| userlevel < ok_dir[main_dir][2])//按userlevel分配区域
		{
			main_dir=dirs[random(sizeof(dirs))];	
            if(++i >= 100)
            {
                main_dir = "/d/city/";
                break;
            }
        }
    }
    user->delete_temp("map/keepsameregion");

    return random_room(main_dir,user->query("combat_exp") < 3000000);
}
string place_belong(object place)
{
    string dir_name;
    string* parts;

/*    if(!place->query("main_dir"))
    {
        parts = explode(base_name(place),"/");
        if(sizeof(parts) > 2)
        {
            dir_name = "/"+parts[0]+"/"+parts[1]+"/";
            place->set("main_dir",dir_name);
        }    
    }*/
    dir_name = place->query_location();
    place->set("main_dir",dir_name);      
    if(place->query("main_dir"))
    {
        if(undefinedp(ok_dir[place->query("main_dir")]))
        {
            return "未知区域";
        }
    	return ok_dir[place->query("main_dir")][0];
    }
    else
    {
        return "不明区域";
    }
}


