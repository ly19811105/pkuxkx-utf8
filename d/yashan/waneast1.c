//模板
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "牙山湾东路");
	set("long", @LONG
从牙山湾往东走就是丰岛海面，北洋舰队的
两艘战舰济远和广乙这两天正在这里运送军货．
LONG
	);
	set("outdoors", "yanshan");
	set("objects", ([
		"/d/lingxiao/npc/dizi_yashan" : random(2),
		]));
	set("exits", ([ 
       "north" : __DIR__"wnbingying.c",
		  "west" : __DIR__"center.c",
		  "east" : __DIR__"waneast2.c",
		]));
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}

