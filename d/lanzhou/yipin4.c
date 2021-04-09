// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
#include "/d/menggu/entry_migong.h"
void create()
{
	set("short", "演武厅");
	set("long", @LONG
这里是一品堂的演武厅，学员毕业正式成为杀手的仪式在这里举行。
LONG );
	set("exits", ([
		"out" : __DIR__"yipin5"
		"north"      : __DIR__"yipin1",
	]));
	set("entry_direction","out");
	set("migong","/d/lanzhou/wuquan");
	set("migong_posi","north");
	set("look_refuse_msg","突然有大量一品堂武士出现，阻止了你的窥探。\n");
	set("enter_refuse_msg","突然有大量一品堂武士出现，阻止你进入后山。\n");
	setup();
}

