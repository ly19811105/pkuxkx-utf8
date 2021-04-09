//jiaofeid.c
//Made by jason@pkuxkx
//2008.12.27

inherit F_DBASE;
inherit F_SAVE;


#include <ansi.h>
#include <localtime.h>

nosave int keynumber = 0;
nosave int maxkey = 0;
nosave int insertedkey = 0;

nosave int starttime = 0;

nosave object* allrooms = ({});
nosave object baoku;
nosave object startroom;
nosave string* allkiller = ({});
nosave mapping jiaofei_score = ([]);

nosave int intask = 0;
nosave int succeed = 0;
nosave int last_time_succeed_flag = 1;

//正在初始化中的标志
nosave int initprogress = 0;

nosave string roomlistfile = "/d/jiaofei/ROOMLIST";

//100为100%发放奖励，90为90%，最少有10%
//主要是受增援土匪的影响

//修改为10倍奖励，任务改为每周一次
nosave int rewardfactor = 1000;
//难度，100为正常，50是弱，150为强，200为神
//奖励是平方关系
nosave int difficulty = 100;

nosave int no_die_flag = 0;

void stop_task();
void kickusers();
void registerroom(object room);
void registerstartroom(object room);
void registerbaoku(object room);
void registeruser(string id);

void loadallrooms();

void checkstarttime();
void send_zengyuan();

//统计函数
void stat_start_task();
void stat_finish_task();
void stat_user_score_reward(string name, int score);
void stat_user_spy(string name, string action, int level);
void stat_user_quan(string name);
void stat_user_miehuo(string name);
void stat_baoku_reward(int reward);
void stat_baoku_gem(int level, string type);
void stat_baoku_weapon(int level, int type, int hole);
void stat_baoku_armor(int level, int type, int hole);
void stat_reporter(string filename);

void create()
{
	object room;
	string* roomfiles = ({});
	string filecontent;
	set("channel_id", HIY"临安剿匪总捕头"NOR);
	seteuid(ROOT_UID);

	set_temp("channel_environment", "/d/jiaofei/shanjiao");

	remove_call_out("checkstarttime");
	call_out("checkstarttime",60);	
	restore();
}

int addkey()
{
	keynumber++;
	if (keynumber >= maxkey)
	{
		keynumber = maxkey;
	}
	//	printf("keynumber:%d\r\n",keynumber);
	return keynumber;
}

varargs void announce(string msg, string tune)
{
	if (!tune) tune = "rw";
	CHANNEL_D->do_channel(this_object(), tune, msg);
}

