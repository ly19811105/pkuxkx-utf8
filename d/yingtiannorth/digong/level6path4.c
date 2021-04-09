inherit __DIR__"karma_room.c";
#include <ansi.h>
#include "/d/menggu/entry_migong.h"
void create()
{
	set("short", YEL"小沙丘"NOR);
	set("long", @LONG
这里是一座小沙丘，往东似乎是天地黄色一片了。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 6);
	set("path", 4);
	set("exits", ([
		//"up" : (:get_path:),
		"out" : __DIR__"level6exit",
		//"north" : __DIR__"shanlus1",
		"east" : __DIR__"level6path3",
	]));
	set("entry_direction","east");
		set("migong","/d/yingtiannorth/digong/level6maze");
		set("migong_posi","west");
		set("look_refuse_msg","地宫迷宫正在发生剧烈变化。\n");
		set("enter_refuse_msg","地宫迷宫正在发生剧变，此时不宜进入。\n");
	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
