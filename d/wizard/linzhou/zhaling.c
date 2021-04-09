
//fix by yhzzyahoo,矿山文件出bug，闭掉看看

inherit ROOM; //纯矿山

#include <ansi.h>
#include "/d/southmountain/dongtianmu/random_clone.h"
#include "/d/southmountain/qingliangfeng/minemap.h"
#define SnakeRate 180
#define Max_Snake 50
string AREA()//本区域目录
{
	return "/d/lingzhou/";
}
int MinePoints() 
{
	return 15;
}
int MineRefreshRate() 
{
	return 550;
}
int gene_snakes();
void create() 
{ 
        set("short", "扎陵湖");
        set("long", @LONG
这里是扎陵湖。
LONG
        );
	
        set("exits", ([ /* sizeof() == 3 */
   //"south" : __DIR__"zoudao2.c",
]));
		set("searchCD",2);//副本内lookfor一步的cd
		set("mine_level",65);//可以练的mining级别，实际为+10.
		set("MineAppear",5);//出现的矿产的级别，一共8级。
		set("mine_level_bonus",50);//高于此级别有练级奖励。
		set("mine_assist_level",15);//低于10级也可能采到高级矿
        set("migong_name","扎陵湖"),
        set("no_clean_up", 1);
        set("no_reset", 1);
		set("no_task",1);
		set("outdoors", "lingzhou");
        setup();
	//	gene_mines();
		gene_snakes();
}
string welcome_msg(object me)
{
	if (me->query_skill("mining",1)>1||me->query_skill("smithing",1)>1)
	return HIG"【扎陵湖】湖区内有很多矿石，最高为5级以下矿石碎片，最高提升玩家采矿术到75级。\n"NOR;
}
int start()
{
    object ob=this_object();
    object exit1=load_object(__DIR__"zhaling3");
    //object exit2=load_object(__DIR__"changgengshang");
    object exit3=load_object(__DIR__"zhaling1");
    //object exit4=load_object(__DIR__"shanlus1");
    set("migong_name","扎陵湖"),
    gene("湖泽",3,ob,exit1,0,exit3,0,0); //样本，随机迷宫8个参数，第一个为迷宫地貌类型，在include/random_map.h可查，第二个为迷宫复杂度，3为迷宫原点，4-7为出口，无出口则需补0,第八个参数为迷宫出口对于真实地图是否可见，不可见为1，可见为0
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
	snake1=filter(snake1,(: environment($1)->query_location()==$2:),"/d/lingzhou/");
	snake2=children("/d/guiyunzhuang/npc/snake2");
	snake2=filter(snake2,(: environment:));
	snake2=filter(snake2,(: environment($1)->query_location()==$2:),"/d/lingzhou/");
	snake3=children("/d/guiyunzhuang/npc/snake3");
	snake3=filter(snake3,(: environment:));
	snake3=filter(snake3,(: environment($1)->query_location()==$2:),"/d/lingzhou/");
	total=sizeof(snake1)+sizeof(snake2)+sizeof(snake3);
	if (total>Max_Snake)
	{
		remove_call_out("gene_snakes");
		call_out("gene_snakes",SnakeRate);
		return 1;
	}
	spots=MinePoints()+random(MinePoints()/2);
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