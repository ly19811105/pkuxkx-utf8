//jwhz.c
//甲午战争。（与历史有违之处在所难免了，呵呵）
//mudy

#define NONE    "n"
#define FRIEND  "f"
#define ENEMY   "e"
#define R_RATE  133 //整体调整奖励

inherit F_DBASE;
#include <ansi.h>
#include <localtime.h>

string *friend_file=({
	"/d/jwhz/jiashishi.c",
	"/d/jwhz/jiashishi_1.c"
	});
string *enemy_file=({
	"/d/jwhz/jiashishij.c",
	"/d/jwhz/jiashishij_1.c",	
	"/d/jwhz/jiashishij_2.c",
	});
string *pre_msg=({
});
void start_task();
void task_done(int type);
int update_all();
int enemy_move();
int enemy_fire();
int cancel();
int jiangli(int coe);
int inspect_victory();
void miehuo();
void checkstarttime();

void create()
{
	seteuid(getuid());
	set("channel_id",HIW"雪我国耻之甲午海战"NOR);
	set("wide",30);
	set("height",30);
	set("begin",0);
	set("victory",0);
    set_temp("channel_environment", "/d/yashan/waneast3");

	update_all();

	remove_call_out("checkstarttime");
	call_out("checkstarttime",60);	

}
void start_task()
{
	int wide,height;
	string *chuansheng;
	object cang,gangkou;
	CHANNEL_D->do_channel(this_object(), "rw", "甲午战争之牙山海战。", -1);
    CHANNEL_D->do_channel(this_object(), "rw", "请大家在牙山打开bd道，否则看不见海战信息。\n", -1);	
	CHANNEL_D->do_channel(this_object(), "bd", HIW"一段不能忘却的历史......\n", -1);
	wide=query("wide");
	height=query("height");
	set("player_count",0);
	set("begin",1);
	set("taskid",10+random(50));	
	//初始化船只
	gangkou=load_object("/d/yashan/waneast3.c");
	gangkou->set("no_reset",1);
	gangkou->delete("sink");
	gangkou->delete("sink_cause");
	write(sizeof(friend_file));
	for(int i=0;i<sizeof(friend_file);i++)
	{
		
		chuansheng=load_object(friend_file[i])->query("chuansheng");
		for(int j=0;j<sizeof(chuansheng);j++)
		{
			cang=load_object(chuansheng[j]);
			cang->renew();
			cang->set("no_reset",1);//不要更新
		}
	}
	for(int i=0;i<sizeof(enemy_file);i++)
	{
		chuansheng=load_object(enemy_file[i])->query("chuansheng");
		for(int j=0;j<sizeof(chuansheng);j++)
		{
			cang=load_object(chuansheng[j]);
			cang->renew();
			cang->set("no_reset");
		}
	}
	update_all();
	remove_call_out("pre_message1");
	call_out("pre_message1",5);
	enemy_fire();
/*	enemy_move();
	inspect_victory();*/
	return;
}
int pre_message1()
{
	CHANNEL_D->do_channel(this_object(), "bd", HIW"一段不可忘却的历史.....．", -1);
	remove_call_out("pre_message2");
	call_out("pre_message2",5);
	return 1;
}
int pre_message2()
{
	CHANNEL_D->do_channel(this_object(), "bd", HIW"一段被"+RED"血染红的篇章.....．", -1);
	remove_call_out("pre_message3");
	call_out("pre_message3",5);
	return 1;
}
int pre_message3()
{
	CHANNEL_D->do_channel(this_object(), "bd", WHT"一曲用"+HIC"泪"+"谱写的赞歌......", -1);
	remove_call_out("pre_message4");
	call_out("pre_message4",20);
	return 1;
}
int pre_message4()
{
	CHANNEL_D->do_channel(this_object(), "bd", WHT"一个没有人性的民族和一头熟睡中的雄狮之间的真实故事......", -1);
	remove_call_out("pre_message5");
	call_out("pre_message5",5);
	return 1;
}
int pre_message5()
{
	CHANNEL_D->do_channel(this_object(), "bd", HIY + "甲午战争之牙山海战。", -1);
	remove_call_out("pre_message6");
	call_out("pre_message6",10);
	return 1;
}
int pre_message6()
{
	CHANNEL_D->do_channel(this_object(), "bd", HIC + "明治天皇：开拓万里波涛，宣布国威于四方！", -1);
	CHANNEL_D->do_channel(this_object(), "bd", HIM + "日本侵略的矛头指向中国和朝鲜。", -1);
	CHANNEL_D->do_channel(this_object(), "bd", MAG + "一八六九年八月十五日。", -1);
	remove_call_out("pre_message7");
	call_out("pre_message7",5);
	return 1;
}
int pre_message7()
{
	CHANNEL_D->do_channel(this_object(), "bd", HIM + "日本魔爪伸入朝鲜，签订《江华条约》。", -1);
	CHANNEL_D->do_channel(this_object(), "bd", MAG + "一八七六年二月二十六日。", -1);
	remove_call_out("pre_message8");
	call_out("pre_message8",5);
	return 1;
}
int pre_message8()
{
	CHANNEL_D->do_channel(this_object(), "bd", WHT + "中日签订《天津条约》。", -1);
	CHANNEL_D->do_channel(this_object(), "bd", MAG + "一八八五年四月十八日。", -1);
	remove_call_out("pre_message9");
	call_out("pre_message9",5);
	return 1;
}
int pre_message9()
{
	CHANNEL_D->do_channel(this_object(), "bd", HIM + "李鸿章派军二千余人在牙山登陆。", -1);
	CHANNEL_D->do_channel(this_object(), "bd", MAG + "一八九四年六月四日。", -1);
	remove_call_out("pre_message10");
	call_out("pre_message10",5);
	return 1;
}
int pre_message10()
{
	CHANNEL_D->do_channel(this_object(), "bd", HIM+"日本进驻汉城。", -1);
	CHANNEL_D->do_channel(this_object(), "bd", MAG + "一八九四年六月十日。", -1);
	remove_call_out("pre_message11");
	call_out("pre_message11",5);
	return 1;
}
int pre_message11()
{
	CHANNEL_D->do_channel(this_object(), "bd", HIM + "朝鲜王宫沦陷，日本拘禁国王，成立傀儡政权。", -1);
	CHANNEL_D->do_channel(this_object(), "bd", MAG + "一八九四年七月二十三日。", -1);
	remove_call_out("pre_message12");
	call_out("pre_message12",5);
	return 1;
}
int pre_message12()
{
	CHANNEL_D->do_channel(this_object(), "bd", HIM + "日本海军侵略矛头指向中国，对中国不宣而战，派吉野、秋津洲、浪速三艘军舰，向牙山进犯！", -1);
	CHANNEL_D->do_channel(this_object(), "bd", HIW + "中国海军面临极大威胁!", -1);
	CHANNEL_D->do_channel(this_object(), "bd", BNK+RED + "甲午战争爆发！", -1);
	CHANNEL_D->do_channel(this_object(), "bd", MAG + "一八九四年七月二十五日。", -1);
	CHANNEL_D->do_channel(this_object(), "bd", HIR+ "牙山告急......", -1);
	remove_call_out("pre_message13");
	call_out("pre_message13",30);
	return 1;
}
int pre_message13()
{
	CHANNEL_D->do_channel(this_object(), "bd", HIR+ "牙山告急......", -1);
	remove_call_out("pre_message14");
	call_out("pre_message14",30);
	return 1;
}
int pre_message14()
{
	CHANNEL_D->do_channel(this_object(), "bd", HIR+ "牙山告急......", -1);
	remove_call_out("start_attack");
	call_out("start_attack",30);
	return 1;
}
int start_attack()
{
	CHANNEL_D->do_channel(this_object(), "bd", HIR + "日本发出战舰！", -1);
	enemy_move();
	inspect_victory();
	return 1;
}


