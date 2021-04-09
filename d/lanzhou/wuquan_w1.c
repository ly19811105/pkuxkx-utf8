// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "五泉山西");
	set("long", @LONG
这里是五泉山的西侧一段，西面更为险峻。
LONG );
	set("exits", ([
		//"eastdown" : __DIR__"wuquan_w1",
		"westup" : __DIR__"wuquan_w2",
		//"north" : __DIR__"west_street2",
		//"south" : __DIR__"west_lane1",
	]));
	set("outdoors", "lanzhou");
	setup();
}

int valid_leave(object me,string dir)
{
	if (dir!="westup"&&!userp(me)) return notify_fail("");
	return ::valid_leave(me,dir);
}