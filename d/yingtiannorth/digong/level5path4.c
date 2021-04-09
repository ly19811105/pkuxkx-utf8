inherit __DIR__"karma_room.c";
#include <ansi.h>
#include "/d/menggu/entry_migong.h"
void create()
{
	set("short", "小路"NOR);
	set("long", @LONG
这里是一条小路，西面被一块大石头挡住了。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 5);
	set("path", 4);
	set("exits", ([
		//"up" : (:get_path:),
		"east" : __DIR__"level5path3",
		//"north" : __DIR__"shanlus1",
		//"west" : __DIR__"level5exit",
	]));
	set("entry_direction","east");
		set("migong","/d/yingtiannorth/digong/level5maze");
		set("migong_posi","west");
		set("look_refuse_msg","地宫迷宫正在发生剧烈变化。\n");
		set("enter_refuse_msg","地宫迷宫正在发生剧变，此时不宜进入。\n");
	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
void init()
{
	add_action("do_say","say");
	::init();
}
int del_exit()
{
	delete("exits/west");
	set("long","这里是一条小路，西面被一块大石头挡住了。\n");
	delete_temp("mixed_long");
}
int do_say(string arg)
{
	if (!arg||arg!=query("passwd"))
	return 0;
	message_vision(HIW+"$N"+HIW+"缓缓念出：『"+arg+"』。\n",this_player());
	set("exits/west",__DIR__"level5exit");
	set("long", "这里是一条小路，西面不知道通向哪里。\n");
	delete_temp("mixed_long");
	remove_call_out("del_exit");
	call_out("del_exit",6);
	return 1;
}