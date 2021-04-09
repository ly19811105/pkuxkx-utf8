inherit __DIR__"lanzhou.c";
#include <ansi.h>
void create()
{
	set("short", "药铺");
	set("long", @LONG
这里是一家老字号药铺，药铺老板笑盈盈地看着来往顾客。
LONG);
        set("outdoors", "lanzhou");

	set("exits", ([
		"enter" : __DIR__"yaopu2",
		"north" : __DIR__"datiepu",
		"west" : __DIR__"south_avenue2",
		//"north" : __DIR__"beijie3",
	]));
	set("no_task",1);
	set("objects", ([
		__DIR__"npc/yaolaoban" : 1,
        ])); 
	setup();
}
int valid_leave(object me,string dir)
{
	object rm;
	if (dir=="enter")
	{
		if (me->is_busy()||me->is_fighting())
		return notify_fail("你正忙着呢。\n");
		if(time() - me->query("killer/time") < 900)
		return notify_fail("你刚刚杀了人，别想躲进药铺隔间里。\n");
		if (time()>=me->query_temp("PermitAlchemy")&&time()>=me->query_temp("PermitAlchemy2"))
		return notify_fail("你要租药炉需要跟药铺老板打招呼了。\n");
		if (time()<me->query_temp("PermitAlchemy2"))
		rm=new(__DIR__"yaopu3");
		else if (time()<me->query_temp("PermitAlchemy"))
		rm=new(__DIR__"yaopu2");
		message_vision("$N和老板打过招呼后，向药铺后堂的小隔间离去。\n",me);
		me->move(rm);
		rm->set("user",me->query("id"));
		return notify_fail("你来到了药铺的小隔间。\n");
	}
	return ::valid_leave(me,dir);
}