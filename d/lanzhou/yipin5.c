// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "后山小径");
	set("long", @LONG
这里是一条弯弯曲曲的小路，通往五泉山。
LONG );
	set("exits", ([
		"enter" : __DIR__"yipin4"
		//"north"      : __DIR__"yipin1",
	]));
	//set("outdoors", "lanzhou");
	setup();
}
int valid_leave(object me,string dir)
{
	if (dir!="enter"&&!userp(me)) return notify_fail("");
	return ::valid_leave(me,dir);
}