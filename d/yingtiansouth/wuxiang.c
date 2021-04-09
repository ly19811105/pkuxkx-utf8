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
	return "/d/yingtiansouth/";
}

#define SnakeRate 180
#define Max_Snake 50
int gene_snakes();
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
		set("searchCD",2);//副本内lookfor一步的cd
		set("drug_level",45);//这里是这个副本出现药材的级别在此以下，副本内可以升级的采药术在35+10以下。
		set("level_bonus",40);
        set("migong_name","无想山"),
        set("no_clean_up", 1);
        set("no_reset", 1);
		set("no_task",1);
		set("outdoors", "wuxiang");
        setup();
		gene_features();
		gene_snakes();
}
string welcome_msg(object me)
{
	if (me->query_skill("alchemy",1)>1||me->query_skill("herbalism",1)>1)
	return HIW"【无想山】山中有很多药材，最高为45级药材，最高提升玩家采药术到55级。\n"NOR;
}
int start()
{
    object ob=this_object();
    object exit1=load_object(__DIR__"wuxiange1");
    //object exit2=load_object(__DIR__"shanlus1");
    object exit3=load_object(__DIR__"wuxiangw1");
    object exit4=load_object(__DIR__"wuxiangn1");
    set("migong_name","无想山"),
    gene("山地",1,ob,exit1,0,exit3,exit4,0); //样本，随机迷宫8个参数，第一个为迷宫地貌类型，在include/random_map.h可查，第二个为迷宫复杂度，3为迷宫原点，4-7为出口，无出口则需补0,第八个参数为迷宫出口对于真实地图是否可见，不可见为1，可见为0
    return 1;
}

int over()
{
    clear_all();
	start();
    return 1;
}

int gene_snakes()
{
	int spots,total;
	object snake,*snake1,*snake2,*snake3;
	string room;
	if (strsrch(file_name(this_object()), "#")!=-1)
	return 1;
	if (!query("fully_generated")&&!query("generating"))
	{
		start();
		remove_call_out("gene_snakes");
		call_out("gene_snakes",30);
		return 1;
	}
	if (!query("fully_generated"))
	{
		remove_call_out("gene_snakes");
		call_out("gene_snakes",30);
		return 1;
	}
	snake1=children("/d/guiyunzhuang/npc/snake1");
	snake1=filter(snake1,(: environment:));
	snake1=filter(snake1,(: environment($1)->query_location()==$2:),"/d/yingtiansouth/");
	snake2=children("/d/guiyunzhuang/npc/snake2");
	snake2=filter(snake2,(: environment:));
	snake2=filter(snake2,(: environment($1)->query_location()==$2:),"/d/yingtiansouth/");
	snake3=children("/d/guiyunzhuang/npc/snake3");
	snake3=filter(snake3,(: environment:));
	snake3=filter(snake3,(: environment($1)->query_location()==$2:),"/d/yingtiansouth/");
	total=sizeof(snake1)+sizeof(snake2)+sizeof(snake3);
	if (total>Max_Snake)
	{
		remove_call_out("gene_snakes");
		call_out("gene_snakes",SnakeRate);
		return 1;
	}
	spots=HerbPoints()+random(HerbPoints()/2);
	if (spots<sizeof(query("gene_rooms"))/3)
	spots=sizeof(query("gene_rooms"))/3;
	for (int i=0;i<spots;i++)
	{
		if (room=query("gene_rooms/"+random(sizeof(query("gene_rooms")))))
		{
			snake=new("/d/guiyunzhuang/npc/snake"+(1+random(3)));
			snake->move(room);
			if (random(2))
			snake=new("/d/guiyunzhuang/npc/snake"+(1+random(3)));
			snake->move(room);
		}
	}
	remove_call_out("gene_snakes");
	call_out("gene_snakes",SnakeRate);
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