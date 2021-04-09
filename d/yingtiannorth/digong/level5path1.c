inherit __DIR__"karma_room.c";
#include <ansi.h>
#include "/d/menggu/entry_migong.h"
void create()
{
	set("short", "细石路"NOR);
	set("long", @LONG
这里是一条细石子铺成的道路，一路延伸下去。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 5);
	set("path", 1);
	set("exits", ([
		//"up" : (:get_path:),
		"east" : __DIR__"level5entry",
		//"north" : __DIR__"shanlus1",
		"west" : __DIR__"level5path2",
	]));
	set("entry_direction","west");
		set("migong","/d/yingtiannorth/digong/level5maze");
		set("migong_posi","east");
		set("look_refuse_msg","地宫迷宫正在发生剧烈变化。\n");
		set("enter_refuse_msg","地宫迷宫正在发生剧变，此时不宜进入。\n");
	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
