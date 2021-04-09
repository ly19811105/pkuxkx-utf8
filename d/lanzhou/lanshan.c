inherit ROOM; //纯矿山
#include <ansi.h>
#include "/d/southmountain/dongtianmu/random_clone.h"
#include "/d/southmountain/qingliangfeng/minemap.h"
#define MinePoints 20
#define MineRefreshRate 950
#define AREA "/d/lanzhou/"
int gene_mines();
void create() 
{ 
        set("short", "兰山");
        set("long", @LONG
这里是兰山。
LONG
        );
	
        set("exits", ([ /* sizeof() == 3 */
   //"south" : __DIR__"zoudao2.c",
]));
		set("searchCD",3);//副本内lookfor一步的cd
		set("mine_level",60);//可以练的mining级别，实际为+10.
		set("MineAppear",5);//出现的矿产的级别，一共8级。
		set("mine_level_bonus",45);//高于此级别有练级奖励。
		set("mine_assist_level",15);//低于10级也可能采到高级矿
        set("migong_name","兰山"),
        set("no_clean_up", 1);
        set("no_reset", 1);
		set("no_task",1);
		set("NotForTask",1);
		set("outdoors", "lanzhou");
        setup();
		gene_mines();
}
string welcome_msg(object me)
{
	if (me->query_skill("mining",1)>1||me->query_skill("smithing",1)>1)
	return HIC"【兰山】兰山内有很多矿石，最高为5级以下矿石碎片，最高提升玩家采矿术到70级。\n"NOR;
}
int start()
{
    object ob=this_object();
    //object exit1=load_object(__DIR__"zhaling3");
    //object exit2=load_object(__DIR__"changgengshang");
    object exit3=load_object(__DIR__"lanshan_w1");
    object exit4=load_object(__DIR__"yufo11");
    set("migong_name","兰山"),
    gene("山地",2,ob,0,0,exit3,exit4,0); //样本，随机迷宫8个参数，第一个为迷宫地貌类型，在include/random_map.h可查，第二个为迷宫复杂度，3为迷宫原点，4-7为出口，无出口则需补0,第八个参数为迷宫出口对于真实地图是否可见，不可见为1，可见为0
    return 1;
}

int over()
{
    clear_all();
	start();
    return 1;
}
void clear_mineroom()
{
	object *rooms=children(__FILE__);
	for (int i=0;i<sizeof(rooms);i++)
	{
		if (rooms[i]->query("MINE_SPOT"))
		{
			tell_room(rooms[i],WHT+rooms[i]->query("short")+WHT+"的矿脉似乎发生了变化。\n"+NOR);
			rooms[i]->delete("MINE_SPOT");
		}
	}
	gene_mines();
	return;
}
int gene_mines()
{
	int spots;
	string *rooms=({}),room;
	if (strsrch(file_name(this_object()), "#")!=-1)
	return 1;
	if (!query("fully_generated")&&!query("generating"))
	{
		start();
		remove_call_out("gene_mines");
		call_out("gene_mines",30);
		return 1;
	}
	if (!query("fully_generated"))
	{
		remove_call_out("gene_mines");
		call_out("gene_mines",30);
		return 1;
	}
	spots=MinePoints+random(MinePoints/2);
	if (spots<sizeof(query("gene_rooms"))/3)
	spots=sizeof(query("gene_rooms"))/3;
	for (int i=0;i<spots;i++)
	{
		if (room=query("gene_rooms/"+random(sizeof(query("gene_rooms")))))
		{
			room->delete("MineMaze_generated");
			room->init_mine_map();
			room->set("MINE_SPOT",1);
			rooms+=({room});
		}
	}
	set("mine_rooms",rooms);
	remove_call_out("clear_mineroom");
	call_out("clear_mineroom",MineRefreshRate);
	return 1;
}
int players()
{
	object *users;
	users=children(USER_OB);
	users=filter(users,(: environment:));
	users=filter(users,(: environment($1)->query_location()==$2:),AREA);
	if (!wizardp(this_player())) return 0;
	if (sizeof(users)<1)
	write("此区域没有玩家。\n");
	else
	write("此区域的玩家有：\n");
	for (int i=0;i<sizeof(users);i++)
	write(users[i]->query("name")+"("+users[i]->query("id")+")\t");
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
		exit=load_object("/d/lanzhou/yufosi");
		else
		exit=load_object(origin->query(exits[random(sizeof(exits))]));
		msg=leave_msg(origin,exit);
		clear_user_room(this_object(),exit,msg);
		return;
	}
}