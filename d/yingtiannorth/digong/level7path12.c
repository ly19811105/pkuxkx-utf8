inherit __DIR__"karma_room.c";
#include <ansi.h>
#include "gene_guard.h"
void create()
{
	set("short", MAG"三论塔"NOR);
	set("long", @LONG
这里是地宫第七层的三论塔。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 7);
	set("path", 12);
	set("exits", ([
		//"up" : (:get_path:),
		"northdown" : __DIR__"level7path13",
		//"north" : __DIR__"shanlus1",
		"eastup" : __DIR__"level7path11",
	]));
	set("max_user",1);
	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
