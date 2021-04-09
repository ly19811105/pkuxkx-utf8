//Created By Pal
//cometh@tom.com
//2003.10.5
#pragma save_binary

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "北大侠客行人才交流市场");
	set("long", @LONG
这里是北大侠客行的人才交流市场，你可以到这里招募家丁。
LONG
	);
	set("exits", ([
		"east":__DIR__"center",
		]));
	set("objects", ([
//房间有的物品
		]));
	setup();
}

void init()
{
	object me;
	string str,filename;

	me = this_player();
	str=me->query("id");

	filename="/data/home/file/"+str[0..0]+"/"+str+"/"+"gate.c";
	if(file_size(filename)>0)
	{
		add_action("do_hire","zhaopin");
		add_action("do_hire","hire");
	}
}

int do_hire(string arg)
{
	object me;
	int num;
	if(!arg || (arg!="guard" && arg!="jia ding"))
		return notify_fail("你要招募什么样的人才？\n");
	me=this_player();
	num=(int)me->query_temp("selfcreate/rencainum");
	//如果符合条件
	num++;
	me->set_temp("selfcreate/rencainum",num);
	tell_object(me,"你成功招募到一个家丁");
	return 1;
}