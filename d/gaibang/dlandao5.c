// Room: /d/gaibang/wdandao1.c
// Date: Haa 96/03/22

#include <room.h>
inherit ROOM;




void create()
{
	set("short", "暗道");
	set("long", @LONG
这是丐帮 极其秘密的地下通道，乃用丐帮几辈人之心血掘成。 
LONG
	);

	set("exits", ([
                        "south" : __DIR__"dlandao6",
                        "northeast" : __DIR__"dlandao4",
	]));
    set("no_task",1);
    set("objects",([
        "/d/pker/npc/hutu":1
    ]));

	setup();
	replace_program(ROOM);
}



