inherit __DIR__"karma_room.c";
#include <ansi.h>
void create()
{
	set("short", YEL"小沙丘"NOR);
	set("long", @LONG
这里是一座小沙丘，往东似乎是天地黄色一片了。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 6);
	set("path", 3);
	set("exits", ([
		//"up" : (:get_path:),
		//"out" : __DIR__"level6exit",
		//"north" : __DIR__"shanlus1",
		"west" : __DIR__"level6path4",
	]));
	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
