// 东天目山，一座随机生成的区域。玩家副本 Zine 2014/7/14
inherit "/d/southmountain/dongtianmu/baseroom.c";
#include <ansi.h>
int GrOwUp()
{
	int time,min,sec;
	if (time()-query("init_time")>1800)
	{
		message("vision", "很多奇花异草已经成熟了。\n",this_object(), ({}) );
		set("init_time",time());
		set("can_pick","/obj/remedy/reference"->random_drug("herb"));
	}
	else
	{
		time=query("init_time")+1800-time();
		sec=time%60;
		min=(time-sec)/60;
		message("vision", "这里的奇花异草上次被采摘过度，这时还没有回复生机。["+min+":"+sec+"]\n",this_object(), ({}) );
	}
	return 1;
}
string look_grass();
int progress()
{
	mixed *info= filter_array(call_out_info(), (: $1[1]==$2 :), "GrOwUp");
	if (sizeof(info)<1)
	{
		call_out("GrOwUp",30);
		message("vision", "这里的奇花异草正在生长……\n",this_object(), ({}) );
		return 1;
	}
	return 0;
}
void create()
{
	set("short", "山路");
	set("long", @LONG
这里是一段崎岖的山路，因为人迹罕至，长着一些奇花异草(grass)。
LONG
	);
        set("outdoors", "dongtianmu");
	set("item_desc", ([
                "grass" : (:look_grass:)]));
	set("exits", ([
		"eastdown" : __DIR__"dashi",
		//"up" : __DIR__"fenghuang2",
		//"northeast" : __DIR__"wall1",
		//"west" : __DIR__"wall1",
	]));
	set("no_clean_up",1);
	set("no_reset",1);
	set("objects", ([
		//__DIR__"npc/wujiang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	set("init_time",time());
	setup();
	progress();
}
string look_grass()
{
	object me=this_player();
	if (!me->query_skill("herbalism",1))
	return "这些奇花异草在其他地方并不常见。\n";
	else if (progress()==0)
	return "这些花草很多可以入药，等它们长成以后，你可以试着摘摘(zhai)。\n";
	else
	return "";
}
void init()
{
	add_action("do_zhai","zhai");
}

int do_zhai()
{
	object me=this_player(),ob;
	int no;
	if (!me->query_skill("herbalism",1))
	return notify_fail("你根本不会采药，乱摘是没用的。\n");
	if (me->is_busy()||me->is_fighting())
	return notify_fail("你正忙着呢。\n");
	if (!query("can_pick"))
	return notify_fail("这里的奇花异草上次被采摘过度，这时还没有回复生机。你等等再来吧。\n");
	no=query("can_pick");
	ob="/obj/remedy/reference"->ObtainDrug(no);
	delete("can_pick");
	if (ob&&ob->query("herb_lv")>me->query_skill("herbalism",1))
	{
		tell_object(me,"可惜"+ob->query("name")+"这种药材太难采集，超过了你的能力。\n");
		tell_object(me,"你看着碎成一地的"+ob->query("name")+"，不禁摇了摇头。\n");
		destruct(ob);
	}
	else
	{
		for (int i=0;i<2+random(5);i++)
		{
			ob="/obj/remedy/reference"->ObtainDrug(no);
			ob->move(me);
		}
		if (me->query_skill("herbalism",1)<120)
			me->improve_skill("herbalism",10+random(10));
		message_vision("$N采集到了一些$n。\n",me,ob);
	}
	return 1;
}
