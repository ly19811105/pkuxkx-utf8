//模板
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "牙山米行");
	set("long", @LONG
这里原来是牙三米行，但现在已经成为
北洋舰队的粮仓了。这里放的全部是军米。
LONG
	);
	set("objects", ([
		  
		]));
	set("exits", ([ 
		  "south"  : __DIR__"wanxi1.c",
		]));
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}

