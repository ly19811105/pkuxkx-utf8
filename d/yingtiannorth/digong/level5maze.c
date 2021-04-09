inherit __DIR__"karma_room.c";
#include <ansi.h>
#include "/d/southmountain/dongtianmu/random_clone.h"
#define AREA "/d/yingtiannorth/digong/"
int gene_features();
void create() 
{ 
        set("short", "地宫五层中心");
        set("long", @LONG
这里是地宫五层的中心。
LONG
        );
        set("migong_name","地宫"),
		set("level",5);
		set("maze",1);
        set("no_clean_up", 1);
        set("no_reset", 1);
		set("no_task",1);
		set("outdoors", "digong");
        setup();
		gene_features();
}
string welcome_msg(object me)
{
	return MAG"【地宫】你进入了地宫第五层迷宫。\n"NOR;
}
string goodbye_msg(object me)
{
	return MAG"【地宫】你离开了地宫第五层迷宫。\n"NOR;
}
int start()
{
    object ob=this_object();
    object exit1=load_object(__DIR__"level5path2");
    //object exit2=load_object("/d/yingtiansouth/lakes1");
    object exit3=load_object(__DIR__"level5path3");
    //object exit4=load_object(__DIR__"laken1");
    set("migong_name","地宫"),
    gene("林地",1,ob,exit1,0,exit3,0,0); //样本，随机迷宫8个参数，第一个为迷宫地貌类型，在include/random_map.h可查，第二个为迷宫复杂度，3为迷宫原点，4-7为出口，无出口则需补0,第八个参数为迷宫出口对于真实地图是否可见，不可见为1，可见为0
    return 1;
}

int over()
{
    clear_all();
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
	::init();
}

int gene_features()
{
	object tree;
	string room;
	if (strsrch(file_name(this_object()), "#")!=-1)
	return 1;
	if (!query("fully_generated")&&!query("generating"))
	{
		start();
		remove_call_out("gene_features");
		call_out("gene_features",30);
		return 1;
	}
	if (!query("fully_generated"))
	{
		remove_call_out("gene_features");
		call_out("gene_features",30);
		return 1;
	}
	room=query("gene_rooms/"+random(sizeof(query("gene_rooms"))));
	tree=new(__DIR__"obj/thetree");
	tree->move(room);
	room->delete("outdoors");
	set("tree_room",room);
	return 1;
}