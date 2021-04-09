//城门
// By Zine 23 Nov 2010

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", HIG"后山"NOR);
        set("long", 
"这里清凉寺的后山，传说清凉寺下藏着一座七层的地宫。\n"

        );
        set("exits", ([
                
              
                //"out" : __DIR__"qls",
				"south" : __DIR__"qlsi",
                
        ]));
		set("no_task",1);
        setup();
   
}
void karma_start()
{
	object *inv=all_inventory(this_object());
	inv=filter(inv,(:userp:));
	inv=filter(inv,(:living:));
	if (sizeof(inv)<1) return;
	for (int i=0;i<sizeof(inv);i++)
	{
		if (i<=12)
		{
			inv[i]->move("/d/yingtiannorth/digong/level1entry");
			tell_object(inv[i],HBCYN+HIW+"此时正是清凉寺地宫开启的时候，你一闪身走了进去。\n");
		}
		else
		tell_object(inv[i],HBCYN+HIW+"清凉寺地宫开启了，你慢慢吞吞地跟在后面，等你移到地宫门口，地宫的门已经关上了。\n");
	}
	CHANNEL_D->do_channel(this_object(), "jh", HBCYN+HIW+"【清凉寺地宫】倒浮屠任务现在开启……\n"+NOR, -1);
	if (objectp(STATISTIC_D->query("Karma_Holder")))
	STATISTIC_D->query("Karma_Holder")->delete("allow_enter_karma");
	return;
}
void init()
{
	mixed *info= filter_array(call_out_info(), (: $1[1]==$2 :), "karma_start");
	if (!this_player()->query_temp("karma/LegalEnter"))
	{
		this_player()->move("/d/yingtiannorth/qlsi");
		tell_object(this_player(),"混入清凉寺后山被人发现，你被赶了出来。\n");
		tell_room("/d/yingtiannorth/qlsi",WHT+this_player()->name()+WHT+"被人从清凉寺后山狼狈地赶了出来。\n"NOR,({this_player()}));
	}
	if (query("player_num")>=12)
	{
		remove_call_out("karma_start");
		return karma_start();
	}
	if (query("player_num")>=6&&sizeof(info)<1)
	{
		CHANNEL_D->do_channel(this_object(), "jh", HBCYN+HIW+"【清凉寺地宫】现在已经有超过六个玩家准备进入地宫，地宫将在两分钟后或达到十二玩家时开启。\n"+NOR, -1);
		call_out("karma_start",120);
	}
	return;
}
void clear_all_rooms()
{
	object room;
	string filename,my_dir="/d/yingtiannorth/digong/",*dir;
	log_file( "user/karma", sprintf("*****%s开始清理地宫生成房间。*****\n",ctime(time())) );  	
	load_object(my_dir+"level1entry")->clear_users();
	log_file( "user/karma", sprintf("%s清理迷宫内玩家。\n",ctime(time())) );  	
	room=load_object(__DIR__"digong/level5maze");
	room->over();
	log_file( "user/karma", sprintf("%s清理迷宫%s生成房间。\n",ctime(time()),base_name(room)) );  	
	room=load_object(__DIR__"digong/level6maze");
	log_file( "user/karma", sprintf("%s清理迷宫%s生成房间。\n",ctime(time()),base_name(room)) );  	
	room->over();
	dir=get_dir(my_dir);
	for(int i=0;i<sizeof(dir);i++)
	{
		if(file_size(my_dir+dir[i])>0&&sscanf(dir[i],"%s.c",filename)==1)
		{
			if (dir[i]=="karma_room.c") continue;
			if (room=load_object(my_dir+dir[i]))
			{
				log_file( "user/karma", sprintf("%s清理地宫房间%s。\n",ctime(time()),my_dir+dir[i]) );
				destruct(room);
			}
		}
	}
	log_file( "user/karma", sprintf("%s清理地宫房间%s。\n",ctime(time()),__FILE__) );
	log_file( "user/karma", sprintf("*****%s清理地宫房间完毕。*****\n",ctime(time())) );  	
	return;
}
void Over_Karma(object me)
{
	if (userp(me))
	CHANNEL_D->do_channel(this_object(), "bd", HIW+"◇清凉寺地宫◇\t"+me->query("name")+HIW+"最先完成浮屠地宫任务，全身而出，地宫将在十分钟后关闭，请其他仍在地宫内的玩家尽快完成。\n"+NOR, -1);
	else
	CHANNEL_D->do_channel(this_object(), "bd", HIW+"◇清凉寺地宫◇\t"+me->query("name")+HIW+"地宫将在十分钟后关闭，请其他仍在地宫内的玩家尽快完成。\n"+NOR, -1);
	remove_call_out("clear_all_rooms");
	call_out("clear_all_rooms",600);
}