//开门，所有钥匙都齐全就可以开门了。
void opendoor()
{
	int reward = 0;
	float factor = 1;
	int type = 0;
	int number = 0;
	int slot = 0;
	object obj;
	int level = 5;
	int i = 0;
	int j = 0;
	int weapontype = 0;
	int armortype = 0;
	int minkeynumber = maxkey;
	int usedtime = 0;

	int goldcost, dancost, weaponcost, armorcost, gemcost, ptzcost, wanzicost;

	string gemtype = "yan";

	if (!intask) return;

	insertedkey++;

	if (difficulty < 100)
	{
		minkeynumber = 2;
	}
	else if (difficulty == 100)
	{
		minkeynumber = 3;
	}
	else if (difficulty > 100 && difficulty < 200)
	{
		minkeynumber = 4;
	}
	else//200
	{
		minkeynumber = 5;
	}

	if (insertedkey >= minkeynumber)
	{

		succeed = 1;
		if (!objectp(baoku))
		{
			log_file("jiaofei.log", "宝库对象不存在。\r\n");
			stop_task();
			return;
		}

		//根据任务完成时间来决定宝库的价值，公式:
		//30分钟内完成获得系数为1，大于或者小于10分钟都线性处理
		//基数计算公式：
		//逐个房间统计：每个level为1的房间产生100点奖励.level 9为9*9*100点

		//1两黄金=20点奖励
		//2o的武器=8*1600*(level - 4)*(level - 4)点		--- 全部设置为2o武器，避免成为垃圾，相应提高cost
		//2o的盔甲=6*1600*(level - 4)*(level - 4)点		--- 全部设置为2o武器，避免成为垃圾，相应提高cost
		//宝石=2800*(level - 4)*(level - 4)点		
		//孽龙丹(2000 exp,1000 pot)=1500点
		//菩提子(100内力) = 2500
		//九转熊胆丸 = 1500点

		goldcost = 15;
		dancost = 1500;
		ptzcost = 2500;
		gemcost = 1900;
		armorcost = 6 * 1600;
		weaponcost = 8 * 1600;
		wanzicost = 1500;




		//总公式为：reward = sum(level*level*100)*(30*60)/time
		//30分钟这个参数可以适当调节。

		if (time() - starttime > 0)
		{
			usedtime = time() - starttime;
			if (usedtime < 15 * 60)
			{
				usedtime = 15 * 60;
			}
			factor = 2000.0 / usedtime;
		}
		else
		{
			//bug
			log_file("jiaofei.log", "完成时间小于开始时间\r\n");
			stop_task();
			return;
		}

		for (i = 0; i < sizeof(allrooms); i++)
		{
			if (objectp(allrooms[i]))
			{
				reward += allrooms[i]->level()*allrooms[i]->level() * 100 * factor;
			}
		}

		//奖励系数
		reward = reward / 100 * rewardfactor;
		//难度系数,立方关系。所以,50%难度奖励是1/8,200%难度是8		
		reward = reward / 100 * difficulty;
		reward = reward / 100 * difficulty;
		reward = reward / 100 * difficulty;

		reward = reward * SPEWEEK_D->query_jiaofei_bonus() / 100;

		//难度3的奖励为70%
		if (difficulty == 150)
		{
			reward = reward / 10 * 7;
		}
		//难度4的奖励减半
		if (difficulty == 200)
		{
			reward = reward / 2;
		}

		stat_baoku_reward(reward);

		printf("total reward is %d\n", reward);

		if (reward <= 0)
		{
			//bug
			log_file("jiaofei.log", "奖励为0。\r\n");
			stop_task();
			return;
		}

		//printf("all reward:%f\r\n",reward/factor);

		if (difficulty >= 100)//掉落天魔解体大法秘籍
		{
			if (random(difficulty) > 99 )
			{
				if (time() - query("auxiliary_present") > 86400)
				{
					set("auxiliary_present", time());
					obj = new("/obj/gem/tanjing");
					obj->move(baoku);
				}
				obj = new("/d/jiaofei/obj/jietibook");
				obj->move(baoku);
				message( "channel:rumor", HIM"【谣言】五指山剿匪快讯：五指山土匪宝库瑞气升腾，宝物出世！\n"NOR,users());
			}
		}

		if (difficulty > 100 && difficulty < 200 && (time() - starttime) < 1800)
		{
			//第三难度区间，产生3o,lvl 7的武器
			if (random(100) < 5)//20分之一的概率
			{
				weapontype = random(9) + 1;
				//消耗一半的 reward
				reward = reward / 2;
				obj = new("/obj/gem/weapon");
				obj->gen_weapon(weapontype, 9700, 9700);
				obj->set("forge/max", 3);
				obj->set("weapon_prop/damage", 200 + random(50));
				obj->set("weapon/damage", obj->query("weapon_prop/damage"));
				obj->move(baoku);
				announce(HIY"在土匪宝库发现一件极品装备！");
			}
		}
		else
		{
			if (difficulty >= 200 && (time() - starttime) < 1800)
			{
				//第四难度区间，产生两个3o,lvl 8的武器
				if (random(100) < 2)//50分之一的概率
				{
					//消耗全部的 reward
					reward = 0;
					weapontype = random(9) + 1;
					obj = new("/obj/gem/weapon");
					obj->gen_weapon(weapontype, 10000, 10000);
					obj->set("forge/max", 3);
					obj->set("weapon_prop/damage", 300 + random(100));
					obj->set("weapon/damage", obj->query("weapon_prop/damage"));
					obj->move(baoku);
					stat_baoku_weapon(level, obj->query("type"), obj->query("forge/max"));

					weapontype = random(9) + 1;
					obj = new("/obj/gem/weapon");
					obj->gen_weapon(weapontype, 10000, 10000);
					obj->set("forge/max", 3);
					obj->set("weapon_prop/damage", 300 + random(100));
					obj->set("weapon/damage", obj->query("weapon_prop/damage"));
					obj->move(baoku);
					stat_baoku_weapon(level, obj->query("type"), obj->query("forge/max"));

					announce(HIY"在土匪宝库发现一件极品装备！", "bd");
					announce(HIY"在土匪宝库又发现一件极品装备！", "bd");


				}
			}
		}

		j = 0;
		while (reward > 0)
		{
			printf("reward:%d,j:%d\n", reward, j);

			if (j++ % 100 == 0) reset_eval_cost();

			//随机产生各种奖励	
			number = 0;

			type = random(11);
			if (reward < gemcost)
			{
				type = 7;
			}
			switch (type)
			{
				//weapon			
			case 0:
			case 1:
			case 2:
			case 3:
				if (difficulty < 100)
				{
					level = 5;
				}
				else if (difficulty == 100)
				{
					level = 5 + random(2);
				}
				else if (difficulty < 200)
				{
					level = 6 + random(2);
				}
				else
				{
					level = 6 + random(3);
				}
				number = weaponcost*(level - 4)*(level - 4);
				if (reward < number) break;
				weapontype = random(9) + 1;
				obj = new("/obj/gem/weapon");

				switch (level)
				{
				case 5:
					obj->gen_weapon(weapontype, 8500, 8500);
					break;
				case 6:
					obj->gen_weapon(weapontype, 9300, 9300);
					break;
				case 7:
					obj->gen_weapon(weapontype, 9700, 9700);
					break;
				case 8:
					obj->gen_weapon(weapontype, 10000, 10000);
					break;
				default:
					break;
				}
				reward -= number;
				obj->set("forge/max", 2);
				obj->set("weapon_prop/damage", level*(30 + random(11)));
				obj->set("weapon/damage", obj->query("weapon_prop/damage"));
				//					obj->set_weapon_desc(obj);
				obj->move(baoku);
				stat_baoku_weapon(level, obj->query("type"), obj->query("forge/max"));
				break;
			case 4://armor	
			case 5:
			case 6:
				if (difficulty < 100)
				{
					level = 5;
				}
				else if (difficulty == 100)
				{
					level = 5 + random(2);
				}
				else if (difficulty < 200)
				{
					level = 6 + random(2);
				}
				else
				{
					level = 6 + random(3);
				}
				slot = random(2) + 2;
				number = armorcost*(level - 4)*(level - 4);
				if (slot == 3) number = number * 10;
				armortype = random(9) + 1;
				//盔甲防御最高，其他更低一些
				if (armortype != 1) number = number / 3;
				if (reward < number) break;

				obj = new("/obj/gem/armor");


				obj->set("type", armortype);
				switch (level)
				{
				case 5:
					obj->gen_armor(armortype, 8500, 8500);
					break;
				case 6:
					obj->gen_armor(armortype, 9300, 9300);
					break;
				case 7:
					obj->gen_armor(armortype, 9700, 9700);
					break;
				case 8:
					obj->gen_armor(armortype, 10000, 10000);
					break;
				default:
					break;
				}
				reward -= number;
				obj->set("forge/max", slot);
				if (armortype == 1)
				{
					obj->set("armor_prop/armor", level*(50 + random(11)));
				}
				else
				{
					obj->set("armor_prop/armor", level*(8 + random(7)));
				}
				obj->set("armor/armor", obj->query("armor_prop/armor"));
				//					obj->set_armor_desc(obj);
				obj->move(baoku);
				stat_baoku_armor(level, obj->query("type"), obj->query("forge/max"));
				break;
			case 7://gem	
			case 8:
			case 9:
			case 10:
				if (difficulty < 100)
				{
					level = 5;
				}
				else if (difficulty == 100)
				{
					level = 5 + random(2);
					if (random(15) == 0) level = 8;
				}
				else if (difficulty < 200)
				{
					level = 6 + random(2);
					if (random(10) == 0) level = 8;
				}
				else
				{
					level = 6 + random(3);
					if (random(5) == 0) level = 8;
				}

				number = gemcost*(level - 4)*(level - 4)*(level - 4)*(level - 4);
				if (reward < number) { reward = 0; }

				obj = new("/obj/gem/gem");
				//种类不太重要，直接设定
				i = random(20);
				if (i < 3) gemtype = "yan";
				else if (i < 6) gemtype = "mu";
				else if (i < 9) gemtype = "sui";
				else if (i < 12) gemtype = "jin";
				else if (i < 15) gemtype = "bing";
				else if (i < 16) gemtype = "gu";
				else if (i < 17) gemtype = "yu";
				else if (i < 18) gemtype = "jiao";
				else gemtype = "jia";

				switch (level)
				{
				case 5:
					obj->set_level(9939, 9939, gemtype);
					break;
				case 6:
					obj->set_level(9979, 9979, gemtype);
					break;
				case 7:
					obj->set_level(9994, 9994, gemtype);
					break;
				case 8:
					obj->set_level(10000, 10000, gemtype);
					break;
				default:
					break;
				}
				reward -= number;
				obj->move(baoku);
				stat_baoku_gem(level, gemtype);
				break;

			default:
				break;
			}
		}
		announce(HIW"宝库的大门打开了！", "bd");
		//把所有lastroom的通道打开
		for (i = 0; i < sizeof(allrooms); i++)
		{
			if (objectp(allrooms[i]) && allrooms[i]->islastroom())
			{
				allrooms[i]->setdoorstr(0);
			}
		}
		stop_task();
	}

}

