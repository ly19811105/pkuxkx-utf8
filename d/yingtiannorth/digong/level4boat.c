inherit __DIR__"karma_room.c";
#include <ansi.h>

void create()
{
	set("short", "小船"NOR);
	set("long", @LONG
这是一艘小船，可以开船(start)下船(getoff)和划桨(hua)。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 4);
	set("boat", 1);
	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
void init()
{
	add_action("do_start","start");
	add_action("do_hua","hua");
	add_action("do_getoff","getoff");
	::init();
}
int do_getoff()
{
	object me=this_player();
	if (me->is_busy())
	{
		write("你正忙着呢。\n");
		return 1;
	}
	if (query("takeoff"))
	{
		write("船在河中，你要下船？\n");
		return 1;
	}
	if (query("takeoff")&&!query("allow_off"))
	{
		write("船在河中，你要下船？\n");
		return 1;
	}
	message_vision("$N小心地走下了小船。\n",me);
	if (query("getoff"))
	me->move(query("getoff"));
	else
	me->move(query("boardfrom"));
	return 1;
}
int do_hua()
{
	object me=this_player(),boat;
	if (me->is_busy())
	{
		write("你正忙着呢。\n");
		return 1;
	}
	if (!query("takeoff"))
	{
		write("船还没开呢，划什么划？\n");
		return 1;
	}
	if (me->query_temp("karma/level4/skill")!="oar")
	{
		tell_object(me,"你不擅长开船，找个擅长的人来做吧。\n");
		return 1;
	}
	me->add_busy(2);
	message_vision("$N把小船向前划去。\n",me);
	add("forward",1);
	if (query("forward")>5+random(2))
	{
		set("allow_off",1);
		delete("takeoff");
		delete("forward");
		message_vision("一声轻响，小船到岸了。\n",me);
		boat=new(__DIR__"obj/boat");
		if (query("from")==1)
		{
			set("getoff",__DIR__"level4river2");
			boat->move(__DIR__"level4river2");
		}
		else
		{
			set("getoff",__DIR__"level4river");
			boat->move(__DIR__"level4river");
		}
	}
	return 1;
}
int do_start()
{
	object me=this_player(),boat;
	if (me->is_busy())
	{
		write("你正忙着呢。\n");
		return 1;
	}
	if (me->query_temp("karma/level4/skill")!="captain")
	{
		tell_object(me,"你不擅长开船，找个擅长的人来做吧。\n");
		return 1;
	}
	if (!me->query_temp("karma/level4/captain_notice"))
	{
		me->set_temp("karma/level4/captain_notice",1);
		write("现在开船，没有上船的人就上不来了，你确定要开船吗？确定请再次输入start。\n");
		return 1;
	}
	message_vision("$N开启了小船，缓缓离岸。\n",me);
	set("takeoff",1);
	delete("getoff");
	delete("allow_off");
	if (boat=query("off_boat"));
	{
		if (environment(boat)&&environment(boat)->isroom())
		{
			tell_room(environment(boat),"小船缓缓驶离岸边。\n");
			destruct(boat);
		}
	}
	return 1;
}