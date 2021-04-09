inherit ROOM; //药山模板
#include <ansi.h>
#define __GENHERB__
#include "/d/southmountain/dongtianmu/random_clone.h"
#include "/d/southmountain/dongtianmu/herbmap.h"
int HerbPoints()//整个副本一次出现药材的房间数
{
	return 10;
}
int HerbRefreshRate()//多少秒刷新一次
{
	return 800;
}
string AREA()//本区域目录
{
	return "/d/southmountain/dashigu/";
}
void create() 
{ 
        set("short", "大石谷");
        set("long", @LONG
这里是大石谷的谷底。
LONG
        );
	
        set("exits", ([ /* sizeof() == 3 */
   //"south" : __DIR__"zoudao2.c",
]));
		set("searchCD",2);//副本内lookfor一步的cd
		set("drug_level",45);//这里是这个副本出现药材的级别在此以下，副本内可以升级的采药术在35+10以下。
		set("level_bonus",40);//超过这个级别在副本能有额外加成
        set("migong_name","大石谷");
        set("no_clean_up", 1);
        set("no_reset", 1);
		set("outdoors", "dashigu");
		set("valid_startroom", 1);
        setup();
		gene_features();
}
string welcome_msg(object me)
{
	if (me->query_skill("alchemy",1)>1||me->query_skill("herbalism",1)>1)
	return CYN"【大石谷】谷内有很多药物，最高为45级药物，最高提升玩家采药术到55级。\n"NOR;
}
int start()
{
    object ob=this_object();
    object exit1=load_object(__DIR__"yingzui");
    object exit2=load_object(__DIR__"jingshui");
    //object exit3=load_object(__DIR__"shanluw1");
    object exit4=load_object(__DIR__"huoshankou");
    set("migong_name","大石谷"),
    gene("湖泽",1,ob,exit1,exit2,0,exit4,0); //样本，随机迷宫8个参数，第一个为迷宫地貌类型，在include/random_map.h可查，第二个为迷宫复杂度，3为迷宫原点，4-7为出口，无出口则需补0,第八个参数为迷宫出口对于真实地图是否可见，不可见为1，可见为0
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
	if (me->query("tianmuQuests/dashigu/gather"))
	{
		me->set("startroom", base_name(this_object()));
		me->set_temp("revive_room",base_name(this_object()));
	}
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

int valid_leave(object me,string dir)
{
	if (!random(20)&&me->query("tianmuQuests/dashigu/monkey")=="kill")
	{
		me->add_busy(1+random(2));
		return notify_fail(RED"你正要离开，却发现树上几只猴子在对着你扔石子。\n"NOR);
	}
	return ::valid_leave(me,dir);
}

