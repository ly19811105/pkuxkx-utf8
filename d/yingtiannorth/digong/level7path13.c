inherit __DIR__"karma_room.c";
#include <ansi.h>
#include "gene_guard.h"
void create()
{
	set("short", RED"密宗塔"NOR);
	set("long", @LONG
这里是地宫第七层的密宗塔。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 7);
	set("path", 13);
	set("exits", ([
		"out" : "/d/yingtiannorth/qlsi",
		//"northdown" : __DIR__"level7path13",
		//"north" : __DIR__"shanlus1",
		"southup" : __DIR__"level7path12",
	]));
	set("max_user",1);
	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
