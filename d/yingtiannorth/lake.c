inherit ROOM; //药山模板
#include <ansi.h>
#include "/d/southmountain/dongtianmu/random_clone.h"
#include "/d/southmountain/dongtianmu/herbmap.h"
int HerbPoints()//整个副本一次出现药材的房间数
{
	return 8;
}
int HerbRefreshRate()//多少秒刷新一次
{
	return 600;
}
string AREA()//本区域目录
{
	return "/d/yingtiannorth/";
}

void create() 
{ 
        set("short", "东天目");
        set("long", @LONG
这里是东天目山的主峰。
LONG
        );
	
        set("exits", ([ /* sizeof() == 3 */
   //"south" : __DIR__"zoudao2.c",
]));
		set("searchCD",3);//副本内lookfor一步的cd
		set("drug_level",55);//这里是这个副本出现药材的级别在此以下，副本内可以升级的采药术在35+10以下。
		set("level_bonus",45);
        set("migong_name","大湖"),
        set("no_clean_up", 1);
        set("no_reset", 1);
		set("no_task",1);
		set("outdoors", "lake");
        setup();
		gene_features();
}
string welcome_msg(object me)
{
	if (me->query_skill("alchemy",1)>1||me->query_skill("herbalism",1)>1)
	return HIC"【大湖】这里有很多药材，最高为55级药材，最高提升玩家采药术到65级。\n"NOR;
}
int start()
{
    object ob=this_object();
    object exit1=load_object(__DIR__"lakee1");
    object exit2=load_object("/d/yingtiansouth/lakes1");
    //object exit3=load_object(__DIR__"wuxiangw1");
    object exit4=load_object(__DIR__"laken1");
    set("migong_name","大湖"),
    gene("湖泽",2,ob,exit1,exit2,0,exit4,0); //样本，随机迷宫8个参数，第一个为迷宫地貌类型，在include/random_map.h可查，第二个为迷宫复杂度，3为迷宫原点，4-7为出口，无出口则需补0,第八个参数为迷宫出口对于真实地图是否可见，不可见为1，可见为0
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