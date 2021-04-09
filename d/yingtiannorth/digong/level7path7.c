inherit __DIR__"karma_room.c";
#include <ansi.h>
#include "gene_guard.h"
void create()
{
	set("short", HIR"毗昙塔"NOR);
	set("long", @LONG
这里是地宫第七层的毗昙塔。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 7);
	set("path", 7);
	set("exits", ([
		//"up" : (:get_path:),
		"westdown" : __DIR__"level7path8",
		//"north" : __DIR__"shanlus1",
		"northup" : __DIR__"level7path6",
	]));
	set("max_user",1);
	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
