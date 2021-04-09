inherit ROOM; //药山模板
#include <ansi.h>
#define __GENMINES__
#include "/d/southmountain/dongtianmu/random_clone.h"
#include "/d/southmountain/dongtianmu/herbmap.h"
#include "/d/southmountain/qingliangfeng/minemap.h"
int HerbPoints()//整个副本一次出现药材的房间数
{
	return 8;
}
int HerbRefreshRate()//多少秒刷新一次
{
	return 900;
}
string AREA()//本区域目录
{
	return "/d/southmountain/qingliangfeng/";
}
int MinePoints() 
{
	return 12;
}
int MineRefreshRate() 
{
	return 700;
}
void create() 
{ 
        set("short", "清凉峰");
        set("long", @LONG
这里是清凉峰。
LONG
        );
	
        set("exits", ([ /* sizeof() == 3 */
   //"south" : __DIR__"zoudao2.c",
]));
		set("searchCD",2);//副本内lookfor一步的cd
		set("drug_level",55);//这里是这个副本出现药材的级别在此以下，副本内可以升级的采药术在35+10以下。
		set("level_bonus",50);
		set("mine_level",40);//可以练的mining级别，实际为+10，即50.
		set("MineAppear",3);//出现的矿产的级别，一共8级。
		set("mine_level_bonus",30);//高于此级别有练级奖励。
		set("mine_assist_level",10);//低于10级也可能采到高级矿
        set("migong_name","清凉峰"),
        set("no_clean_up", 1);
        set("no_reset", 1);
		set("outdoors", "dongtianmu");
        setup();
		gene_features();
		//gene_mines();
}
string welcome_msg(object me)
{
	if (me->query_skill("alchemy",1)>1||me->query_skill("herbalism",1)>1)
	return HIG"【清凉峰】山中有很多药物，最高为55级药物，最高提升玩家采药术到65级。\n"NOR;
	if (me->query_skill("mining",1)>1||me->query_skill("smithing",1)>1)
	return HIG"【清凉峰】山中有很多矿石，最高为3级以下矿石碎片，最高提升玩家采矿术到50级。\n"NOR;
}
int start()
{
    object ob=this_object();
    //object exit1=load_object(__DIR__"shanlue1");
    object exit2=load_object(__DIR__"changgengshang");
    //object exit3=load_object(__DIR__"shanluw1");
    object exit4=load_object(__DIR__"taizijian");
    set("migong_name","清凉峰"),
    gene("山地",2,ob,0,exit2,0,exit4,0); //样本，随机迷宫8个参数，第一个为迷宫地貌类型，在include/random_map.h可查，第二个为迷宫复杂度，3为迷宫原点，4-7为出口，无出口则需补0,第八个参数为迷宫出口对于真实地图是否可见，不可见为1，可见为0
    return 1;
}

int over()
{
    clear_all();
	start();
    return 1;
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
	add_action("move_in_map","lookfor");
	add_action("do_gather","gather");
	add_action("move_MINE_map","shift");
	add_action("do_excavate","excavate");
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