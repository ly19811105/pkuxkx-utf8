inherit __DIR__"karma_room.c";
#include <ansi.h>
#include "gene_guard.h"
void create()
{
	set("short", HIC"禅宗塔"NOR);
	set("long", @LONG
这里是地宫第七层的禅宗塔。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 7);
	set("path", 4);
	set("exits", ([
		//"up" : (:get_path:),
		"northdown" : __DIR__"level7path5",
		//"north" : __DIR__"shanlus1",
		"eastup" : __DIR__"level7path3",
	]));
	set("max_user",1);
	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
