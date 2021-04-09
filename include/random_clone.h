//随机地图，Zine
//type是地图类型，可以选择山地、林地、湖泽、沙漠、草原、混合，缺省为混合
//size是地图尺寸，1-小，2-中，3-大，4-超大，缺省为随机
//origin为指定迷宫开始object，缺省为当前。
//exit1-4为迷宫出口，缺省则为封闭迷宫。可选其中某exit，如全部指定则分别连接地图最东、最南、最西、最北的边缘
#include <ansi.h>
string *types=({"山地","林地","湖泽","沙漠","草原","混合"});
string generate_connection(object origin,int size,string type);
int new_room(int delay,object new_origin,int size,string type);
int change_new_name(string type,object the_origin,int assign);
string obtain_edge(object origin);
string leave_msg(object origin,object exit);
string op_position(string dir);
string * extra_conn=({"xiaodao","xiaolu","xiaojing","biandao","zhailu","xialu"});
string * extra_conn_name=({"小道","小路","小径","便道","窄路","狭路"});
mapping * connections=({
	([  "direction":"east","op-direction":"west","horizontal_increase":1,"vertical_increase":0,"level_increase":0,"clock_direction":3,]),
	([  "direction":"west","op-direction":"east","horizontal_increase":-1,"vertical_increase":0,"level_increase":0,"clock_direction":7,]),
	([  "direction":"north","op-direction":"south","horizontal_increase":0,"vertical_increase":1,"level_increase":0,"clock_direction":1,]),
	([  "direction":"south","op-direction":"north","horizontal_increase":0,"vertical_increase":-1,"level_increase":0,"clock_direction":5,]),
	([  "direction":"southeast","op-direction":"northwest","horizontal_increase":1,"vertical_increase":-1,"level_increase":0,"clock_direction":4,]),
	([  "direction":"southwest","op-direction":"northeast","horizontal_increase":-1,"vertical_increase":-1,"level_increase":0,"clock_direction":6,]),
	([  "direction":"northeast","op-direction":"southwest","horizontal_increase":1,"vertical_increase":1,"level_increase":0,"clock_direction":2,]),
	([  "direction":"northwest","op-direction":"southeast","horizontal_increase":-1,"vertical_increase":1,"level_increase":0,"clock_direction":8,]),
	([  "direction":"northup","op-direction":"southdown","horizontal_increase":0,"vertical_increase":1,"level_increase":1,"clock_direction":1,]),
	([  "direction":"northdown","op-direction":"southup","horizontal_increase":0,"vertical_increase":1,"level_increase":-1,"clock_direction":1,]),
	([  "direction":"southup","op-direction":"northdown","horizontal_increase":0,"vertical_increase":-1,"level_increase":1,"clock_direction":5,]),
	([  "direction":"southdown","op-direction":"northup","horizontal_increase":0,"vertical_increase":-1,"level_increase":-1,"clock_direction":5,]),
	([  "direction":"eastup","op-direction":"westdown","horizontal_increase":1,"vertical_increase":0,"level_increase":1,"clock_direction":3,]),
	([  "direction":"eastdown","op-direction":"westup","horizontal_increase":1,"vertical_increase":0,"level_increase":-1,"clock_direction":3,]),
	([  "direction":"westup","op-direction":"eastdown","horizontal_increase":-1,"vertical_increase":0,"level_increase":1,"clock_direction":7,]),
	([  "direction":"westdown","op-direction":"eastup","horizontal_increase":-1,"vertical_increase":0,"level_increase":-1,"clock_direction":7,]),
	([  "direction":"up","op-direction":"down","horizontal_increase":0,"vertical_increase":0,"level_increase":1,"clock_direction":9,]),
	([  "direction":"down","op-direction":"up","horizontal_increase":0,"vertical_increase":0,"level_increase":-1,"clock_direction":10,]),
});//18个常规方向，不包含enter/out，因为enter/out无法体现坐标变化
#define TYPE10 0
#define TYPE11 14//0-14 山地描述
#define TYPE20 15
#define TYPE21 30//15-30 林地描述
#define TYPE30 31
#define TYPE31 46//31-46 湖泽描述
#define TYPE40 47
#define TYPE41 61//47-61 沙漠描述
#define TYPE50 62
#define TYPE51 70//62-70 草原描述
#define TYPE60 71
#define TYPE61 74//71-74 综合描述，可出现在任何环境，但概率低
#define TYPE70 75
#define TYPE71 80//75-80 对应6种地形up描述
#define TYPE80 81
#define TYPE81 86//81-86 对应6种地形down描述
string *shorts=({"荒地","山路","山坡","山间平台","陡坡","山脊","峭壁","枯藤","巨岩","山腰","一线天","悬崖","缓坡","泉眼","瀑布",
"巨木","松柏林","小树林","密林","矮树","平地","树桩","便道","林间小道","枯树","斜坡","树丛","灌木","溪间","小溪","荆棘林",
"湖边","湖畔","岸边","浅滩","湿地","滩涂","泥塘","水塘","沼泽","大沼泽","垂柳","莲池","岸边柳树","草地","草丛","泥泞路",
"沙丘","大沙丘","沙坡","沙漠","大沙漠","仙人掌","巨型沙丘","荒原","绿洲","沙漠绿洲","废墟","古河道遗址","古城废墟","大仙人掌","古道",
"草原","大草原","废弃帐篷","废弃营地","河滩","变浅的河道","牧场","草甸","草场",
"老宅","旧宅","废园","杂院",
"顶峰","树冠","土坡上","沙丘上","高处","屋顶",
"洞穴","土窝","大水坑","沙穴","兔子洞","陷坑",});
int * drink_place=({14,29,30,32,33,34,35,39,43,56,57,67,68,84});
//可drink ({14,29,30,32,33,34,35,39,43,56,57,67,68,84})
int * fish_place=({14,29,30,32,33,34,35,39,43});
//可fish ({14,29,30,32,33,34,35,39,43,56,57})
int * look_place=({15,16,43,60,61,69});
//可look景观 ({15,16,43,60,61,69}) 瀑布，巨木，莲池，古城废墟，大仙人掌，牧场
int * zhai_place=({17,18,19});
//可以zhai果子 ({17,18,19})
int * ji_place=({53,61});
//可以ji汁({53,61})仙人掌，大仙人掌
int * thirsty_place=({48,49,50,51,52,54,58});
//可快速消耗饮水({48,49,50,51,52,54,58})
int * mountain_animal=({3,4,5,6,10,11,13});
//出现山鸡，猕猴，山羊，麻雀，狼，野猪，狐狸 ({3,4,5,6,10,11,13})
int * forest_animal=({17,18,19,24,26,27,31});
//出现鹿，老虎，黑熊，野兔，巨蟒，竹叶青，松鼠({17,18,19,24,26,27,31})
int * lakeside_animal=({32,33,34,35,36,37});
//出现鳄鱼，野鸭，大雁，白鹤({32,33,34,35,36,37})
int * desert_animal=({48,49,50,51,52,54,58,60});
//出现蝎子，响尾蛇，秃鹫({48,49,50,51,52,54,58,60})
int * grassland_animal=({63,64,67,69,70,71});
//出现牦牛，绵羊，马，野马({63,64,67,69,70,71})
int * animal_place=({3,4,5,6,10,11,13,17,18,19,24,26,27,31,32,33,34,35,36,37,48,49,50,51,52,54,58,60,63,64,67,69,70,71});

