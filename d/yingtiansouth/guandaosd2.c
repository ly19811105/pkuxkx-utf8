// Room: /d/suzhou/road1.c
// Date: May 31, 98  Java

inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", YEL"江南小道"NOR);
	set("long", @LONG
这是一条泥泞的江南小路，西北方向通往建康府，东面方向是苏州城了，
东南方向通向了太湖。
LONG );
	set("outdoors", "yingtianfu");
	set("no_clean_up", 0);
	set("exits", ([
		"northeast"     : __DIR__"tulue2",
		"west" : __DIR__"guandaosc",
		"southeast" : __DIR__"guandaosd3",
	]));
	setup();
}

