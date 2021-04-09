//模板
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "牙山湾西路");
	set("long", @LONG
可以看得出以前这里也是一个和谐的小镇，
但现在已经看不出一丝和谐的气息了，有的只
是山雨欲来风满楼的萧条．
LONG
	);
	set("outdoors", "yanshan");
	set("objects", ([
		"/d/lingxiao/npc/dizi_yashan" : random(2),
		]));
	set("exits", ([ 
		  "west" : __DIR__"wanxi3.c",
		  "east" : __DIR__"wanxi1.c",
		"south" : __DIR__"machehang",
		]));
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}

