//by zine
#include <ansi.h>
inherit "/d/riyuejiao/entry_prison.c";
void create()
{
	set("short","过道");
	set("long",@LONG 
一条长长的过道，过道里灯火忽明忽暗，闪烁不定。
LONG
	);
	set("exits", ([
		"east"	: __DIR__"prison",
		"west"	: __DIR__"prison",
		"north"	: __DIR__"prison_entry",
        "south" : __DIR__"guodao2",
	]));
    set("no_task",1);
	setup();
}

