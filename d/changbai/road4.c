// 雪路
// by steel

inherit ROOM;

void create()
{
	set("short", "雪原");
	set("long", @LONG
	这里是北方的一片雪原,积雪终年不化,放眼望去,白茫茫的一片,
一个人影也看不到.
LONG
	);
	set("outdoors", "changbai");
	set("exits", ([
                "north" : __DIR__"iceroad1",
		"south" : __DIR__"road2",
	]));
	setup();

}

#include "xuedi.h"