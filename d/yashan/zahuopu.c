//模板
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "杂货铺");
	set("long", @LONG
这里是一个废旧的杂货铺，以前在这里
可以买到很多海上的东西，但现在已经是不
可能的了。
LONG
	);
	set("objects", ([
		"/d/lingxiao/npc/dizi_yashan" : random(2),
		]));
	set("exits", ([ 
		  "east"  : __DIR__"wansouth1.c",
		]));
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}

