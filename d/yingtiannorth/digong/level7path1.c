inherit __DIR__"karma_room.c";
#include <ansi.h>
#include "gene_guard.h"
void create()
{
	set("short", HIG"华严塔"NOR);
	set("long", @LONG
这里是地宫第七层的华严塔。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 7);
	set("path", 1);
	set("exits", ([
		//"up" : (:get_path:),
		"eastdown" : __DIR__"level7path2",
		//"north" : __DIR__"shanlus1",
		"out" : __DIR__"level7entry",
	]));
	set("max_user",1);
	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
