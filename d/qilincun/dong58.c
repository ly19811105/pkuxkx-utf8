// Rewrote by iszt@pkuxkx, 2007-02-11
#include "dong.h"
inherit ROOM;

void create()
{
	setshort();
	setlong();
    set("no_task",1);
	set("exits", ([
		"north" : __DIR__"dong57",
		"south" : __DIR__"dong03",
	]));
	setobject();

//	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
