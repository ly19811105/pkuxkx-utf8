inherit ROOM; //药山模板
#include <ansi.h>
#include "/d/southmountain/dongtianmu/random_clone.h"
#include "/d/southmountain/dongtianmu/herbmap.h"
#define HerbPoints 8
#define HerbRefreshRate 300
#define AREA "/d/lanzhou/"
#define SnakeRate 180
#define Max_Snake 10
int gene_snakes();
int gene_features();
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
		set("drug_level",55);//这里是这个副本出现药材的级别在此以下，副本内可以升级的采药术在35+10以下。
		set("level_bonus",50);
        set("migong_name","五泉山"),
        set("no_clean_up", 1);
        set("no_reset", 1);
		set("no_task",1);
		set("NotForTask",1);
		set("outdoors", "lanzhou");
        setup();
		gene_features();
		gene_snakes();
}
int start()
{
    object ob=this_object();
    object exit1=load_object(__DIR__"wuquan_e");
    //object exit2=load_object(__DIR__"shanlus1");
    object exit3=load_object(__DIR__"wuquan_w1");
    object exit4=load_object(__DIR__"yipin5");
    set("migong_name","五泉山"),
    gene("林地",1,ob,exit1,0,exit3,exit4,0); //样本，随机迷宫8个参数，第一个为迷宫地貌类型，在include/random_map.h可查，第二个为迷宫复杂度，3为迷宫原点，4-7为出口，无出口则需补0,第八个参数为迷宫出口对于真实地图是否可见，不可见为1，可见为0
    return 1;
}

int over()
{
    clear_all();
	start();
    return 1;
}
void clear_herbroom()
{
	object *rooms=children(__FILE__);
	for (int i=0;i<sizeof(rooms);i++)
	{
		if (rooms[i]->query("HERB_SPOT"))
		{
			tell_room(rooms[i],WHT+rooms[i]->query("short")+WHT+"的药材正在以肉眼可见的速度枯萎下去。\n"+NOR);
			rooms[i]->delete("HERB_SPOT");
		}
	}
	gene_features();
	return;
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
	spots=HerbPoints+random(HerbPoints/2);
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
int gene_features()
{
	int spots;
	string *rooms=({}),room;
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
	spots=HerbPoints+random(HerbPoints/2);
	if (spots<sizeof(query("gene_rooms"))/3)
	spots=sizeof(query("gene_rooms"))/3;
	for (int i=0;i<spots;i++)
	{
		if (room=query("gene_rooms/"+random(sizeof(query("gene_rooms")))))
		{
			room->delete("map_generated");
			room->init_map();
			room->set("HERB_SPOT",1);
			rooms+=({room});
		}
	}
	set("herb_rooms",rooms);
	remove_call_out("clear_herbroom");
	call_out("clear_herbroom",HerbRefreshRate);
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
		exit=load_object("/d/lanzhou/yipin");
		else
		exit=load_object(origin->query(exits[random(sizeof(exits))]));
		msg=leave_msg(origin,exit);
		clear_user_room(this_object(),exit,msg);
		return;
	}
}