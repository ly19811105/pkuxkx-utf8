// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
#include "/d/menggu/entry_migong.h"
void create()
{
	set("short", "兰山脚下");
	set("long", @LONG
这里是兰山的脚下，东面入山，西面进城。
LONG );
	set("exits", ([
		"westdown" : __DIR__"south_street3",
		"eastup" : __DIR__"lanshan_w1",
	]));
	set("outdoors", "lanzhou");
	set("entry_direction","eastup");
	set("migong","/d/lanzhou/lanshan");
	set("migong_posi","west");
	set("look_refuse_msg","突然有玉佛寺僧人出现，阻止了你的窥探。\n");
	set("enter_refuse_msg","突然有玉佛寺僧人出现，阻止你进入后山。\n");
	setup();
}

