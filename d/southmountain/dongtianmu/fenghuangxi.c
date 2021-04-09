// 东天目山，一座随机生成的区域。玩家副本 Zine 2014/7/14
inherit "/d/southmountain/dongtianmu/baseroom.c";
#include <ansi.h>
void create()
{
	set("short", "凤凰西麓");
	set("long", @LONG
这里是凤凰山的西麓，地势甚微陡峭，西面低处有一块石台，不过被山涧隔
开了。
LONG
	);
        set("outdoors", "dongtianmu");

	set("exits", ([
		"westdown" : __DIR__"dashi",
		"east" : "/d/hangzhou/fenghuang",
		//"northeast" : __DIR__"wall1",
		//"west" : __DIR__"wall1",
	]));

	set("objects", ([
		//__DIR__"npc/wujiang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}

void init()
{
	add_action("do_jump","jump");
}

int do_jump(string arg)
{
	object me=this_player();
	if (me->is_busy()||me->is_fighting())
	return notify_fail("你正忙着呢。\n");
	if (!arg||arg!="west")
	return 0;
	message_vision(HIC+"$N"+HIC+"向着西面奋力一跃。\n"+NOR,me);
	me->move(__DIR__"dashi");
	return 1;
}

int valid_leave(object me,string dir)
{
	if (dir=="westdown")
	return notify_fail("山涧隔着呢，你可以尝试跳(jump west)过去。\n");
	return ::valid_leave(me,dir);
}
