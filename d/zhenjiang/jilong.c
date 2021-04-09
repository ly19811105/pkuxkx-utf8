inherit ROOM; //纯矿山
#include <ansi.h>
#include "/d/southmountain/dongtianmu/random_clone.h"
#include "/d/southmountain/qingliangfeng/minemap.h"
#define MinePoints 15
#define MineRefreshRate 500
#define AREA "/d/zhenjiang/"
int gene_mines();
int gene_self();
void create() 
{ 
        set("short", "鸡笼山");
        set("long", @LONG
这里是鸡笼山。
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
        set("migong_name","鸡笼山"),
        set("no_clean_up", 1);
        set("no_reset", 1);
		set("no_task",1);
		set("outdoors", "zhenjiang");
        setup();
		gene_mines();
		gene_self();
}
string welcome_msg(object me)
{
	if (me->query_skill("mining",1)>1||me->query_skill("smithing",1)>1)
	return HIG"【鸡笼山】山中有很多矿石，最高为5级以下矿石碎片，最高提升玩家采矿术到75级。\n"NOR;
}
int start()
{
    object ob=this_object();
    //object exit1=load_object(__DIR__"shanlue1");
    //object exit2=load_object(__DIR__"changgengshang");
    object exit3=load_object(__DIR__"jlsw1");
    object exit4=load_object(__DIR__"shanlus1");
    set("migong_name","鸡笼山"),
    gene("山地",3,ob,0,0,exit3,exit4,0); //样本，随机迷宫8个参数，第一个为迷宫地貌类型，在include/random_map.h可查，第二个为迷宫复杂度，3为迷宫原点，4-7为出口，无出口则需补0,第八个参数为迷宫出口对于真实地图是否可见，不可见为1，可见为0
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
int gene_self()
{
	string path,exit;
	if (strsrch(file_name(this_object()), "#")!=-1)
	return 1;
	if (!query("fully_generated")&&!query("generating"))
	{
		start();
		remove_call_out("gene_self");
		call_out("gene_self",2);
		return 1;
	}
	if (!query("fully_generated"))
	{
		remove_call_out("gene_self");
		call_out("gene_self",2);
		return 1;
	}
	exit=query("exit3");
	path=query("pathways/w_path");
	exit->set("long",exit->query("old_long")+HBWHT+RED+"\n这里似乎被人插上了一块路牌(lupai)。\n"+NOR);
	exit->delete_temp("mixed_long");
	exit->set("item_desc",(["lupai":"进山路：east->"+path+"\n"]));
	exit=query("exit4");
	path=query("pathways/n_path");
	exit->set("long",exit->query("old_long")+HBWHT+RED+"\n这里似乎被人插上了一块路牌(lupai)。\n"+NOR);
	exit->delete_temp("mixed_long");
	exit->set("item_desc",(["lupai":"进山路：south->"+path+"\n"]));
	set("short",HBRED+HIC+"鸡笼山主峰"+NOR);
	set("long","这里是鸡笼山主峰，听说已经被一伙强人所占据，这里盖起了一座山寨(shanzhai)。\n");
	set("item_desc",(["shanzhai":"这里是不知道哪路绿林豪杰的山寨，如果没有什么本事，最好还是不要随便进入(enter shanzhai)。\n"]));
	set("zhai_entry",1);
	return 1;
}
int do_enter(string arg)
{
	object me=this_player();
	if (!query("zhai_entry")) return 0;
	if (!arg||arg!="shanzhai") return 0;
	if (!me->query_temp("OustBandit/start"))
	{
		write("进山寨剿匪太危险了，你必须征得官府同意才行。\n");
		return 1;
	}
	if (me->is_busy()||me->is_fighting())
	{
		write("你正忙着呢。\n");
		return 1;
	}
	tell_room(__DIR__"fortress_entry",me->name()+"小心翼翼地走了过来。\n");
	me->move(__DIR__"fortress_entry");
	tell_room(this_object(),HIG+me->name()+HIG+"小心翼翼地进入了山寨。\n"+NOR);
	tell_object(me,"你走进山寨里面。等队友都来了之后输入"+HIW+"ready"+NOR+"开始任务。\n");
	return 1;
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
	add_action("do_enter","enter");
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