string *colors=({YEL,GRN,HIG,GRN,YEL,HIC,WHT,YEL,WHT,GRN,HBGRN,HBCYN,GRN,WHT,HIW,
HIG,HBGRN,GRN,HBGRN,GRN,WHT,HBYEL,YEL,GRN,HBYEL,CYN,HIG,HIY,WHT,HIW,HIG,
GRN,HIG,HBGRN,HBGRN,WHT,HIW,HBYEL,WHT,HBYEL,HBYEL,GRN,HBGRN,HIG,HIG,GRN,HBYEL,
YEL,HBYEL,HIY,HBYEL,HBYEL,GRN,HBYEL,GRN,HIG,HIG,CYN,HIC,HBCYN,HBGRN,HBCYN,
GRN,HIG,MAG,HBMAG,HBGRN,WHT,HBGRN,GRN,HIG,
HBRED,HBCYN,HBWHT,WHT,
HBCYN,HBGRN,HBYEL,HIY,GRN,HBRED,
CYN,YEL,HIW,HIY,HBGRN,GRN});

int blind_random_map()
{
	return 1;
}

int initiate_obtain_edge(object origin)
{
    mixed *waiting_info;
    string topic="generate_connection";
    waiting_info = filter_array(call_out_info(), (: $1[1]==$2 :), topic);
    if (sizeof(waiting_info)>0)
    {
        remove_call_out("initiate_obtain_edge");
        call_out("initiate_obtain_edge",1,origin);
        return 1;
    }
    else
    {
        origin->add_temp("succ_possibility",1);
        if (origin->query_temp("succ_possibility")>3)
        {
            remove_call_out("initiate_obtain_edge");
            obtain_edge(origin);
            return 1;
        }
        else
        {
            remove_call_out("initiate_obtain_edge");
            call_out("initiate_obtain_edge",1,origin);
            return 1;
        }
    }
}

string gene(string type,int size,object origin,object exit1,object exit2,object exit3,object exit4,int invisible)
{
	string msg;
	if (!type||member_array(type,types)<0)
	type="混合";
	if (!size||size<0||size>4)
	size=1+random(4);
	if (!origin)
	origin=this_object();
	if (!size)//size决定层次，小地图2-3层，中等地图3-4层，大地图3-5层，特大地图4-5层
	size=2+random(3);
	else if (size==1||size==2)
	size=2+random(2);
	else if (size==3)
	size=2+random(3);
	else if (size==4)
	size=3+random(2);
	else 
	size=2+random(3);
	origin->delete("exit1");
	origin->delete("exit2");
	origin->delete("exit3");
	origin->delete("exit4");//状态清零
	if (exit1&&objectp(exit1))
	{
		origin->set("exit1",file_name(exit1));
		exit1->set("random_map_exit",1);
	}
	if (exit2&&objectp(exit2))
	{
		origin->set("exit2",file_name(exit2));
		exit2->set("random_map_exit",1);
	}
	if (exit3&&objectp(exit3))
	{
		origin->set("exit3",file_name(exit3));
		exit3->set("random_map_exit",1);
	}
	if (exit4&&objectp(exit4))
	{
		origin->set("exit4",file_name(exit4));
		exit4->set("random_map_exit",1);
	}
	if (invisible)
	origin->set("invisible",1);
	origin->set("overall_type",type);
	origin->set("origin_file",origin);
	origin->set("x",0);//原点坐标
	origin->set("y",0);
	origin->set("z",0);
	origin->add("no_clean_up",1);
	origin->add("no_reset",1);
	origin->set("total_layers",size);
	origin->delete("fully_generated");
	origin->set("generating",1);
	origin->change_new_name(type,origin);
	origin->delete_temp("mixed_long");
	generate_connection(origin,size,type);
	call_out("initiate_obtain_edge",2,origin);
	msg="初始化……地点:"+base_name(origin)+"层数:"+chinese_number(size)+"类型:"+type+"。\n";
	return msg;
}
void record_maze_map(object the_origin,object origin,object new_room,string conn_dir)
{
	string room_id,new_id,*filter_n=({"northup","northdown","north",}),*filter_ne=({"northeast"}),*filter_e=({"eastup","eastdown","east",}),
	*filter_se=({"southeast"}),*filter_s=({"southup","southdown","south",}),*filter_sw=({"southwest"}),*filter_w=({"westup","westdown","west",}),*filter_nw=({"northwest"});
	if (origin==the_origin)
	{
		origin->set("room_id","roomA0");
		the_origin->set("MAZE_LIST/roomA0",origin->query("short"));
	}
	room_id=origin->query("room_id");
	if (member_array(conn_dir,filter_n)!=-1)
	new_id="room"+room_id[strwidth(room_id)-1..strwidth(room_id)-1]+"1";
	else if (member_array(conn_dir,filter_ne)!=-1)
	new_id="room"+room_id[strwidth(room_id)-1..strwidth(room_id)-1]+"2";
	else if (member_array(conn_dir,filter_e)!=-1)
	new_id="room"+room_id[strwidth(room_id)-1..strwidth(room_id)-1]+"3";
	else if (member_array(conn_dir,filter_se)!=-1)
	new_id="room"+room_id[strwidth(room_id)-1..strwidth(room_id)-1]+"4";
	else if (member_array(conn_dir,filter_s)!=-1)
	new_id="room"+room_id[strwidth(room_id)-1..strwidth(room_id)-1]+"5";
	else if (member_array(conn_dir,filter_sw)!=-1)
	new_id="room"+room_id[strwidth(room_id)-1..strwidth(room_id)-1]+"6";
	else if (member_array(conn_dir,filter_w)!=-1)
	new_id="room"+room_id[strwidth(room_id)-1..strwidth(room_id)-1]+"7";
	else if (member_array(conn_dir,filter_nw)!=-1)
	new_id="room"+room_id[strwidth(room_id)-1..strwidth(room_id)-1]+"8";
	else
	new_id="CANNOT_DISPLAY";
	new_room->set("room_id",new_id);
	the_origin->set("MAZE_LIST/"+new_id,new_room->query("short"));
}
string retract_path(string *paths)
{
	string path,result="";
	for (int i=sizeof(paths)-1;i>=0;i--)
	{
		path=op_position(paths[i]);
		result+="->"+path;
	}
	return result;
}
int get_op_pathway(string e_path,string s_path,string w_path,string n_path,object origin)
{
	string path_n="",path_e="",path_w="",path_s="";
	if (stringp(n_path))
	path_n=retract_path(explode(n_path,"->"));
	if (stringp(s_path))
	path_s=retract_path(explode(s_path,"->"));
	if (stringp(w_path))
	path_w=retract_path(explode(w_path,"->"));
	if (stringp(e_path))
	path_e=retract_path(explode(e_path,"->"));
	origin->set("pathways/path_e",path_e);
	origin->set("pathways/path_s",path_s);
	origin->set("pathways/path_w",path_w);
	origin->set("pathways/path_n",path_n);
	return 1;
}
string pathway(object room)
{
	string path;
	if (room&&load_object(room->query("previous_room")))
	{
		path=op_position(room->query("previous_room_direction"));
		room=load_object(room->query("previous_room"));
	}
	while (room&&room->query("previous_room"))
	{
		if (load_object(room->query("previous_room")))
		{
			path+="->"+op_position(room->query("previous_room_direction"));
			room=load_object(room->query("previous_room"));
		}
	}
	return path;
}
string get_pathway(object origin)
{
	string e_path,s_path,w_path,n_path;
	if (!origin)//wiz called.
	origin=this_object();
	e_path=pathway(origin->query("most_east"));
	s_path=pathway(origin->query("most_south"));
	w_path=pathway(origin->query("most_west"));
	n_path=pathway(origin->query("most_north"));
	origin->set("pathways/e_path",e_path);
	origin->set("pathways/s_path",s_path);
	origin->set("pathways/w_path",w_path);
	origin->set("pathways/n_path",n_path);
	get_op_pathway(e_path,s_path,w_path,n_path,origin);
	return "\n";
}
void clear_user_room(object room,object exit,string leave_msg)
{
	object *all_pl=all_inventory(room);
	for (int j=0;j<sizeof(all_pl);j++)
	{
		if (all_pl[j]&&userp(all_pl[j]))
		{
			all_pl[j]->move(exit);
			tell_object(all_pl[j],leave_msg);
		}
	}
}
void init()
{
	object me=this_player();
	object origin,exit,ob=this_object();
	string *exits=({"exit1","exit2","exit3","exit4"}),msg;
	add_action("do_drink","drink");
	add_action("do_look","look");
	add_action("do_zhai","zhai");
	add_action("do_ji","ji");
	if (ob->query("origin_file"))
	origin=ob->query("origin_file");
	if (!origin) return;
	if (!origin->query("fully_generated"))
	{
		for (int i=0;i<sizeof(exits);i++)
		if (!origin->query(exits[i]))
		exits-=({exits[i]});
		if (sizeof(exits)==0)
		exit=load_object("/d/luoyang/wumiao");
		else
		exit=load_object(origin->query(exits[random(sizeof(exits))]));
		msg=leave_msg(origin,exit);
		clear_user_room(this_object(),exit,msg);
		return;
	}
}

