inherit __DIR__"karma_room.c";
#include <ansi.h>
#include "/d/southmountain/dongtianmu/random_clone.h"
#define AREA "/d/yingtiannorth/digong/"
void create() 
{ 
        set("short", "地宫六层中心");
        set("long", @LONG
这里是地宫六层的中心。
LONG
        );
        set("migong_name","地宫"),
		set("level",6);
		set("maze",1);
        set("no_clean_up", 1);
        set("no_reset", 1);
		set("no_task",1);
		set("outdoors", "digong");
        setup();
}
string welcome_msg(object me)
{
	return HIR"【地宫】你进入了地宫第六层迷宫。\n"NOR;
}
string goodbye_msg(object me)
{
	return HIR"【地宫】你离开了地宫第六层迷宫。\n"NOR;
}
int start()
{
    object ob=this_object();
    //object exit1=load_object(__DIR__"level5path2");
    object exit2=load_object(__DIR__"level6path2");
    object exit3=load_object(__DIR__"level6path3");
    //object exit4=load_object(__DIR__"laken1");
    set("migong_name","地宫"),
    gene("沙漠",1,ob,0,exit2,exit3,0,0); //样本，随机迷宫8个参数，第一个为迷宫地貌类型，在include/random_map.h可查，第二个为迷宫复杂度，3为迷宫原点，4-7为出口，无出口则需补0,第八个参数为迷宫出口对于真实地图是否可见，不可见为1，可见为0
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
	if (origin==this_object())
	tell_object(this_player(),HIR+"到了这里，你似乎发现西行才是通往下一层的路。\n"+NOR);
	Add_Credit(this_object(),"karma_given",this_player(),4500);
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

void gene_killer(object *team,object env)
{
	object *places=({}),killer;
	int num=3,exp=0,qi,jing,neili,jingli;
	for (int i=0;i<sizeof(team);i++)
	{
		if (team[i]->query_temp("karma/level6/pass_places")&&arrayp(team[i]->query_temp("karma/level6/pass_places")))
		places=team[i]->query_temp("karma/level6/pass_places");
		if (member_array(this_object(),places)==-1)
		places+=({this_object()});
		team[i]->set_temp("karma/level6/pass_places",places);
		exp+=team[i]->query("combat_exp");
		qi+=team[i]->query("max_qi");
		jing+=team[i]->query("max_jing");
		neili+=team[i]->query("max_neili");
		jingli+=team[i]->query("max_jingli");
	}
	exp/=sizeof(team);
	qi/=sizeof(team);
	jing/=sizeof(team);
	neili/=sizeof(team);
	jingli/=sizeof(team);
	if (qi>40000) qi=40000;
	if (sizeof(team)/2>num) num=sizeof(team)/2;
	for (int i=0;i<num;i++)
	{
		killer=new(__DIR__"npc/robber");
		killer->move(this_object());
		killer->copy(exp,qi,jing,neili,jingli);
		killer->kill_ob(team[random(sizeof(team))]);
	}
	return;
}
int check_robber()
{
	object *inv=all_inventory(this_object());
	for (int i=0;i<sizeof(inv);i++)
	if (inv[i]->query("is_KARMA_ROBBER")&&living(inv[i]))
	return 0;
	return 1;
}
object * current_team(object me,object env,object *team)
{
	for (int i=0;i<sizeof(team);i++)
	if (!environment(team[i])||environment(team[i])!=env)
	team-=({team[i]});
	return team;
}
object check_team(object *team)
{
	object pl;
	for (int i=0;i<sizeof(team);i++)
	if (team[i]->is_busy())
	return team[i];
	return pl;
}
int valid_leave(object me,string dir)
{
	int food = me->max_food_capacity();
	int water = me->max_water_capacity();
	object camel,pl;
	object env=environment(me),*team= me->query_team();
	team=current_team(me,env,team);
	if (!team||!arrayp(team)||sizeof(team)<2)
	return notify_fail(RED"一个人想要穿越沙漠那是找死。\n"NOR);
	if (!check_robber())
	return notify_fail(RED"不杀完最后一个沙盗，恐怕是难以离开了。\n"NOR);
	if (random(3)&&(!me->query_temp("karma/level6/pass_places")||member_array(this_object(),me->query_temp("karma/level6/pass_places"))==-1))
	{
		gene_killer(team,env);
		return notify_fail("你正要离开，突然杀出了一群沙盗！\n");
	}
	if (pl=check_team(team))
	{
		message_vision("$N现在正忙着呢，大家决定等等。\n",pl);
		return notify_fail("");
	}
	if (env&&member_array((int)env->query("room_type"),thirsty_place)!=-1)
	{
		if( userp(me) && ::valid_leave(me, dir)&& (!objectp(camel = me -> query_temp("riding"))|| camel->name() != HIW"白骆驼"NOR ) )
		{
			me->add("food", - food / 10);
			me->add("water", - water / 3);
			me->add_busy(2);
			tell_object(me, HIY"你觉得口干舌燥，真是生不如死！\n不知道何时才能走出茫茫大沙漠。\n"NOR);
			if(me->query("food") < 0 || me->query("water") < 0 )
				call_out("faint_me", 1, me);
		}
	}
	if (team[0]&&living(team[0]))
	message_vision(HIR"大家在$N"+HIR+"的带领下继续前进。\n"NOR,team[0]);
	for (int i=0;i<sizeof(team);i++)
	team[i]->move(this_object()->query("exits/"+dir));
	return notify_fail("");
}