//设置任务的出发房间。主要用于在任务开始前把玩家从各个房间踢出去，否则
//玩家可能呆在宝库或者其他地方不走。

void registerstartroom(object room)
{
	if (!undefinedp(startroom) || undefinedp(room)) return;
	//	printf("registerstartroom\r\n");
	startroom = room;
}

void registerbaoku(object room)
{
	if (!undefinedp(baoku) || undefinedp(room)) return;
	baoku = room;
}

void registeruser(string id)
{
	if (member_array(id, allkiller) == -1)
	{
		allkiller += ({ id });
	}
}

void registerroom(object room)
{
	object* tmproomarray;
	if (!objectp(room) || member_array(room, allrooms) != -1)
	{
		return;
	}

	allrooms += ({ room });

	if (room->islastroom())
	{
		maxkey++;
	}
}

int start_task_inroom_bystep(int roomindex)
{
	int t0 = time();
	int i = 0;
	int start_count = 0;

	if (roomindex == 0 || random(5) == 0)
	{
		announce(HIY"各路豪杰，请速到五指峰下会合，剿匪即将开始！");
	}

	for (i = roomindex; i < sizeof(allrooms) && start_count < 3; i++)
	{
		if (objectp(allrooms[i]))
		{
			allrooms[i]->start_task();
			start_count++;
		}
	}

	if (i == sizeof(allrooms))
	{
		//done!
		remove_call_out("start_task_inroom_bystep");
		intask = 1;
		succeed = 0;
		//printf("start rooms cost:%d\r\n",time()-t0);    	
		insertedkey = 0;
		keynumber = 0;

		remove_call_out("stop_task");
		//任务最长不能超过60分钟
		call_out("stop_task", 3600);
		announce(HIY"剿匪任务现在开始！各路人马即刻进攻！在山顶会合！");
		initprogress = 0;
		//派援兵
		if (difficulty > 100)
		{
			//普通难度以上才有增援土匪
			remove_call_out("send_zengyuan");
			//频率:150是5分钟一次，200是3分钟一次
			if (difficulty < 200)
			{
				call_out("send_zengyuan", 300);
			}
			else
			{
				call_out("send_zengyuan", 180);
			}
		}
	}
	else
	{
		remove_call_out("start_task_inroom_bystep");
		call_out("start_task_inroom_bystep", 5, i);
	}
}
void start_task()
{
	object p;

	int i = 0;
	if (intask) return;

	//在这里就开始计算开始时间，这样剿匪完成的时间有一个基数，而不会无限趋近0
	//这对于控制50%难度下的奖励非常重要。

	starttime = time();
	stat_start_task();

	initprogress = 1;

	remove_call_out("checkstarttime");

	for (i = 0; i < sizeof(allkiller); i++)
	{
		if (objectp(p = find_player(allkiller[i])))
		{
			p->delete_temp("jiaofei");
		}
	}

	//printf("delete marks cost:%d\r\n",time()-t1);

	allkiller = ({});
	jiaofei_score = ([]);

	loadallrooms();

	//printf("loadrooms cost:%d\r\n",time()-t1);

	kickusers();
	//printf("kick users cost:%d\r\n",time()-t1);


	//分次装载，以免系统停滞太久
	remove_call_out("start_task_inroom_bystep");
	call_out("start_task_inroom_bystep", 1, 0);

}