string position(int i,int j)
{
	string si,sj,key;
	si=sprintf("%d",i);
	sj=sprintf("%d",j);
	key=si+"|"+sj;
	return query(key);
}
int write_position(int i,int j,string value)
{
	string si,sj,key;
	si=sprintf("%d",i);
	sj=sprintf("%d",j);
	key=si+"|"+sj;
	set(key,value);
	return 1;
}


int update_all()
{
	int wide,height;
	object obj;
	string si,sj,key;
	wide=query("wide");
	height=query("height");
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<wide;j++)
		{
			si=sprintf("%d",i);
			sj=sprintf("%d",j);
			key=si+"|"+sj;
			set(key,NONE);
		}
	}
	for(int i=0;i<sizeof(friend_file);i++)
	{
		obj=load_object(friend_file[i]);
		write_position(obj->query("y"),obj->query("x"),FRIEND);
	}
	for(int i=0;i<sizeof(enemy_file);i++)
	{
		obj=load_object(enemy_file[i]);
		write_position(obj->query("y"),obj->query("x"),ENEMY);
	}
	return 1;
}
int update_all_ships()
{
	object obj;
	for(int i=0;i<sizeof(friend_file);i++)
	{
		obj=load_object(friend_file[i]);
		if(!obj->query("sink"))
		write_position(obj->query("y"),obj->query("x"),FRIEND);
	}
	for(int i=0;i<sizeof(enemy_file);i++)
	{
		obj=load_object(enemy_file[i]);
		if(!obj->query("sink"))
		write_position(obj->query("y"),obj->query("x"),ENEMY);
	}
}
int enemy_move()
{
	object enemy;
	int player_count,shipcount;
	
	player_count = query("player_count");
	shipcount = 2;
	if ((player_count) <= 10)
		shipcount = 1;
	else if ((player_count) > 15)
			shipcount = 3;
	for(int i=0;i<shipcount;i++)
	{
		enemy=load_object(enemy_file[i]);
		enemy->auto_move();
	}
	return 1;
}
int enemy_fire()
{
	object enemy;
	for(int i=0;i<sizeof(enemy_file);i++)
	{
		enemy=load_object(enemy_file[i]);
		enemy->auto_fire();
	}
	return 1;
}

