inherit __DIR__"karma_room.c";
#include <ansi.h>

void create()
{
	set("short", "树上"NOR);
	set("long", @LONG
这里是一棵高大的树的树身上。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 5);
	set("ontree", 1);
	set("real_dark",1);
	setup();
}
void init()
{
	add_action("do_climb","climb");
	::init();
}
int do_climb()
{
	object me=this_player();
	if (me->is_busy())
	{
		write("你正忙着呢。\n");
		return 1;
	}
	write("你现在正在往上爬。\n");
	return 1;
}