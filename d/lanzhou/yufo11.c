// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", HIG"入山路"NOR);
	set("long", @LONG
这里进入了玉佛寺的后山，两侧种植着一些竹子。
LONG );
	set("exits", ([
		//"enter" : __DIR__"yufo9",
		"northdown" : __DIR__"yufo10",

	]));
	//set("outdoors", "lanzhou");
	setup();
}

int valid_leave(object me,string dir)
{
	if (dir!="northdown"&&!userp(me)) return notify_fail("");
	return ::valid_leave(me,dir);
}