int inspect_victory()
{
	int china_remain,japan_remain;
	object china_chuan,japan_chuan;
	china_remain=0;
	japan_remain=0;
	for(int i=0;i<sizeof(friend_file);i++)
	{
		china_chuan=load_object(friend_file[i]);
		if(!china_chuan->query("sink"))
		{
			china_remain=1;
			break;
		}
	}
	for(int i=0;i<sizeof(enemy_file);i++)
	{
		japan_chuan=load_object(enemy_file[i]);
		if(!japan_chuan->query("sink"))
		{
			japan_remain=1;
			break;
		}
	}
	if(china_remain&&japan_remain)
	{
		remove_call_out("inspect_victory");
		call_out("inspect_victory",10);
		return 1;
	}
	if(china_remain&&!japan_remain)
	{//中国获胜
		CHANNEL_D->do_channel(this_object(), "bd", HIR + "日本舰队全军覆没！", -1);
		task_done(2);
		miehuo();
		return 1;
	}
	if(!china_remain&&japan_remain)
	{//日本获胜
		CHANNEL_D->do_channel(this_object(), "bd", HIR + "中国北洋舰队全军覆没！", -1);
		task_done(3);
		return 1;
	}
	if(!china_remain&&!japan_remain)
	{//同归于尽
		CHANNEL_D->do_channel(this_object(), "bd", HIR + "中日双方同归于尽！", -1);
		task_done(1);
		return 1;
	}

	return 1;
}
void miehuo()//一次性灭火。
{
	object chuan,cang;
	string *chuansheng;
	for( int i=0;i<sizeof(friend_file);i++)
	{
		chuan=load_object(friend_file[i]);
		chuansheng=chuan->query("chuansheng");
		for( int j=0;j<sizeof(chuansheng);j++)
		{
			cang=load_object(chuansheng[j]);
			if(cang->query("fire"))
			{
				cang->set("fire",0);
				message("vision",HIW"火渐渐自己熄灭了\n"NOR,cang);
			}
		}
	}
	return;
}