void stop_task()
{
	object p;
	if (!intask) return;

	remove_call_out("stop_task");
	remove_call_out("send_zengyuan");

	for (int i = 0; i < sizeof(allrooms); i++)
	{
		if (objectp(allrooms[i]))
		{
			allrooms[i]->stop_task();
		}
	}

	for (int i = 0; i < sizeof(allkiller); i++)
	{
		if (objectp(find_player(allkiller[i])))
		{
			jiaofei_score[allkiller[i]] = find_player(allkiller[i])->query_temp("jiaofei/score");
		}
		else
		{
			jiaofei_score[allkiller[i]] = 0;
		}
	}

	if (succeed)
	{
		announce(HIW"剿匪任务宣布结束！匪寇已经全部肃清！");
	}
	else
	{
		announce(HIW"因时日太长，粮草不济，剿匪任务宣布失败！");
	}

	last_time_succeed_flag = succeed;

	stat_finish_task();

	intask = 0;
	insertedkey = 0;
	keynumber = 0;
	succeed = 0;

	remove_call_out("checkstarttime");
	call_out("checkstarttime", 60);

}

void kickusers()
{
	object* allplayers;
	object env;
	string filename;

	if (undefinedp(startroom) || !objectp(startroom)) return;

	allplayers = users();

	for (int i = 0; i < sizeof(allplayers); i++)
	{
		if (objectp(allplayers[i]))
		{
			env = environment(allplayers[i]);
			if (objectp(env))
			{
				filename = file_name(env);
				if (strsrch(filename, "d/jiaofei") != -1)
				{
					if (strsrch(filename, "shanjiao") == -1 && strsrch(filename, "road1") == -1 && strsrch(filename, "road2") == -1 && strsrch(filename, "road3") == -1 && strsrch(filename, "lx") == -1)
					{
						tell_object(allplayers[i], "低沉的牛角号响起，似乎有人在进攻山寨。守卫急急忙忙的把你赶下了山。\r\n");
						allplayers[i]->move(startroom);
					}
				}
			}
		}
	}
}