int faint_me(object me)
{
	if (!me||!living(me))
	return 1;
	me->set("water",0);
	if(random(4))
	{
		message_vision(HIY"$N干渴过度，只觉脑中嗡嗡作响，眼冒金星！\n"NOR, me);
		if (me->query("eff_jing")<40||me->query("jing")<40)
		{
			me->add_busy(45);;
			me->unconcious();
			return 1;
		}
		me->receive_wound("jing", 40, "在沙漠中干渴");
		return 1;
	}
	message_vision(HIY"$N干渴过度，终于体力不支，晕倒在地！\n"NOR, me);
	me->add_busy(45);;
	me->unconcious();
	return 1;
}


int valid_leave(object me,string dir)
{
	int food = me->max_food_capacity();
	int water = me->max_water_capacity();
	object camel;
	object env=environment(me);
	if (env&&member_array((int)env->query("room_type"),thirsty_place)!=-1)
	{
		if( userp(me) && ::valid_leave(me, dir)&& (!objectp(camel = me -> query_temp("riding"))|| camel->name() != HIW"白骆驼"NOR ) )
		{
			me->add("food", - food / 10);
			me->add("water", - water / 3);
			me->add_busy(2);
			tell_object(me, HIY"你觉得口干舌燥，真是生不如死！\n不知道何时才能走出茫茫大沙漠。\n"NOR);
			if(me->query("food") < 0 || me->query("water") < 0 )
				call_out("faint_me", 1, me);
		}
	}
	return ::valid_leave(me, dir);
}

int lookview(object me,object env)
{
	if (!me)
	return 1;
	if (env!=environment(me))
	return 1;
	if (env->query("room_type")==15)
	{
		tell_object(me,HIW+"这里的瀑布奔流而下，似乎千年未曾停歇过。\n"+NOR);
		return 1;
	}
	if (env->query("room_type")==16)
	{
		tell_object(me,HIG+"这棵巨大的树木需要十几个壮汉才能围抱起来，树冠遮天蔽日。\n"+NOR);
		return 1;
	}
	if (env->query("room_type")==43)
	{
		tell_object(me,WHT+"这一池的莲花静静的开着，高贵素雅。\n"+NOR);
		return 1;
	}
	if (env->query("room_type")==60)
	{
		tell_object(me,CYN+"千年前的古城，早已成了断瓦残垣，不知何样的文明曾在这里孕育过。\n"+NOR);
		return 1;
	}
	if (env->query("room_type")==61)
	{
		tell_object(me,HIG+"这棵巨大的仙人掌竟有一人多高，沙漠中竟有此等雄奇的植物。\n"+NOR);
		return 1;
	}
	if (env->query("room_type")==69)
	{
		tell_object(me,HIG+"草原上的牧场，放眼望去，直是“风吹草低见牛羊”。\n"+NOR);
		return 1;
	}
	return 1;
}

int do_look(string arg)
{
	object me=this_player();
	object env=environment(me);
	if (arg=="view"&&env&&member_array((int)env->query("room_type"),look_place)!=-1)
	{
		if (time()-(int)me->query_temp("randommap/lookview")>60)
		{
			write("你凝望着"+env->query("short")+"，不由感慨大自然的壮观。\n");
			me->set_temp("randommap/lookview",time());
			call_out("lookview",1+random(2),me,env);
			return 1;
		}
		else
		{
			write("世界如此美好，你却如此暴躁。此等美景也不能让你收起点浮躁的心吗？\n");
			return 1;
		}
	}
	else
	return 0;
}

