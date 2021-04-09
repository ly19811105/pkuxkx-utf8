// Room: /d/beijing/fuchengdajie.c
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIC"阜成门大街"NOR);
	set("long",
CYN"这是繁华热闹的阜成门外大街，大街街面宽阔，车水马龙，川流不息，人群
熙熙攘攘，来来往往。街边上耍枪买艺、百货小吃，应有尽有，帝都风貌可见一
斑。街西是著名的药店一笑堂，街东则是饭馆食为天。\n"NOR
	);
	set("no_clean_up", 0);
	set("exits", ([ /* sizeof() == 3 */
	  "south" : __DIR__"xuanwumen",
	  "north" : __DIR__"fuchengdajie",
	  "west"  : __DIR__"yixiaotang",
	  "east"  : __DIR__"shiweitian",
	  "southeast"  : __DIR__"lingjing",
	]));
	set("outdoors", "beijing");
	set("cost", 2);

	setup();
}
