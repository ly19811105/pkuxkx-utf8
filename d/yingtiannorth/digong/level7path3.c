inherit __DIR__"karma_room.c";
#include <ansi.h>
#include "gene_guard.h"
void create()
{
	set("short", HIB"天台塔"NOR);
	set("long", @LONG
这里是地宫第七层的天台塔。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 7);
	set("path", 3);
	set("exits", ([
		//"up" : (:get_path:),
		"westdown" : __DIR__"level7path4",
		//"north" : __DIR__"shanlus1",
		"northup" : __DIR__"level7path2",
	]));
	set("max_user",1);
	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