void task_done(int type)
{
	object cang,gangkou;
	string *chuansheng;
	gangkou=load_object("/d/yashan/waneast3.c");
	gangkou->delete("no_reset");
	for(int i=0;i<sizeof(friend_file);i++)
	{
		chuansheng=load_object(friend_file[i])->query("chuansheng");
		for(int j=0;j<sizeof(chuansheng);j++)
		{
			cang=load_object(chuansheng[j]);
			cang->delete("no_reset");//更新
		}
	}
	
	for(int i=0;i<sizeof(enemy_file);i++)
	{
		chuansheng=load_object(enemy_file[i])->query("chuansheng");
		for(int j=0;j<sizeof(chuansheng);j++)
		{
			cang=load_object(chuansheng[j]);
			cang->set("no_reset");
		}
	}
	set("begin",0);
	remove_call_out("post_msg1");
	call_out("post_msg1",5,type);

	remove_call_out("checkstarttime");
	call_out("checkstarttime",60);

	return ;
}
int post_msg1(int type)
{
	if(type==1)
		CHANNEL_D->do_channel(this_object(), "bd", HIM+ "甲午海战首战告捷，但是日军侵略的步伐仍在继续......", -1);
	else if(type==2)
		CHANNEL_D->do_channel(this_object(), "bd", HIM+ "一开始就以这样惨烈的战斗开始，注定了甲午之战悲剧的收场......", -1);
	else
		CHANNEL_D->do_channel(this_object(), "bd", HIM+ "清政府的无能导致了这场悲剧的发生，但是东方的雄狮终有它醒来的一天......", -1);
	remove_call_out("post_msg2");
	call_out("post_msg2",5,type);
	return 1;
}
int post_msg2(int type)
{
	CHANNEL_D->do_channel(this_object(), "bd", HIM+ "清政府被迫对日宣战。", -1);
	CHANNEL_D->do_channel(this_object(), "bd", MAG+ "一八九四年八月一日。", -1);
	remove_call_out("post_msg3");
	call_out("post_msg3",5,type);
	return 1;
}
int post_msg3(int type)
{
	CHANNEL_D->do_channel(this_object(), "bd", HIM+ "日军强渡鸭绿江，清军全线崩溃。", -1);
	CHANNEL_D->do_channel(this_object(), "bd", MAG+ "一八九四年十月二十五日。", -1);
	remove_call_out("post_msg4");
	call_out("post_msg4",5,type);
	return 1;
}
int post_msg4(int type)
{
	CHANNEL_D->do_channel(this_object(), "bd", HIM+ "九连、东安沦陷。", -1);
	CHANNEL_D->do_channel(this_object(), "bd", MAG+ "一八九四年十月二十六日。", -1);
	remove_call_out("post_msg5");
	call_out("post_msg5",5,type);
	return 1;
}
int post_msg5(int type)
{
	CHANNEL_D->do_channel(this_object(), "bd", HIM+ "金州沦陷。", -1);
	CHANNEL_D->do_channel(this_object(), "bd", MAG+ "一八九四年十一月六日。", -1);
	remove_call_out("post_msg6");
	call_out("post_msg6",5,type);
	return 1;
}
int post_msg6(int type)
{
	CHANNEL_D->do_channel(this_object(), "bd", HIM+ "大连沦陷。", -1);
	CHANNEL_D->do_channel(this_object(), "bd", MAG+ "一八九四年十一月八日。", -1);
	remove_call_out("post_msg7");
	call_out("post_msg7",5,type);
	return 1;
}
int post_msg7(int type)
{
	CHANNEL_D->do_channel(this_object(), "bd", HIM+ "旅顺沦陷，日军屠城四天，全市仅活"+RED"三十六"+HIM"人...", -1);
	CHANNEL_D->do_channel(this_object(), "bd", MAG+ "一八九四年十一月二十二日。", -1);
	remove_call_out("post_msg8");
	call_out("post_msg8",5,type);
	return 1;
}
int post_msg8(int type)
{
	CHANNEL_D->do_channel(this_object(), "bd", HIM+ "日军荣城龙须岛登陆，荣城沦陷。", -1);
	CHANNEL_D->do_channel(this_object(), "bd", MAG+ "一八九五年一月二十日。", -1);
	remove_call_out("post_msg9");
	call_out("post_msg9",5,type);
	return 1;
}
int post_msg9(int type)
{
	CHANNEL_D->do_channel(this_object(), "bd", HIM+ "威海卫沦陷。威海长峰人民自发抗击日军。", -1);
	CHANNEL_D->do_channel(this_object(), "bd", MAG+ "一八九五年二月三日。", -1);
	remove_call_out("post_msg10");
	call_out("post_msg10",5,type);
	return 1;
}
int post_msg10(int type)
{
	CHANNEL_D->do_channel(this_object(), "bd", HIM+ "日军偷袭，击沉我军来远、威远、宝筏三舰。下午炮战良久，日军退。", -1);
	CHANNEL_D->do_channel(this_object(), "bd", MAG+ "一八九五年二月六日。", -1);
	remove_call_out("post_msg11");
	call_out("post_msg11",5,type);
	return 1;
}
int post_msg11(int type)
{
	CHANNEL_D->do_channel(this_object(), "bd", HIM+ "英、法、俄洋员勾结无耻清军将领若干策划投降，丁汝昌严辞拒绝。", -1);
	CHANNEL_D->do_channel(this_object(), "bd", MAG+ "一八九五年二月七日。", -1);
	remove_call_out("post_msg12");
	call_out("post_msg12",5,type);
	return 1;
}
int post_msg12(int type)
{
	CHANNEL_D->do_channel(this_object(), "bd", HIM+ "丁汝昌再次拒绝帝国主义分子和汉奸的诱降。", -1);
	CHANNEL_D->do_channel(this_object(), "bd", MAG+ "一八九五年二月八日。", -1);
	remove_call_out("post_msg13");
	call_out("post_msg13",5,type);
	return 1;
}
int post_msg13(int type)
{
	CHANNEL_D->do_channel(this_object(), "bd", HIM+ "靖远在日军三十多艘军舰的攻击下，中炮搁浅。", -1);
	CHANNEL_D->do_channel(this_object(), "bd", MAG+ "一八九五年二月九日。", -1);
	remove_call_out("post_msg14");
	call_out("post_msg14",5,type);
	return 1;
}
int post_msg14(int type)
{
	CHANNEL_D->do_channel(this_object(), "bd", HIM+ "丁汝昌再次拒降，定远炮弹打完，丁汝昌、刘步蟾下令炸毁定远，同日夜，刘步蟾自杀。",-1);
	CHANNEL_D->do_channel(this_object(), "bd", MAG+ "一八九五年二月十日。", -1);
	remove_call_out("post_msg15");
	call_out("post_msg15",5,type);
	return 1;
}
int post_msg15(int type)
{
	CHANNEL_D->do_channel(this_object(), "bd", HIM+ "刘公岛弹药用尽，援兵无望，丁汝昌再次拒降，当夜自杀殉国。", -1);
	CHANNEL_D->do_channel(this_object(), "bd", MAG+ "一八九五年二月十一日。", -1);
	remove_call_out("post_msg16");
	call_out("post_msg16",5,type);
	return 1;
}
int post_msg16(int type)
{
	CHANNEL_D->do_channel(this_object(), "bd", HIM+ "刘公岛护军统领张文宣反对投降，愤而自杀。", -1);
	CHANNEL_D->do_channel(this_object(), "bd", MAG+ "一八九五年二月十二日。", -1);
	remove_call_out("post_msg17");
	call_out("post_msg17",5,type);
	return 1;
}
int post_msg17(int type)
{
	CHANNEL_D->do_channel(this_object(), "bd", HIM+ "刘公岛沦陷。", -1);
	CHANNEL_D->do_channel(this_object(), "bd", MAG+ "一八九五年二月十七日。", -1);
	remove_call_out("post_msg18");
	call_out("post_msg18",5,type);
	return 1;
}
int post_msg18(int type)
{
	CHANNEL_D->do_channel(this_object(), "bd", WHT+ "《中日马关条约》签订。", -1);
	CHANNEL_D->do_channel(this_object(), "bd", MAG+ "一八九五年四月十七日。", -1);
	remove_call_out("post_msg19");
	call_out("post_msg19",5,type);
	return 1;
}
int post_msg19(int type)
{
	CHANNEL_D->do_channel(this_object(), "bd", RED+ "威海人民此后开展了长达三年的反抗日军的斗争，迫使日军于一八九八年从威海撤退。", -1);
	remove_call_out("post_msg20");
	call_out("post_msg20",5,type);
	return 1;
}
int post_msg20(int type)
{
	CHANNEL_D->do_channel(this_object(), "bd", HIM+ "历史不能责备......", -1);
	remove_call_out("post_msg21");
	call_out("post_msg21",5,type);
	return 1;
}
int post_msg21(int type)
{
	CHANNEL_D->do_channel(this_object(), "bd", HIM+ "历史不堪责备......", -1);
	remove_call_out("post_msg22");
	call_out("post_msg22",5,type);
	return 1;
}
int post_msg22(int type)
{
	CHANNEL_D->do_channel(this_object(), "bd", HIM+ "但历史不能忘记！", -1);
	CHANNEL_D->do_channel(this_object(), "bd", HIC+ "让我们齐声唱同一首歌，那就是......", -1);
	remove_call_out("post_msg23");
	call_out("post_msg23",5,type);
	return 1;
}
int post_msg23(int type)
{
	CHANNEL_D->do_channel(this_object(), "bd", HIC+ "就是......", -1);
	remove_call_out("final");
	call_out("final",5,type);
	return 1;
}
int final(int type)
{
	object *all_users;
	all_users=users();
/*
	for(int i=0;i<sizeof(all_users);i++)
	{
                message( "channel:" + "baowei",HIC+ "【闲聊】"+all_users[i]->query("name")+HIC"挥舞大刀，引吭高歌：“大刀－－向、鬼子的头上砍去！”\n\n"NOR,users());
		//all_users[i]->command("chat* sing2");
	}
*/
    CHANNEL_D->do_channel(this_object(), "bd", HIR"“大刀向鬼子们的头上砍去，北侠的弟兄们，抗战的一天来到了，抗战的一天来到了！", -1);
    CHANNEL_D->do_channel(this_object(), "bd", HIR"前面有东北的义勇军，后面有全国的老百姓，咱们北侠不是孤军。", -1);
    CHANNEL_D->do_channel(this_object(), "bd", HIR"看准那敌人，把它消灭！把它消灭！冲啊！大刀向鬼子们的头上砍去，杀！”", -1);
    remove_call_out("final_jiangli");
	call_out("final_jiangli",10,type);
	return 1;
}
int final_jiangli(int type)
{
	CHANNEL_D->do_channel(this_object(), "rw", "甲午海战任务全部结束！", -1);
	if(type==3)
		cancel();
	else
		jiangli(type);
	return 1;
}

