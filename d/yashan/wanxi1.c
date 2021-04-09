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
      "south" : __DIR__"jiuwu.c",
     "north" : __DIR__"mihang.c",
		  "west" : __DIR__"wanxi2.c",
		  "east" : __DIR__"center.c",
		]));
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}