int istaskstart()
{
	return intask;
}

void loadallrooms()
{
	//确保load所有房间
	string* roomfiles;
	object room;
	string filecontent = read_file(roomlistfile);
	roomfiles = explode(filecontent, "\n");
	for (int j = 0; j < sizeof(roomfiles); j++)
	{
		if (strwidth(roomfiles[j]) == 0) continue;
		roomfiles[j] = replace_string(roomfiles[j], "\n", "");
		roomfiles[j] = replace_string(roomfiles[j], "\r", "");
		roomfiles[j] = replace_string(roomfiles[j], "\t", "");
		roomfiles[j] = replace_string(roomfiles[j], " ", "");

		room = find_object(roomfiles[j]);
		if (!objectp(room))
		{
			if (catch (room = load_object(roomfiles[j])) != 0)
			{
				log_file("jiaofei.log", "load " + roomfiles[j] + "fail\n");
				continue;
			}
		}

		if (!objectp(room))
		{
			//printf(roomfiles[j]+"\r\n");
			continue;
		}

		if (room->istaskroom() == 1)
		{
			registerroom(room);
		}
		else if (room->isstartroom() == 1)
		{
			registerstartroom(room);
		}
		else if (room->isbaoku() == 1)
		{
			registerbaoku(room);
		}
	}
}

int query_last_time_succeed_flag()
{
	return last_time_succeed_flag;
}

int query_start_time()
{
	mixed* timeinfos;
	int hour;
	int minute;
	int mday;

	timeinfos = localtime(time());

	hour = timeinfos[LT_HOUR];
	minute = timeinfos[LT_MIN];
	mday = timeinfos[LT_MDAY];

	if (mday % 2 == 1)
	{
		return 21;
	}
	else
	{
		return 16;
	}
}