int do_zhai()
{
	object guo,me=this_player();
	object env=environment(me);
	if (env&&member_array((int)env->query("room_type"),zhai_place)!=-1)
	{
		if (random(100)>19&&time()-(int)me->query_temp("randommap/zhaiguo")>10+random(50)) 
		{
			guo=new("obj/food/guo");
			guo->move(me);
			me->set_temp("randommap/zhaiguo",time());
			message("vision", me->name()+"爬上"+env->query("short")+"的一棵大树，摘下了一只果子。\n",environment(me), ({me}) );
			write("你从"+env->query("short")+"的树上，摘下了一只"+guo->query("name")+"。\n");
		}
		else write("树上的果子都烂光了。\n");
		return 1;
	}
	else
	return 0;
}

int do_ji()
{
	object me=this_player();
	object env=environment(me);
	int current_water,max_water;
	if (env&&member_array((int)env->query("room_type"),ji_place)!=-1)
	{
		if (random(100)>39) 
		{   
			current_water = me->query("water");
			max_water = (int)me->max_water_capacity();
			if (current_water<max_water/3) 
			{   
				me->add("water", 30+random(20));
				message("vision", me->name()+"将"+env->query("short")+"的仙人掌挤出汁来，喝了下去。\n",environment(me), ({me}) );
				write("你喝下了仙人掌里挤出的汁水。\n");
				return 1;
			}
			message_vision("$N把仙人掌挤出了汁水，立刻被沙漠的暴虐天气所蒸发。\n",me);
			return 1;
		}
		else 
		{
			message_vision(RED+"$N一个不慎，被仙人掌的刺狠狠扎在了手上。\n"+NOR,me);
			if (me->query("qi")<10)
			me->unconcious();
			else
			me->add("qi",-10);
			return 1;
		}
	}
	else
	return 0;
}

int do_drink(string arg)
{
    object me=this_player();
    object env=environment(me);
    int current_water,max_water;
    if (env&&member_array((int)env->query("room_type"),drink_place)!=-1)
    {
        if(arg) return 0;
        current_water = me->query("water");
        max_water = (int)me->max_water_capacity();
        if (current_water<max_water) 
        {   
            me->add("water", 200-random(50));
            message("vision", me->name()+"捧起"+env->query("short")+"附近的水源就是一阵牛饮。\n",environment(me), ({me}) );
            write("你捧起"+env->query("short")+"附近的水，一阵畅饮。\n");
        }
        else write("你已经不渴了，还是别涨破肚子了。\n");
        return 1;
    }
    else
    {
        return 0;
    }
}
void clear_exit(object exit,string exit_dir)
{
	mapping dir=(["exit1":"west","exit2":"north","exit3":"east","exit4":"south"]);
	exit->delete("exits/"+dir[exit_dir]);
	exit->delete("random_map_exit");
	exit->delete("realmap");
	if (exit->query("no_clean_up")>=1)
	exit->add("no_clean_up",-1);
	if (exit->query("no_reset")>=1)
	exit->add("no_reset",-1);
	if (exit->query("no_clean_up")<0)
	exit->set("no_clean_up",0);
	if (exit->query("no_reset")<0)
	exit->set("no_reset",0);
}
string clear_all()
{
	object exit=load_object("/d/luoyang/wumiao"),origin,dest_room,*all_pl;
	int i,j;
	string uni_exit,msg,*exits=({"exit1","exit2","exit3","exit4"});
	mapping variables;
	mixed *variable;
	if (this_object()->query("origin_file"))
	{
		if (!origin=this_object()->query("origin_file"))
		return "寻找原始文件失败。\n";
		for (i=0;i<sizeof(exits);i++)
		if (!origin->query(exits[i]))
		exits-=({exits[i]});
		if (sizeof(exits)>0&&stringp(uni_exit=origin->query(exits[random(sizeof(exits))])))
		exit=load_object(uni_exit);
		for (i=0;i<sizeof(exits);i++)
		{
			if (stringp(origin->query(exits[i]))&&load_object(origin->query(exits[i])))
			clear_exit(origin->query(exits[i]),exits[i]);
		}
		msg=leave_msg(origin,exit);
		for (i=0;i<sizeof(origin->query("gene_objects"));i++)
		{
			if (origin->query("gene_objects/"+i))
			{
				clear_user_room(origin->query("gene_objects/"+i),exit,msg);
				destruct(origin->query("gene_objects/"+i));
			}
		}
		origin->add("no_clean_up",-1);
		origin->add("no_reset",-1);
		clear_user_room(origin,exit,msg);
		if (origin)
		{
			variables=(mapping)origin->query_entire_dbase();
			if (mapp(variables))
			{
				variable=keys(variables);
				for (j=0;j<sizeof(variable);j++)
				origin->delete(variable[j]);
			}
			variables=(mapping)origin->query_entire_temp_dbase();
			if (mapp(variables))
			{
				variable=keys(variables);
				for (j=0;j<sizeof(variable);j++)
				origin->delete_temp(variable[j]);
			}
		}
		return "清理随机地图完成！\n";
	}
	else
	return "寻找原始文件失败。\n";
}
/*string clear_all()
{
	object exit=load_object("/d/luoyang/wumiao"),origin,dest_room,*all_pl;
	int i,j;
	string uni_exit,msg,*exits=({"exit1","exit2","exit3","exit4"});
	mapping variables;
	mixed *variable;
	if (this_object()->query("origin_file"))
	{
		if (!origin=this_object()->query("origin_file"))
		return "寻找原始文件失败。\n";
		for (i=0;i<sizeof(exits);i++)
		if (!origin->query(exits[i]))
		exits-=({exits[i]});
		if (sizeof(exits)>0&&stringp(uni_exit=origin->query(exits[random(sizeof(exits))])))
		exit=load_object(uni_exit);
		for (i=0;i<sizeof(exits);i++)
		{
			if (stringp(origin->query(exits[i]))&&load_object(origin->query(exits[i])))
			clear_exit(origin->query(exits[i]),exits[i]);
		}
		msg=leave_msg(origin,exit);
		for (i=0;i<sizeof(origin->query("gene_rooms"));i++)
		{
			if (origin->query("gene_rooms/"+i))
			{dest_room=load_object(origin->query("gene_rooms/"+i));}
			if (dest_room)
			{
				clear_user_room(dest_room,exit,msg);
				destruct(dest_room);
			}
		}
		origin->add("no_clean_up",-1);
		origin->add("no_reset",-1);
		clear_user_room(origin,exit,msg);
		if (origin)
		{
			variables=(mapping)origin->query_entire_dbase();
			if (mapp(variables))
			{
				variable=keys(variables);
				for (j=0;j<sizeof(variable);j++)
				origin->delete(variable[j]);
			}
			variables=(mapping)origin->query_entire_temp_dbase();
			if (mapp(variables))
			{
				variable=keys(variables);
				for (j=0;j<sizeof(variable);j++)
				origin->delete_temp(variable[j]);
			}
		}
		return "清理随机地图完成！\n";
	}
	else
	return "寻找原始文件失败。\n";
}*/

