//北大侠客行终极秘密－－八虎朝龙
//Made by jason@pkuxkx
//2001.3.28
/*
故事梗概：传说东汉年间有一大将，征战南北，战功赫赫，
因为为人正直，遭宦官排挤，最后竟然被满门抄斩，唯独
其幼子在一员家将的拼死保护下冲出重围，从此流落山林。
此子成年之后，立志为家父报仇，苦心钻研其父留下的武
学心得，加上其天资非凡，又得武林前辈相助，最终练就
了一生绝世武功，虽然最后并没有能够刺杀皇帝，但是其
武学成就登峰造极，千百年来，未有人能达到他十分之一
的境界。相传他有八大弟子，各自学有一门武功，岁月沧
桑，如今早已不知下落，而这八门据称骇惊天人的武功也
成为江湖传说中的秘密。

时间很快到了北宋年间，朝廷懦弱无能，辽夏虎视耽耽，
政局动荡，江湖风雨也变幻莫测，作为武林支柱的少林
突然在一夜之间被人血洗，很多前辈高手被人暗杀，而且
手法各不相同，唯一相同的就是：所有的人都是一招之间
被人杀死，事前半点都没有察觉到危险，死时脸上还保持
着当时正常的表情。一时之间，江湖人人自危，流言纷纷
而且，有人说是一个杀手组织出现了，也有人说是某个绝
世高手想杀尽天下高手，自立天下第一，还有人说是辽夏
朝廷雇佣高级杀手刺杀北宋高手，以为消灭北宋作准备。
但是这个传言很快就证明不对了，因为西夏一品堂和辽国
黑龙殿的高手也遭到了暗杀。只有少林的一个小和尚曾经
见过刺客的一点形象，是一个穿着红色袍子的人，用的兵
器是一个银环，圆润无刃，但是人一碰上就死，此人招式
怪异，且内力之浑厚连少林方丈都只挡了不到半柱香的时
间，而这时间少林罗汉堂一众高手竟然无人能够插手帮忙。
眼见方丈气竭而死。

而身负绝学的你，发誓要铲除这幕后的黑手。

*/
/*迷题情节：系统定时，每30年产生一次，就是一个月，
系统控制所有在少林的NPC突然死亡，玩家昏迷，只留下
某个特定的小和尚。发出大量谣言，谁谁谁被神秘刺客
杀死，最后武林盟主发出确认Chat：少林灭门。
紧接着谣言武林盟主被杀。还有一品堂的死讯，系统设
置一个参数，表明处在这个任务期，10年后,或者有人
完成任务则消除。扬州店小二可以ask出一点点情节，比
如少林小和尚还活着。小和尚可以说出杀手的情况。小和
尚开始出现在杀手帮，random_move。然后系统挑选3M以上
的在线玩家8人，经过考验,就是有人来杀，过关的挑选去一
个地方，闭关练功，学成绝世武功一门。出来后继续寻找黑
手，收集地图的八部分，全了以后就可以找到，杀死他和八
大高手，通关，成为八高手之一，npc。玩家得到一件宝物，
考虑为归魂剑，英雄剑这种武器的克星，而且降低所有武器
的damage,和armor的防御。失败的结果：内力打为0，经验
减1M。
*/
/*
细节迷题：上少林，设置一个参数，但是不给任何提示，
下山路上遭到狙杀，一招能不死，就再加一个参数，刺客
约定子时华山之颠有人见他。到了华山后，并没有人，再
次遇到刺杀，这次被打晕，掉入山崖。醒来后在一片新的
区域。有八个方向，去了就不能回头，各自找到一个人。
见到此人后，他向你展示一招绝世武功，要你去杀五大高手，
全部得手后回来见他，路上看到有人放火杀人，不能管，否则
失败。完成杀人任务，他会收你为挂名弟子，然后让为他
找一个宝物，比如：英雄剑，伏魔刀，金丝宝甲，普梯子，
等等，这样的任务作了一些后，他带你进一个山洞，在那里
学会了一门新的武功（一共八种）。学成出来后，让你
去剿灭一个门派（选定8个，武当，峨嵋，华山，明教，
日月神教，全真，桃花岛，星宿）,在这个过程中收集地图的
八个部分，完成后可以见到老大。老大说出全部的计划：剿
灭天下门派，自立第一，下一个任务是刺杀皇帝，一共三个。
都要杀掉。见到老大的玩家必须比武才能留下一个来。这里
你可以选择say no,然后就会杀你，基本上没有活的可能。如
果成功杀掉，得到八种武功的全本，全部学会。如果say yes
，杀掉皇帝后，会有机会窥探到老大在读的书，参透它，费掉
所学的武功，学会一门新的武功，可以融会贯通，并且得到宝
物。到这里，情节结束。
*/

