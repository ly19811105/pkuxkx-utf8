inherit __DIR__"karma_room.c";
#include <ansi.h>
void create()
{
	set("short", "水坑"NOR);
	set("long", @LONG
这里是一座水坑，积的满是雨水，进入沙漠前，你可要灌满随身的容器。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("resource/water", 1);
	set("level", 6);
	set("path", 2);
	set("exits", ([
		//"up" : (:get_path:),
		//"out" : __DIR__"level6exit",
		//"north" : __DIR__"shanlus1",
		"south" : __DIR__"level6path1",
	]));
	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