int direction_number(int size,object the_origin)
{
	int result,random_dirs=random(4-(int)the_origin->query("total_layers"));
	if (size>3)
	result=4+random(4);
	else if (size>2)
	result=2+random(4);
	else if (size>1)
	result=2+random(2);
	else
	result=1+random(2);
	if (this_object()==the_origin)
	result+=2+random(2);
	result+=random_dirs;
	return result;
}

string op_position(string dir)
{
	for (int i=0;i<sizeof(connections);i++)
	if (dir==connections[i]["direction"])
	return connections[i]["op-direction"];
}

string position(object room_a,object room_b)
{
	string result;
	int x1,x2,y1,y2,z1,z2;
	x1=room_a->query("x");
	x2=room_b->query("x");
	y1=room_a->query("y");
	y2=room_b->query("y");
	z1=room_a->query("z");
	z2=room_b->query("z");
	if (x1>x2&&y1>y2)
	result="southwest";
	else if (x1>x2&&y1<y2)
	result="northwest";
	else if (x1<x2&&y1>y2)
	result="southeast";
	else if (x1<x2&&y1<y2)
	result="northeast";
	else 
	{
		if (z1=z2)
		{
			if (x1>x2&&y1==y2)
			result="west";
			else if (x1<x2&&y1=y2)
			result="east";
			else if (x1=x2&&y1>y2)
			result="south";
			else if (x1=x2&&y1<y2)
			result="north";
			else
			result="null";
		}
		else if (z1>z2)
		{
			if (x1>x2&&y1==y2)
			result="westdown";
			else if (x1<x2&&y1=y2)
			result="eastdown";
			else if (x1=x2&&y1>y2)
			result="southdown";
			else if (x1=x2&&y1<y2)
			result="northdown";
			else
			result="null";
		}
		else
		{
			if (x1>x2&&y1==y2)
			result="westup";
			else if (x1<x2&&y1=y2)
			result="eastup";
			else if (x1=x2&&y1>y2)
			result="southup";
			else if (x1=x2&&y1<y2)
			result="northup";
			else
			result="null";
		}
	}
	return result;
}
void process_in_fully_generate(object origin,object s_room,object n_room,object w_room,object e_room)
{
	object room;
	mapping prop_exit=(["exit1":({e_room,"east"}),"exit2":({s_room,"south"}),"exit3":({w_room,"west"}),"exit4":({n_room,"north"})]);
	string *exits=keys(prop_exit);
	for (int i=0;i<sizeof(exits);i++)
	{
		if (stringp(origin->query(exits[i]))&&objectp(room=load_object(origin->query(exits[i]))))
		{
			if (prop_exit[exits[i]][0]&&room!=prop_exit[exits[i]][0]&&room->isroom())
			{
				prop_exit[exits[i]][0]->set("exits/"+prop_exit[exits[i]][1],file_name(room));
				if (!origin->query("invisible"))
				room->set("exits/"+op_position(prop_exit[exits[i]][1]),file_name(prop_exit[exits[i]][0]));
				room->add("no_clean_up",1);
				room->add("no_reset",1);
				room->delete("realmap");
			}
		}
	}
}
int fully_generate(object origin)
{
	int i,j,e=0,w=0,s=0,n=0;
	object room,e_room,w_room,s_room,n_room,animal;
	origin->delete("generating");
	origin->set("fully_generated",1);
	origin->name(origin->query("overall_type"),origin);
	origin->delete("realmap");
	for (i=0;i<sizeof(origin->query("gene_rooms"));i++)
	{
		if (origin->query("gene_rooms/"+i))
			if (room=load_object(origin->query("gene_rooms/"+i)))
			{
				room->delete("realmap");
				room->set("type",origin->query("overall_type"));
				room->set_temp("mixed_long",room->query("long")+"\n");
				if (member_array((int)room->query("room_type"),drink_place)!=-1)
				{
					room->set("resource/water", 1);
					room->add_temp("mixed_long",HIW+"这里有足够的干净水源，你可以畅饮(drink)一番。\n"+NOR);
				}
				if (member_array((int)room->query("room_type"),fish_place)!=-1)
				{
					room->set("couldfish",1);
					room->add_temp("mixed_long",HIC+"这里似乎有不少鱼，如果有工具你可以钓到它们。\n"+NOR);
				}
				if (member_array((int)room->query("room_type"),look_place)!=-1)
				room->add_temp("mixed_long",CYN+"这里的景观无限壮丽，你可以欣赏(look view)一番。\n"+NOR);
				if (member_array((int)room->query("room_type"),zhai_place)!=-1)
				room->add_temp("mixed_long",HIG+"这里的树上长了一些野果，你可以摘下(zhai)果腹。\n"+NOR);
				if (member_array((int)room->query("room_type"),ji_place)!=-1)
				room->add_temp("mixed_long",HBGRN+"仙人掌的汁藏在内里，你可以把它挤(ji)出来，不过要小心不要刺到手了。\n"+NOR);
				if (member_array((int)room->query("room_type"),animal_place)!=-1)
				{
					animal=new("clone/npc/random_animal");
					animal->move(room);
				}
				if (room->query("extra_link"))
				for (j=0;j<sizeof(room->query("extra_link"));j++)
				room->add_temp("mixed_long",HIG+room->query("extra_link/"+j)+NOR);
				if (room->query("x")>e)
				{
					e=room->query("x");
					e_room=room;
				}
				if (room->query("x")<w)
				{
					w=room->query("x");
					w_room=room;
				}
				if (room->query("y")>n)
				{
					n=room->query("y");
					n_room=room;
				}
				if (room->query("y")<s)
				{
					s=room->query("y");
					s_room=room;
				}
			}
	}
	origin->set("most_south",s_room);
	origin->set("most_north",n_room);
	origin->set("most_east",e_room);
	origin->set("most_west",w_room);
	process_in_fully_generate(origin,s_room,n_room,w_room,e_room);
	get_pathway(origin);
	return 1;
}

int already_link(object room1,object room2)//检查2个房间是否已经联通
{
	mapping dirs=room1->query("exits");
	string *dir_name=keys(dirs);
	for (int i=0;i<sizeof(dir_name);i++)
	if (room1->query("exits/"+dir_name[i])==file_name(room2))
	return 1;
	return 0;
}

