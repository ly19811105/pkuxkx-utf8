// room: /d/xingxiu/cave.c
// Jay 3/18/96
// Modified by iszt@pkuxkx, 2007-03-30

inherit ROOM;

int do_move(string);
int do_zuan(string);

void create()
{
	set("short", "逍遥洞");
	set("long", @LONG
这是一个粗糙的石洞，里面铺了几张臭哄哄的草垫子(dianzi)。垫子旁边
是一些破酒罐子。洞壁(wall)上有些字迹。
LONG);
	set("exits", ([
		"out" : __DIR__"xxh6",
	]));
	set("no_clean_up", 0);
	set("item_desc", ([
		"wall" : "星宿淫贼人人得而株之！\n",
		"dianzi": "臭烘烘的垫子有什么可看的！\n",
	]) );
	set("sleep_room", 1);
	setup();
}
void init()
{
	add_action("do_move", "move");
	add_action("do_zuan", "zuan");
}
int do_move(string arg)
{
	object me;
	me = this_player();
	if( !arg || arg=="" ) return 0;
	if( arg=="dianzi" )
	{
		if (me->query_temp("marks/阿"))
		{
			write("你挪了挪垫子，发现垫子底下有一个大洞(dong)，可以钻(zuan)进去。\n");
			this_player()->set_temp("marks/挪", 1);
			return 1;
		}
		return 0;
	}
}
int do_zuan(string arg)
{
	object me = this_player();
	if (me->query_temp("marks/钻"))
		return notify_fail("你不是找到冰魄杖了吗，怎么还要下去？\n");
	if (me->query_temp("marks/挪") )
	{
		message("vision", me->name() + "突然不见了。\n", environment(me), ({me}) );
		me->move(__DIR__"andao.c");
		message("vision", me->name() + "钻进洞来。\n", environment(me), ({me}) );
		this_player()->set_temp("marks/钻", 1);
		return 1;
	}
	else {
		write("你想往哪儿钻？\n");
		return 1;
	}
}