//每周六晚上21点开始
void checkstarttime()
{
	mixed* timeinfos;
	int hour;
	int minute;
	int mday;
	int wday;

	timeinfos = localtime(time());

	hour = timeinfos[LT_HOUR];
	minute = timeinfos[LT_MIN];
	mday = timeinfos[LT_MDAY];
	wday = timeinfos[LT_WDAY];

	if( (wday == 6 && hour == 21 && minute >= 0 && minute <= 2))
	{
		remove_call_out("checkstarttime");
		start_task();
	}
	else
	{
		if( (wday == 6 && hour == 20 && minute >= 45 && minute <= 46))
		{
			announce(HIR"五指山剿匪行动将在十五分钟后开始，各路英雄请做好准备！");
		}
		remove_call_out("checkstarttime");
		call_out("checkstarttime",60);
	}
}

int sort_array_by_score(string id1, string id2)
{
	object p1, p2;
	int int1, int2;
	p1 = find_player(id1);
	p2 = find_player(id2);

	if (undefinedp(p1) || !objectp(p1)) return 1;
	if (undefinedp(p2) || !objectp(p2)) return -1;

	if (sizeof(jiaofei_score))
	{
		int1 = jiaofei_score[id1];
		int2 = jiaofei_score[id2];
	}
	else
	{
		int1 = p1->query_temp("jiaofei/score");
		int2 = p2->query_temp("jiaofei/score");
	}

	if (!int1) return 1;
	if (!int2) return -1;

	if (int1 > int2)
	{
		return -1;
	}
	else if (int1 < int2)
	{
		return 1;
	}
	return 0;
}

//检查一个玩家的功勋排第几
int querysortnumber(string id)
{
	if (member_array(id, allkiller) == -1)
	{
		return -1;
	}
	allkiller = sort_array(allkiller, "sort_array_by_score");
	return member_array(id, allkiller);
}

int querykillernumber()
{
	return sizeof(allkiller);
}

int queryinitprogress()
{
	return initprogress;
}

int decreasereward(int dec)
{
	rewardfactor -= dec;
	if (rewardfactor < 10) rewardfactor = 10;
	return rewardfactor;
}

int getrewardfactor()
{
	return rewardfactor;
}


//for debug
void dump()
{
	printf("==========jiaofeid dump=============\n");
	printf("keynumber:%d,maxkey:%d,insertedkey:%d,starttime:%d,initprogress:%d,difficulty:%d\n", keynumber, maxkey, insertedkey, starttime, initprogress, difficulty);
	if (objectp(baoku))
	{
		printf("baoku:%s\n", file_name(baoku));
	}
	else
	{
		printf("no baoku\n");
	}
	if (objectp(startroom))
	{
		printf("startroom:%s\n", file_name(startroom));
	}
	else
	{
		printf("no startroom\n");
	}

	printf("intask:%d,succeed:%d,\n", intask, succeed);

	printf("\nallrooms:%d\n", sizeof(allrooms));
	for (int i = 0; i < sizeof(allrooms); i++)
	{
		if (!objectp(allrooms[i]))
		{
			printf("not objectp room\n");
			continue;
		}
		printf(file_name(allrooms[i]) + "\r\n");
		allrooms[i]->dump();
	}
	for (int i = 0; i < sizeof(allkiller); i++)
	{
		object p = find_player(allkiller[i]);
		printf("name:%s\n", allkiller[i]);
		if (!undefinedp(p) && objectp(p) && userp(p))
		{
			printf("xinren:%d,score:%d\n", p->query("jiaofei/xinren"), p->query_temp("jiaofei/score"));
		}
	}

}

//每次送5个援兵到start room去
void send_zengyuan()
{
	object obj;
	if (!objectp(startroom)) return;
	for (int i = 0; i < 5; i++)
	{
		obj = new("/d/jiaofei/npc/zengyuan_tufei");
		if (objectp(obj))
		{
			obj->setpath(i);
			obj->move(startroom);
		}
	}
	remove_call_out("send_zengyuan");
	if (difficulty > 100 && difficulty < 200)
	{
		call_out("send_zengyuan", 300);
	}
	else
	{
		call_out("send_zengyuan", 180);
	}
}

