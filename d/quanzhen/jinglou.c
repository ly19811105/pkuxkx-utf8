// Room: /u/kiss/quanzhen/jinglou.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "经楼");
	set("long", @LONG
这里是全真教的经楼，靠墙是一排书架，摆满了道教的典籍。中央有一个长
方形的大桌子，上面也堆满了书。几个道童正在整理书籍。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "north" : __DIR__"xiejingf.c",
]));
        set("objects", ([
      __DIR__"npc/daotong" : 2,
      __DIR__"npc/obj/jing" : 3,
     ]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
