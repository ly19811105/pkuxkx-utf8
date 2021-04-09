// Room: /hangzhou/nandajie2.c
// hubo 2008/4/19 

// Zine 2013 to 临安
inherit "/d/hangzhou/song_room";
#include <ansi.h>
void create()
{
	set("short", "凤凰山顶");
	set("long", @LONG
这里是凤凰山顶，可以俯瞰(fukan)全城。
LONG
	);
        set("outdoors", "hangzhou");

	set("exits", ([
		//"southeast" : __DIR__"wall2",
		"down" : __DIR__"fenghuang",
		//"northeast" : __DIR__"wall1",
		//"west" : __DIR__"wall1",
	]));
	set("no_clean_up",1);
	set("no_reset",1);
	setup();
}

void init()
{
	add_action("do_fukan","fukan");
	add_action("do_seek","seek");
}
int do_seek()
{
	object me=this_player(),ob=this_object(),book;
	message_vision("$N在这里搜寻着什么……\n",me);
	if (time()-ob->query("seek_time")>7200)
	{
		book=new("/d/hangzhou/obj/books/book_strategy_4");
		book->move(me);
		message_vision("$N找到一本$n。\n",me,book);
	}
	ob->set("seek_time",time());
	return 1;
}
int do_fukan(string arg)
{
	string *legal_dirs=({"west","east","north","south"});
	object me=this_player(),ob;
	if (time()-me->query_temp("hangzhou_fukan")<30)
	{
		return notify_fail("你还没看够吗？\n");
	}
	if (!arg)
	{
		return notify_fail("你要向哪个方向俯瞰？\n");
	}
	if (member_array(arg,legal_dirs)==-1)
	{
		return notify_fail("从这边只能向east,south,west或north俯瞰。\n");
	}
	if (arg=="south")
	{
		return notify_fail("南面被群山环绕，你的视线无法及远。\n");
	}
	else if (arg=="west")
	{
		ob=TASK_D->random_room("/d/hangzhou/xihu/");
	}
	else
	{
		ob=TASK_D->random_room("/d/hangzhou/");
	}
	me->set_temp("hangzhou_fukan",time());
	if (ob->query("short")&&ob->query("long"))
	{
		message_vision(HIG"$N乘着天气晴好，举目向着"+arg+"方向眺望……\n"NOR,me);
		tell_object(me,"你很清晰地看到了"+ob->query("short")+"。\n");
		return "/cmds/std/look.c"->mudlook_room(me,ob,0);
	}
	else
	return notify_fail("现在天气不是太好，你的视线无法及远。\n");
}