void setdifficulty(int diff)
{
	if (intask != 1 && initprogress != 1)
	{
		difficulty = diff;
	}
}

int getdifficulty()
{
	return difficulty;
}

int no_die()
{
	return no_die_flag;
}

int set_no_die(int no_die)
{
	if (no_die) no_die_flag = 1;
	else no_die_flag = 0;
	return no_die_flag;
}
/*
 * 保存统计任务数据
 * 统计分两部分：
 * 基础数据，每次任务的情况，包括
 * 启动时间，参与人员，难度，完成时间，最终奖励情况，每个人获得的奖励
 * 二次统计，包括
 * 一共参与人数，平均参与人数，平均奖励情况，奖励排行榜，平均完成时间
 * 这里似乎有个数据库蛮好的。哈哈
 */


string query_save_file()
{
	return "/data/jiaofeid";
}

void stat_start_task()
{
	string taskname = sprintf("jiaofei%d", starttime);
	set(taskname + "/starttime", starttime);
	set(taskname + "/difficulty", difficulty);
}

void stat_finish_task()
{
	string taskname = sprintf("jiaofei%d", starttime);
	set(taskname + "/finishtime", time());
	set(taskname + "/succeed", succeed);
	save();
}

void stat_user_score_reward(string name, int score)
{
	string taskname = sprintf("jiaofei%d", starttime);
	string keyname = taskname + "/users/" + name + "/score";
	add(keyname, score);
}

void stat_user_spy(string name, string action, int level)
{
	string taskname = sprintf("jiaofei%d", starttime);
	add(taskname + "/users/" + name + "/spy/" + sprintf("%s-%d", action, level), 1);
}

void stat_user_quan(string name)
{
	string taskname = sprintf("jiaofei%d", starttime);
	add(taskname + "/users/" + name + "/quan", 1);
}

void stat_user_miehuo(string name)
{
	string taskname = sprintf("jiaofei%d", starttime);
	add(taskname + "/users/" + name + "/miehuo", 1);
}

void stat_baoku_reward(int reward)
{
	string taskname = sprintf("jiaofei%d", starttime);
	set(taskname + "/baoku_reward/point", reward);
}

void stat_baoku_gem(int level, string type)
{
	string taskname = sprintf("jiaofei%d", starttime);
	add(taskname + "/baoku_reward/gem" + sprintf("%d-%s", level, type), 1);
}

void stat_baoku_weapon(int level, int type, int hole)
{
	string taskname = sprintf("jiaofei%d", starttime);
	add(taskname + "/baoku_reward/weapon" + sprintf("%d-%d-%d", level, type, hole), 1);
}

void stat_baoku_armor(int level, int type, int hole)
{
	string taskname = sprintf("jiaofei%d", starttime);
	add(taskname + "/baoku_reward/armor" + sprintf("%d-%d-%d", level, type, hole), 1);
}

