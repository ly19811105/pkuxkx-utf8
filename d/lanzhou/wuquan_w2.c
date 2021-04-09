// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
#include "/d/menggu/entry_migong.h"
void create()
{
	set("short", "五泉山西峰");
	set("long", @LONG
这里是五泉山的西峰，十分陡峭，西面是兰州城一段城墙。
LONG );
	set("exits", ([
		"eastdown" : __DIR__"wuquan_w1",
		"westdown" : __DIR__"wall5",
		//"north" : __DIR__"west_street2",
		//"south" : __DIR__"west_lane1",
	]));
	set("entry_direction","eastdown");
	set("migong","/d/lanzhou/wuquan");
	set("migong_posi","west");
	set("look_refuse_msg","突然有黑衣蒙面人出现，阻止了你的窥探。\n");
	set("enter_refuse_msg","突然有黑衣蒙面人出现，阻止你进入五泉山。\n");
	set("outdoors", "lanzhou");
	setup();
}

