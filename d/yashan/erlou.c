//模板
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "临海楼二楼");
	set("long", @LONG
这里已经破烂不堪，几乎连站的地方都没有。
LONG
	);
	set("outdoors", "yanshan");
	set("objects", ([
		  
		]));
	set("exits", ([ 
		  "down"  : __DIR__"linhailou.c",
		]));
	set("no_clean_up", 1);
	set("hsz_no_task",1);
	setup();
	replace_program(ROOM);
}
/*void init()
{
	object me;
	me=this_player();
	me->move(load_object(__DIR__"linhailou.c"));
	return ;
}*/

