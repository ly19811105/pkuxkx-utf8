//模板
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "牙山湾中心");
	set("long", @LONG
这里就是牙山湾的中心，偶尔可以看到几个
靠海谋生的人在这里拿着从海上捞起来的东西在
卖，现在这个时候他们还到海上去，简直就是在
刀口上过日子．
LONG
	);
	set("outdoors", "yanshan");
	set("objects", ([
		__DIR__"npc/xiaofan.c":1,
		  
		]));
	set("exits", ([ 
            "north" : __DIR__"wannorth1.c",
                  "south" : __DIR__"wansouth1.c",
		  "west" : __DIR__"wanxi1.c",
		  "east" : __DIR__"waneast1.c",
		]));
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}