#include <ansi.h>

inherit F_DBASE;
inherit F_SAVE;

int task_begin=0;
int last_start=0;
string kill_msg=
({
	"一条白色的身影突然从暗处闪现，剑光一闪...\n",
	"你听见暗器破空的声音，眼前一道银光闪过...\n",
	"你突然听见一声惨叫，急忙回头一看,\n",
	"你闻到一股淡淡的香味，往四周看了看,\n",
	"一条高大的人影向着你的方向直扑过来，速度快的你看不清他的脸！！\n",
	"你突然看到剑光闪起，一闪，再闪，再闪！！！\n",
});

int check_time();
int start_final_task();
int end_final_task();
int is_task_begin();
int query_last_start_time();

string query_save_file()
{
	return DATA_DIR+"final_task/final_taskd";
}
void create()
{
	if(!restore())
	set("channeld_id","北大侠客行终极任务");
	check_time();
}

int check_time()
{
	mixed *nowtime=localtime(time());
	if(task_begin==0)
	{
		if(nowtime[LT_HOUR]>8&&nowtime[LT_HOUR]<22
		&&(time()-last_start)>86400*30)
		{
			start_final_task();
			remove_call_out("check_time");
			call_out("check_time",3600);
		}
	}
	else
	{
		if(nowtime[LT_HOUR]>8&&nowtime[LT_HOUR]<22
		&&(time()-last_start)>86400*10)
		{
			end_final_task();
			remove_call_out("check_time");
			call_out("check_time",3600);
		}
	}
	return 1;
}

int start_final_task()
{
	string* files;
	mapping npc_list;
	files=get_dir("/d/shaolin/*.c");
	object room,*inv,fz,fzroom;
	for(int i=0;i<sizeof(files);i++)
	{
		int err;
		string roomfile="/d/shaolin/"+files[i];
		string *key;
		reset_eval_cost();
		if(file_size(roomfile) continue;
		err=catch(roomfile,"???");
		if(err)
		{
			log_file("final_task","cannt load object "+roomfile+"\n");
			continue;
		}
		else
		{
			if(!objectp(room=load_object(roomfile))) 
			{
				log_file("final_task","cannt load object "+roomfile+"\n");
				continue;
			}
		}
		npc_list=room->query("objects");
		if(!mapp(npc_list)||sizeof(npc_list)<=0) continue;
		inv=all_inventory(room);
		key=keys(npc_list);
		for(int j=0;j<sizeof(inv);j++)
		{
			reset_eval_cost();
			if(!inv[j]->is_npc()) continue;
			if((member_array(base_name(inv[j]),key)!=-1
			||member_array(base_name(inv[j])+".c",key)!=-1)&&
			inv[i]->query("family/family_name")=="少林派"
			&&base_name(inv[i])!="/kungfu/class/shaolin/xuan-ci")
			{
				inv[i]->clean_up_enemy();
				inv[i]->delete_temp("last_damage_from");
				inv[i]->start_busy(0);
				message("vision",kill_msg[random(sizeof(kill_msg))],
				room);
				message_vision("$N惨叫一声，倒在地上。\n",inv[i]);
				inv[i]->die();
				message("vision",HIW"【门派】"NOR+"玄慈大师："+
				HIY"我派弟子"+inv[i]->name()+"被人杀害，本座发出江湖追杀令\n"+
				"定要擒拿凶手！！\n"NOR,users());
			}
		}
			
		
	}
	if(!objecpt(fzroom=load_object("/d/shaolin/dxbdian"))) 
	{
		log_file("final_task","cannt load room /d/shaolin/dxbdian");
		return 0;
	}
	else
	{
		if(!objectp(fz=present("xuanci dashi",fzroom)))
			fz=new("/kungfu/class/shaolin/xuan-ci");
		fz->move(fzroom);
		message("vision",kill_msg[random(sizeof(kill_msg))],
				fzroom);
		fz->die();
		CHANNLE_D->do_channel("rumor",HIW"少林方丈玄慈大师被神秘高手暗杀身亡！！\n"NOR);
	}
	message("vision",HIR"【武林盟主令】"NOR+"东方白："+"本盟主已经证实，少林方丈\n"+
	"玄慈大师遇刺身亡，少林满门被杀，少林一派，血脉尽断。\n");
	CHANNLE_D->do_channel("rumor",HIW"武林盟主东方白昨日暴毙！！\n"NOR);
	task_begin=1;
	last_start=time();
	save();
	return 1;
}

int end_final_task()
{
	task_begin=0;
	save();
	return 1;
}

int is_task_begin()
{
	return task_begin;
}

int query_task_start_time()
{
	return last_start_time;
}






