//模板
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "小荒地");
	set("long", @LONG
这里已经是牙三湾南边的尽头了，你发现
旁边有一个金发碧眼“黄毛鬼”在向你鬼鬼祟
祟地张望，不知道打什么主意。
LONG
	);
	set("outdoors", "yanshan");
	set("objects", ([
		__DIR__"npc/usaseller.c":1,
		  
		]));
	set("exits", ([ 
		  "north" : __DIR__"wansouth2.c",
		]));
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}