int jiangli(int coe)
{
	object *all_users;
	int number;
	number=0;
	all_users=users();
	for(int i=0;i<sizeof(all_users);i++)
	{	


		if(all_users[i]->query_temp("jwhz/shooted")
			||all_users[i]->query_temp("jwhz/zhuang")
			||all_users[i]->query_temp("jwhz/jiuhuo")
			||all_users[i]->query_temp("jwhz/jiashi")
			||all_users[i]->query_temp("jwhz/kongzhi")
			)
		{
			number++;
			call_out("jiangli_single",number,all_users[i],coe);
		}
	}
	return 1;
}
int jiangli_single(object me,int coe)
{
	int jiangli,myexp,exp,rep,pot;
  //奖励由whuan调整，2009-1-19
	//*******定义为新手任务，3m之前奖励exp，3m之后换成rep********//
	myexp=me->query("combat_exp");
	jiangli = me->query_temp("jwhz/jiashi")*200; 
	jiangli +=me->query_temp("jwhz/zhuang")*1000; 
	jiangli +=me->query_temp("jwhz/jiuhuo")*50;
	jiangli +=me->query_temp("jwhz/shooted")*100;
	if(me->query_temp("jwhz/kongzhi")>=50)
		jiangli += 1000;
	else
		jiangli +=me->query_temp("jwhz/kongzhi")*20;	
	
	jiangli=jiangli*coe;
	jiangli=jiangli*R_RATE/100;	
	if(myexp>=3000000)
	{ 
		rep=jiangli;
	  CHANNEL_D->do_channel(this_object(), "rw", "由于"+me->query("name")+"在甲午战争中功勋卓著,特奖励"+ "声望"+chinese_number(rep)+"点！", -1);
	    me->add("repute",rep);		
	}
	else
	{
		exp=jiangli;
		pot=jiangli/4;
		rep=jiangli/5;
		if (me->query("exp/haizhan") > myexp/5)
		{
			rep *= 5;
		    CHANNEL_D->do_channel(this_object(), "rw", "由于"+me->query("name")+"在甲午战争中功勋卓著,特奖励"+ "声望"+chinese_number(rep)+"点！", -1);
			me->add("repute",rep);		
		}
		else
		{
		  CHANNEL_D->do_channel(this_object(), "rw", "由于"+me->query("name")+"在甲午战争中功勋卓著,特奖励"+ "经验"+chinese_number(exp)+"点，"
								+ "潜能"+chinese_number(pot)+"点，"+ "声望"+chinese_number(rep)+"点！", -1);			
			me->add("combat_exp",exp);		
			me->add("potential",pot);	
			me->add("exp/haizhan", exp);
			me->add("repute",rep);		
		}
	}
	me->delete_temp("jwhz");
	return 1;
}
int cancel()
{
	object *all_users;
	int number;
	number=0;
	all_users=users();
	for(int i=0;i<sizeof(all_users);i++)
	{
		if(all_users[i]->query_temp("jwhz/shooted")
			||all_users[i]->query_temp("jwhz/zhuang")
			||all_users[i]->query_temp("jwhz/kongzhi")
			||all_users[i]->query_temp("jwhz/jiashi")
			||all_users[i]->query_temp("jwhz/jiuhuo")
			)
			all_users[i]->delete_temp("jwhz");
	}
	return 1;
}
	


//双号21点开始，单号16点开始
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

	if( (mday%2 == 0 && hour == 21 && minute >= 0 && minute <= 10) || (mday%2 == 1 && hour == 12 && minute >= 0 && minute <= 10))
	{
			remove_call_out("checkstarttime");
			start_task();
	}
	else
    {
        	remove_call_out("checkstarttime");
        	call_out("checkstarttime",60);
    }
}
