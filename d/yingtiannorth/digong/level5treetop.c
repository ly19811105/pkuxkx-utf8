inherit __DIR__"karma_room.c";
#include <ansi.h>

void create()
{
	set("short", "树顶上"NOR);
	set("long", @LONG
这里是一棵高大的树的树冠上，坐着一个老和尚。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 5);
	set("treetop", 1);
	setup();
}
void init()
{
	object monk;
	add_action("do_climb","climb");
	if (!monk=present("lao heshang",this_object())||(monk&&!monk->query("is_KARMA_MONK")))
	{
		monk=new(__DIR__"npc/monk");
		monk->move(this_object());
	}
	Add_Credit(this_object(),"karma_given",this_player(),3500);
	::init();
}
int climb(object me)
{
	if (!me||!environment(me)||!environment(me)->query("ontree"))
	return 1;
	me->move(load_object(__DIR__"level5maze")->query("tree_room"));
	message_vision(HIG"$N小心翼翼地爬了下来！\n"NOR,me);
	return 1;
}
int do_climb(string arg)
{
	object me=this_player();
	if (me->is_busy())
	{
		write("你正忙着呢。\n");
		return 1;
	}
	if (arg!="down")
	{
		write("在这里你只能向下爬(climb down)。\n");
		return 1;
	}
	me->add_busy(5);
	message_vision("$N向下爬去。\n",me);
	me->move("/d/yingtiannorth/digong/level5ontree");
	call_out("climb",5+random(5),me);
	return 1;
}