int link_edge(object room_a,object room_b,int x1,int x2,int y1,int y2,object origin)
{
	int i,j,k,l;
	string result,result2,dir,*dirs,*extra_dirs,*extra_name;
	mapping *conns=connections;
	object del_room,affect_room;
	result=position(room_a,room_b);
	result2=op_position(result);
	extra_dirs=extra_conn;
	extra_name=extra_conn_name;
	if (!already_link(room_a,room_b))
	{
		if (room_a->query("exits/"+result)||room_b->query("exits/"+result2)||result=="null")
		{
			for (j=0;j<sizeof(extra_dirs);j++)
			{
				if (!room_a->query("exits/"+extra_dirs[j])&&!room_b->query("exits/"+extra_dirs[j])&&!already_link(room_a,room_b))
				{
					room_a->set("exits/"+extra_dirs[j],file_name(room_b));
					room_b->set("exits/"+extra_dirs[j],file_name(room_a));
					l=sizeof(room_a->query("extra_link"));
					room_a->set("extra_link/"+l,"这里似乎有一条"+extra_name[j]+"通往"+room_b->query("short")+"。\n");
					l=sizeof(room_b->query("extra_link"));
					room_b->set("extra_link/"+l,"这里似乎有一条"+extra_name[j]+"通往"+room_a->query("short")+"。\n");
					k=sizeof(origin->query("link_edge_success_info"));
					origin->set("link_edge_success_info/"+k,"通过"+extra_dirs[j]+"，连接"+file_name(room_a)+"and"+file_name(room_b));
				}
			}
		}
		else
		{
			room_a->set("exits/"+result,file_name(room_b));
			room_b->set("exits/"+result2,file_name(room_a));
			j=sizeof(origin->query("link_edge_success_info"));
			origin->set("link_edge_success_info/"+j,"连接"+file_name(room_a)+"and"+file_name(room_b));
		}
	}
	if (!origin->query("start_fully_generate"))
	{
		origin->set("start_fully_generate",1);
		call_out("fully_generate",1,origin);
	}
	return 1;
}

int connect_by_order(object *rooms,object origin)
{
	int i;
	object *new_rooms=({});
	string *new_rooms_id=({});
	for (i=0;i<sizeof(rooms);i++)
	{
		if (rooms[i]&&rooms[i]->query("previous_clock_direction"))
		{
			rooms[i]->set("edge",1);
			new_rooms+=({rooms[i]});
			new_rooms_id+=({file_name(rooms[i])});
		}
	}
	origin->set("edge_rooms",new_rooms);
	origin->set("edge_rooms_id",new_rooms_id);
	if (sizeof(new_rooms)<2)
	{
		if (!origin->query("start_fully_generate"))
		{
			origin->set("start_fully_generate",1);
			call_out("fully_generate",1,origin);
		}
		return 1;
	}
	for (i=0;i<sizeof(new_rooms)-1;i++)
	link_edge(new_rooms[i],new_rooms[i+1],(int)new_rooms[i]->query("x"),(int)new_rooms[i+1]->query("x"),(int)new_rooms[i]->query("y"),(int)new_rooms[i+1]->query("y"),origin);
	i=sizeof(new_rooms)-1;
	if (i>2)//连成圈
	link_edge(new_rooms[i],new_rooms[0],(int)new_rooms[i]->query("x"),(int)new_rooms[0]->query("x"),(int)new_rooms[i]->query("y"),(int)new_rooms[0]->query("y"),origin);
	return 1;
}
void edge_rooms(object origin,string quarter)
{
	int one=-1,two=-2,three=-3,four=-4;
	object room,*room_1=({}),*room_2=({}),*room_3=({}),*room_4=({});
	if (quarter=="second_q"||quarter=="first_q")
	{
		one=1;
		two=2;
		three=3;
		four=4;
	}
	delete_temp("temp_swap/room_1");
	delete_temp("temp_swap/room_2");
	delete_temp("temp_swap/room_3");
	delete_temp("temp_swap/room_4");
	for (int i=0;i<sizeof(origin->query("outside_objects/"+quarter));i++)
	{
		room=origin->query("outside_objects/"+quarter+"/"+i);
		if (room->query("x")==one)
		room_1+=({room});
		if (room->query("x")==two)
		room_2+=({room});
		if (room->query("x")==three)
		room_3+=({room});
		if (room->query("x")==four)
		room_4+=({room});
	}
	set_temp("temp_swap/room_1",room_1);
	set_temp("temp_swap/room_2",room_2);
	set_temp("temp_swap/room_3",room_3);
	set_temp("temp_swap/room_4",room_4);
}
object edge_room(object *rooms,string mark)
{
	int tmp_y=0;
	object room;
	for (int i=0;i<sizeof(rooms);i++)
	{
		if (mark=="highest"&&rooms[i]->query("y")>tmp_y)
		{
			tmp_y=rooms[i]->query("y");
			room=rooms[i];
		}
		if (mark=="lowest"&&rooms[i]->query("y")<tmp_y)
		{
			tmp_y=rooms[i]->query("y");
			room=rooms[i];
		}
	}
	return room;
}
string connect_edge(object origin)
{
	object *room_1=({}),*room_2=({}),*room_3=({}),*room_4=({}),*rooms;
	object	room0,room1,room2,room3,room4,room5,room6,room7,room8,room9,room10,room11,room12,room13,room14,room15,room16,room17,room18,room19;
	if (origin->query("room_y_max"))
	room0=origin->query("room_y_max");
	if (origin->query("room_x_max"))
	room5=origin->query("room_x_max");
	if (origin->query("room_y_min"))
	room10=origin->query("room_y_min");
	if (origin->query("room_x_min"))
	room15=origin->query("room_x_min");
	if (sizeof(origin->query("outside_objects/first_q"))>1)
	{
		edge_rooms(origin,"first_q");
		room_1=query_temp("temp_swap/room_1");
		room_2=query_temp("temp_swap/room_2");
		room_3=query_temp("temp_swap/room_3");
		room_4=query_temp("temp_swap/room_4");
		if (sizeof(room_1))
		room1=edge_room(room_1,"highest");
		if (sizeof(room_2))
		room2=edge_room(room_2,"highest");
		if (sizeof(room_3))
		room3=edge_room(room_3,"highest");
		if (sizeof(room_4))
		room4=edge_room(room_4,"highest");
	}
	if (sizeof(origin->query("outside_objects/second_q"))>1)
	{
		edge_rooms(origin,"second_q");
		room_1=query_temp("temp_swap/room_1");
		room_2=query_temp("temp_swap/room_2");
		room_3=query_temp("temp_swap/room_3");
		room_4=query_temp("temp_swap/room_4");
		if (sizeof(room_1))
		room9=edge_room(room_1,"lowest");
		if (sizeof(room_2))
		room8=edge_room(room_2,"lowest");
		if (sizeof(room_3))
		room7=edge_room(room_3,"lowest");
		if (sizeof(room_4))
		room6=edge_room(room_4,"lowest");
	}
	if (sizeof(origin->query("outside_objects/third_q"))>1)
	{
		edge_rooms(origin,"third_q");
		room_1=query_temp("temp_swap/room_1");
		room_2=query_temp("temp_swap/room_2");
		room_3=query_temp("temp_swap/room_3");
		room_4=query_temp("temp_swap/room_4");
		if (sizeof(room_1))
		room11=edge_room(room_1,"lowest");
		if (sizeof(room_2))
		room12=edge_room(room_2,"lowest");
		if (sizeof(room_3))
		room13=edge_room(room_3,"lowest");
		if (sizeof(room_4))
		room14=edge_room(room_4,"lowest");
	}
	if (sizeof(origin->query("outside_objects/fourth_q"))>1)
	{
		edge_rooms(origin,"fourth_q");
		room_1=query_temp("temp_swap/room_1");
		room_2=query_temp("temp_swap/room_2");
		room_3=query_temp("temp_swap/room_3");
		room_4=query_temp("temp_swap/room_4");
		if (sizeof(room_1))
		room19=edge_room(room_1,"highest");
		if (sizeof(room_2))
		room18=edge_room(room_2,"highest");
		if (sizeof(room_3))
		room17=edge_room(room_3,"highest");
		if (sizeof(room_4))
		room16=edge_room(room_4,"highest");
	}
	rooms=({room0,room1,room2,room3,room4,room5,room6,room7,room8,room9,room10,room11,room12,room13,room14,room15,room16,room17,room18,room19,});
	origin->set("pre_edge_rooms",rooms);
	origin->set("calculate_edge_step1","划分象限成功");
	connect_by_order(rooms,origin);
	return "\n";
}


