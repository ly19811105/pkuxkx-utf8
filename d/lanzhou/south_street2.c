// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
#include "/d/menggu/entry_migong.h"
void create()
{
	set("short", "山间路");
	set("long", @LONG
这里是兰州以南一条山间路，两侧可以看见葱葱郁郁的山岭(hill)。
LONG );
	set("exits", ([
		"north" : __DIR__"south_street1",
		"southup" : __DIR__"south_street3",
		"westup" : __DIR__"wuquan_e",
	]));
	set("outdoors", "lanzhou");
	set("entry_direction","westup");
	set("migong","/d/lanzhou/wuquan");
	set("migong_posi","east");
	set("look_refuse_msg","突然有黑衣蒙面人出现，阻止了你的窥探。\n");
	set("enter_refuse_msg","突然有黑衣蒙面人出现，阻止你进入五泉山。\n");
	setup();
}

