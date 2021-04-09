//模板
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "临海楼");
	set("long", @LONG
这里是一家酒楼，本来是一个两层的酒楼，
但是第二层已经坍塌，无法上去，从东面的窗
户看出去刚好可以看到丰海海面，如果不是战
争即将爆发，在这里临海饮酒，还真是一件美
事呢。看着这危楼，你敢爬（climb）上去么？
LONG
	);
	set("objects", ([
		"/d/lingxiao/npc/dizi_yashan" : random(2),
		]));
	set("exits", ([ 
		  "west"  : __DIR__"wansouth2.c",
		  "up"    : __DIR__"erlou.c",
		]));
    set("no_fullme_scan",1);
	set("no_clean_up",1);
	setup();
//	replace_program(ROOM);
}
int valid_leave(object me,string dir)
{
	if(dir=="up")
		return notify_fail("上面已经塌了，你还上去干什么？\n");
	return ::valid_leave(me,dir);
}

void init()
{
	add_action("do_climb", "climb");
	add_action("do_climb", "pa");
}
int do_climb(string arg)
{
	object me = this_player();;

	if( !arg || arg=="" ) return 0;

	if(me->is_busy() || me->is_fighting())
	{
		write("你正忙着呢。\n");
		return 1;
	}

	if( arg=="up" )
	{
		if(me->query_skill("dodge") < 150)
		{
			write("你的轻功不足，爬不上去。\n");
			return 1;
		}
		message_vision("$N轻轻一纵，跃上二楼。\n", me);
		message("vision",
			me->name() + "轻轻一纵，跃上二楼。\n",
			environment(me), ({me}) );
		me->move(__DIR__"erlou");
		message("vision",
			me->name() + "从下面飞了上来。\n",
			environment(me), ({me}) );
		me->start_busy(2);
		return 1;
	}
}