string obtain_edge(object origin)
{
	int i,j,min_layer,max_layer=0,flag=0,max_x=0,max_y=0,min_x=0,min_y=0;
	object *outer_layer=({}),*inner_layer=({});
	object room,room_y_max,room_y_min,room_x_max,room_x_min;
	min_layer=(int)origin->query("total_layers")-1;
	origin->set("calculate_edge_step1","ing……");
	for (i=0;i<sizeof(origin->query("gene_rooms"));i++)
	{
		if (load_object(origin->query("gene_rooms/"+i)))
		{
			room=load_object(origin->query("gene_rooms/"+i));
			if (room->query("x")==0&&room->query("y")!=0)
			{
				if (room->query("y")>max_y)
				{
					max_y=room->query("y");
					room_y_max=room;
				}
				if (room->query("y")<min_y)
				{
					min_y=room->query("y");
					room_y_min=room;
				}
			}
			else if (room->query("x")!=0&&room->query("y")==0)
			{
				if (room->query("x")>max_x)
				{
					max_x=room->query("x");
					room_x_max=room;
				}
				if (room->query("x")<min_x)
				{
					min_x=room->query("x");
					room_x_min=room;
				}
			}
			else if (room->query("not_edge"))
			{
				j=sizeof(origin->query("inside_objects"));
				origin->set("inside_objects/"+j,file_name(room)+"\t"+room->query("x")+"\t"+room->query("y"));
			}
			else
			{
				if (room->query("x")!=0&&room->query("y")!=0)
				{
					origin->set("calculate_edge_step1","获得外层objects");
					if (room->query("x")>0&&room->query("y")>0)
					{
						j=sizeof(origin->query("outside_objects/first_q"));
						origin->set("outside_objects/first_q/"+j,room);
					}
					else if (room->query("x")>0&&room->query("y")<0)
					{
						j=sizeof(origin->query("outside_objects/second_q"));
						origin->set("outside_objects/second_q/"+j,room);
					}
					else if (room->query("x")<0&&room->query("y")<0)
					{
						j=sizeof(origin->query("outside_objects/third_q"));
						origin->set("outside_objects/third_q/"+j,room);
					}
					else if (room->query("x")<0&&room->query("y")>0)
					{
						j=sizeof(origin->query("outside_objects/fourth_q"));
						origin->set("outside_objects/fourth_q/"+j,room);
					}
					outer_layer+=({room});
				}
				if (room->query("layer")==min_layer&&room->query("x")!=0&&room->query("y")!=0)
				{
					origin->set("calculate_edge_step1","获得内层objects");
					inner_layer+=({room});
					j=sizeof(origin->query("inner_objects"));
					origin->set("inner_objects/"+j,file_name(room)+"\t"+room->query("x")+"\t"+room->query("y"));
				}
			}
		}
		else
		{
			origin->set("calculate_edge_step1","no");
			return "计算边缘失败！\n";
		}
	}
		origin->set("calculate_edge_step1","yes");
		origin->set("room_x_max",room_x_max);
		origin->set("room_y_max",room_y_max);
		origin->set("room_x_min",room_x_min);
		origin->set("room_y_min",room_y_min);
		origin->set("calculate_edge_step1","分组成功");
		connect_edge(origin);
		return "计算边缘成功！\n";
}

mapping * acceptable_conns(int clock_dir)
{
	int i,*pool=({});
	mapping *conns=connections;
	mapping *result=({});
	if (clock_dir==1)
	pool=({8,1,2});
	else if (clock_dir==2)
	pool=({1,2,3});
	else if (clock_dir==3)
	pool=({2,3,4});
	else if (clock_dir==4)
	pool=({3,4,5});
	else if (clock_dir==5)
	pool=({4,5,6});
	else if (clock_dir==6)
	pool=({5,6,7});
	else if (clock_dir==7)
	pool=({6,7,8});
	else if (clock_dir==8)
	pool=({7,8,1});
	else
	pool=({0});
	if (!random(4))
	pool+=({9,10});
	for (i=0;i<sizeof(conns);i++)
	if (member_array(conns[i]["clock_direction"],pool)!=-1)
	result+=({conns[i]});
	return result;
}

int get_assign(string type,string conn_dir)
{
	if (conn_dir=="up")
	{
		if (type=="山地")
		return TYPE70;
		else if (type=="林地")
		return TYPE70+1;
		else if (type=="湖泽")
		return TYPE70+2;
		else if (type=="沙漠")
		return TYPE70+3;
		else if (type=="草原")
		return TYPE70+4;
		else
		return TYPE70+random(1+TYPE71-TYPE70);
	}
	if (conn_dir=="down")
	{
		if (type=="山地")
		return TYPE80;
		else if (type=="林地")
		return TYPE80+1;
		else if (type=="湖泽")
		return TYPE80+2;
		else if (type=="沙漠")
		return TYPE80+3;
		else if (type=="草原")
		return TYPE80+4;
		else
		return TYPE80+random(1+TYPE81-TYPE80);
	}
	return 0;
}

