//山洞
// by steel

inherit ROOM;
#include "firn.h"

void create()
{
	set("short", "雪洞");
	set("long", @LONG
	这是雪山中的一个洞,洞内风雪虽然小了点,但是奇寒无比,看来没
有什么生命可以在这里生存.  东南方透出一点雪光。
LONG
	);

	set("exits", ([
		"southeast":__DIR__"road5",
                "north" : __DIR__"hole"+(random(10)+1),
                "west" : __DIR__"hole"+(random(10)+1),
                "northwest":__DIR__"hole"+(random(10)+1),
                "south":__DIR__"hole2",
          ]));
	setup();
}

/*
int valid_leave(object me, string dir)
{


       if( dir == "southeast" && !userp(me) )
                        return notify_fail("NPC不要乱跑！\n");
 
       return ::valid_leave(me, dir);
}
*/
