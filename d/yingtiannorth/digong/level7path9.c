inherit __DIR__"karma_room.c";
#include <ansi.h>
#include "gene_guard.h"
void create()
{
	set("short", BLU"涅槃塔"NOR);
	set("long", @LONG
这里是地宫第七层的涅槃塔。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 7);
	set("path", 9);
	set("exits", ([
		//"up" : (:get_path:),
		"eastdown" : __DIR__"level7path10",
		//"north" : __DIR__"shanlus1",
		"southup" : __DIR__"level7path8",
	]));
	set("max_user",1);
	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