string generate_connection(object origin,int size,string type)
{
	int assign,clock_dir,i,dirs,delay=1;//每房间连接方向数
	mapping *temp_conns=({}),*conns=({});
	mapping connection,pre_exits;
	string conn_dir,*pre_exits_dirs=({});
	object new_room,new_origin,the_origin;
	the_origin=origin->query("origin_file");
	the_origin->set("found_origin",1);
	dirs=direction_number(size,the_origin);
	if (size<=0)
	{
		the_origin->set("generate_rooms_completed","层数到0.");
		return "层数小于0.\n";
	}
	else
	size-=1;
	pre_exits=origin->query("exits");
	if (pre_exits)
	pre_exits_dirs=keys(pre_exits);
	if (origin->query("no_extend"))//禁止延展，保持区域合理性
	return "网路末梢\n";
	if (!the_origin)
	{
		origin->set("record","failed");
		return "FAILED.\n";
	}
	if (origin->query("previous_clock_direction"))//选取合适方向，比如A房间 east to B房间，那么B房间延展方向应该为northeast,southeast或者east.
	{
		clock_dir=(int)origin->query("previous_clock_direction");
		conns=acceptable_conns(clock_dir);
	}
	else
	{
		conns=connections;
		for (i=8;i<16;i++)//方向8-15 降低原点出现改变海平面的几率
		if (random(10000)>4999&&connections[i]&&member_array(connections[i],conns)!=-1)
		conns-=({connections[i]});
		if (random(15))//极大降低原点出现up/down的概率
		{
			conns-=({connections[16]});
			conns-=({connections[17]});
		}
	}
	temp_conns=conns;
	for (i=0;i<sizeof(temp_conns);i++)//去掉原房间连接方向
	if (member_array(temp_conns[i]["direction"],pre_exits_dirs)!=-1)
	conns-=({temp_conns[i]});
	the_origin->delete("current_layer_rooms");
	for (i=0;i<dirs;i++)
	{
		if (sizeof(conns)<=0||(size<2&&!random(20)&&the_origin!=origin))//最外2层可能出现死路
		{
			the_origin->set("generate_rooms_completed","方向到0.");
			return "可用方向小于0.\n";
		}
		if (the_origin->blind_random_map())
		new_room=new(base_name(the_origin));
		else
		new_room=new("include/random_map");
		if (origin->query("real_dark"))
		new_room->set("real_dark",1);
		connection=conns[random(sizeof(conns))];
		conns-=({connection});
		conn_dir=connection["direction"];
		if (conn_dir=="up"||conn_dir=="down")
		{
			assign=get_assign(type,conn_dir);
			new_room->change_new_name(type,the_origin,assign);
		}
		else
		{
			new_room->change_new_name(type,the_origin);
		}
		record_maze_map(the_origin,origin,new_room,conn_dir);
		origin->set("exits/"+conn_dir,file_name(new_room));
		i=sizeof(the_origin->query("gene_rooms"));
		{
			the_origin->set("gene_rooms/"+i,file_name(new_room));
			the_origin->set("gene_objects/"+i,new_room);
		}
		i=sizeof(the_origin->query("current_layer_rooms"));
		the_origin->set("current_layer_rooms/"+i,file_name(new_room));
		new_room->set("layer",size);
		new_room->set("previous_clock_direction",connection["clock_direction"]);
		if (origin->query("previous_clock_direction")&&origin->query("previous_clock_direction")==new_room->query("previous_clock_direction"))
		origin->set("not_edge",1);
		new_room->set("previous_room",file_name(origin));
		new_room->set("previous_room_direction",conn_dir);
		new_room->set("origin_file",origin->query("origin_file"));
		new_room->set("exits/"+connection["op-direction"],file_name(origin));
		new_room->set("x",(int)origin->query("x")+connection["horizontal_increase"]);
		new_room->set("y",(int)origin->query("y")+connection["vertical_increase"]);
		new_room->set("z",(int)origin->query("z")+connection["level_increase"]);
		new_origin=new_room;
		delay+=1;
		new_origin->new_room(delay,new_origin,size,type);
	}
	return "初始化……\n";
}

int new_room(int delay,object new_origin,int size,string type)//delay为了保证瞬间运算量不至于过大
{
	if (!delay)
	delay=1;
	call_out("generate_connection",delay,new_origin,size,type);
	return 1;
}

int change_new_name(string type,object the_origin,int assign)
{
	int number;
	if (type=="山地")
	number=TYPE10+random(1+TYPE11-TYPE10);
	else if (type=="林地")
	number=TYPE20+random(1+TYPE21-TYPE20);
	else if (type=="湖泽")
	number=TYPE30+random(1+TYPE31-TYPE30);
	else if (type=="沙漠")
	number=TYPE40+random(1+TYPE41-TYPE40);
	else if (type=="草原")
	number=TYPE50+random(1+TYPE51-TYPE50);
	else
	number=TYPE10+random(1+TYPE61-TYPE10);
	if (assign)
	{
		number=assign;
		set("no_extend",1);
	}
	set("short", colors[number]+shorts[number]+NOR);
	set("long", "这里是一处"+shorts[number]+"，人迹罕至，也不知道你怎么会来到这里的。\n");
	set("room_type",number+1);
	return 1;
}

string leave_msg(object origin,object exit)
{
	if (origin->query("overall_type")=="山地")
	return WHT+"山上寒气渐重，此刻上山，显然不太明智，你退回了"+exit->query("short")+"。\n"+NOR;
	if (origin->query("overall_type")=="林地")
	return HIG+"林子里的光线渐渐被浓密的树冠遮蔽，什么都看不清楚，你退回了"+exit->query("short")+"。\n"+NOR;
	if (origin->query("overall_type")=="湖泽")
	return HIC+"此刻潮水即将上涌，还是快些离去为妙，你退回了"+exit->query("short")+"。\n"+NOR;
	if (origin->query("overall_type")=="沙漠")
	return HIY+"此刻沙漠里刮起了一阵风暴，不知不觉，你竟走到了"+exit->query("short")+"。\n"+NOR;
	if (origin->query("overall_type")=="草原")
	return HBGRN+"在无边无际的大草原里迷失了方向，你只好跟着着商队，来到了"+exit->query("short")+"。\n"+NOR;
	else
	return "地图更新，你被传送至"+exit->query("short")+"。\n";
}