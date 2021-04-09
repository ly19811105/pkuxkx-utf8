inherit __DIR__"karma_room.c";
#include <ansi.h>
#include "gene_guard.h"
void create()
{
	set("short", HIY"净土塔"NOR);
	set("long", @LONG
这里是地宫第七层的净土塔。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 7);
	set("path", 2);
	set("exits", ([
		//"up" : (:get_path:),
		"southdown" : __DIR__"level7path3",
		//"north" : __DIR__"shanlus1",
		"westup" : __DIR__"level7path1",
	]));
	set("max_user",1);
	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
