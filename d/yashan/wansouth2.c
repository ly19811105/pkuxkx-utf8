//模板
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "牙山湾南路");
	set("long", @LONG
路西边有一个破屋，显然已经荒废很久了。
东边有一个破旧的酒楼，酒楼的招牌已经破烂
不堪，但依稀可以辨认得出是“临海楼”三个
字。
LONG
	);
	set("outdoors", "yanshan");
	set("objects", ([
		"/d/lingxiao/npc/dizi_yashan" : random(2),
		]));
	set("exits", ([ 
		  "north" : __DIR__"wansouth1.c",
		  "west"  : __DIR__"powu.c",
		  "east"  : __DIR__"linhailou.c",
		  "south" : __DIR__"wansouth3.c",
		]));
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}