int sort_task_stat(mapping item1, mapping item2)
{
	int key1, key2;
	if (undefinedp(item1) || undefinedp(item2))
	{
		return 0;
	}
	key1 = item1["starttime"];
	key2 = item2["starttime"];
	//key1,key2的格式是time_t
	if (key1 > key2) return 1;
	if (key1 == key2) return 0;
	if (key1 < key2) return -1;

}
void stat_dump_task(mapping data, string filename)
{
	mapping tmp, tmp2, tmp3;
	mixed* pair, pair2;
	string key, key2;
	mixed* allkeys;
	mixed* allkeys2;

	mixed* time = localtime(data["starttime"]);
	write_file(filename, "=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^\n");
	write_file(filename, sprintf("任务开始时间:%d年%d月%d日%d时%d分%d秒\n", time[LT_YEAR], time[LT_MON] + 1, time[LT_MDAY], time[LT_HOUR], time[LT_MIN], time[LT_SEC]));
	time = localtime(data["finishtime"]);
	write_file(filename, sprintf("任务结束时间:%d年%d月%d日%d时%d分%d秒\n", time[LT_YEAR], time[LT_MON] + 1, time[LT_MDAY], time[LT_HOUR], time[LT_MIN], time[LT_SEC]));
	write_file(filename, sprintf("耗时%d分钟\n", (data["finishtime"] - data["starttime"]) / 60));
	write_file(filename, sprintf("难度指数:%d\n", data["difficulty"]));
	if (data["succeed"] == 1){
		write_file(filename, "任务成功\n");
	}
	else {
		write_file(filename, "任务失败\n");
	}

	if (mapp(data["baoku_reward"]))
	{
		write_file(filename, sprintf("宝库最终奖励点数%d\n", data["baoku_reward"]["point"]));
		tmp = data["baoku_reward"];

		write_file(filename, sprintf("宝库宝石出现:\n"));
		allkeys = keys(tmp);
		for (int i = 0; i < sizeof(allkeys); i++)
		{
			key = allkeys[i];
			if (strsrch(key, "gem") != -1)
			{
				write_file(filename, key);
				write_file(filename, ":");
				write_file(filename, sprintf("数量:%d\n", tmp[key]));
			}
		}

		write_file(filename, sprintf("宝库武器出现:\n"));
		allkeys = keys(tmp);
		for (int i = 0; i < sizeof(allkeys); i++)
		{
			key = allkeys[i];
			if (strsrch(key, "weapon") != -1)
			{
				write_file(filename, key);
				write_file(filename, ":");
				write_file(filename, sprintf("数量:%d\n", tmp[key]));
			}
		}
		write_file(filename, sprintf("宝库盔甲出现:\n"));
		allkeys = keys(tmp);
		for (int i = 0; i < sizeof(allkeys); i++)
		{
			key = allkeys[i];
			if (strsrch(key, "armor") != -1)
			{
				write_file(filename, key);
				write_file(filename, ":");
				write_file(filename, sprintf("数量:%d\n", tmp[key]));
			}
		}
	}

	if (mapp(data["users"]))
	{
		write_file(filename, "任务参与者情况统计：\n");
		tmp = data["users"];

		allkeys = keys(tmp);
		for (int i = 0; i < sizeof(allkeys); i++)
		{
			key = allkeys[i];
			write_file(filename, "玩家ID:" + key + "\n");
			tmp2 = tmp[key];
			write_file(filename, sprintf("杀敌积分%d\n", tmp2["score"]));
			write_file(filename, sprintf("阻援完成%d次,灭火完成%d次\n", tmp2["quan"], tmp2["miehuo"]));

			if (mapp(tmp2["spy"]))
			{
				tmp3 = tmp2["spy"];
				write_file(filename, "卧底任务：\n");

				allkeys2 = keys(tmp3);
				for (int j = 0; j < sizeof(allkeys2); j++)
				{
					key2 = allkeys2[j];
					write_file(filename, key2 + sprintf("%d\n", tmp3[key2]));
				}
			}
			write_file(filename, "\n");

		}
	}
	write_file(filename, "=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^\n");
}

void stat_reporter(string filename)
{
	mixed* allkeys;
	string key;
	mixed* taskstats = ({});
	mixed* sorted_taskstats;
	mixed* time;
	//产生报表。
	if (intask || initprogress) return;
	if (!filename) filename = "/log/static/jiaofei";

	if (!write_file(filename, "jiaofei task stat reporter\n", 1)) return;
	restore();
	allkeys = keys(dbase);
	for (int i = 0; i < sizeof(allkeys); i++)
	{
		if (strsrch(allkeys[i], "jiaofei") != -1)
		{
			taskstats += ({ dbase[allkeys[i]] });
		}
	}

	sorted_taskstats = sort_array(taskstats, (:sort_task_stat : ));

	for (int i = 0; i < sizeof(sorted_taskstats); i++) {
		//	    printf("%d\n",sorted_taskstats[i]["starttime"]);
		//    time = localtime(sorted_taskstats[i]["starttime"]);    
		//  printf(sprintf("任务开始时间:%d年%d月%d日%d时%d分%d秒\n",time[LT_YEAR],time[LT_MON]+1,time[LT_MDAY],time[LT_HOUR],time[LT_MIN],time[LT_SEC]));	    
		stat_dump_task(sorted_taskstats[i], filename);
	}
}
