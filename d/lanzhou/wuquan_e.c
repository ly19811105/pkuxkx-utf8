// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "五泉山东麓");
	set("long", @LONG
这里是五泉山的东侧，东面是一条山间小路，西面就进山了。
LONG );
	set("exits", ([
		//"eastdown" : __DIR__"wuquan_w1",
		"eastdown" : __DIR__"south_street2",
		//"north" : __DIR__"west_street2",
		//"south" : __DIR__"west_lane1",
	]));
	set("outdoors", "lanzhou");
	setup();
}

int valid_leave(object me,string dir)
{
	if (dir!="eastdown"&&!userp(me)) return notify_fail("");
	return ::valid_leave(me,dir);
}