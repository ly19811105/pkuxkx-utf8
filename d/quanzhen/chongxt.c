// Room: /u/hacky/quanzhen/chongxt.c
// Made by: hacky

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "玄虚堂");
	set("long", @LONG
这是一间宽敞的屋子，整个房间由几根雕龙画凤的柱子撑着，房间的南面左
右各立着一个道士，他们手中持着拂尘，外面的人只能从他们面前经过。道士头
顶的屋檐下挂着一块木匾。
LONG
	);
	set("exits", ([ /* sizeof() == 3 */
  "north" : __DIR__"tianzd.c",
  "south" : __DIR__"xuanzt.c",
]));
	set("objects", ([ /* sizeof() == 1 */
 CLASS_D("quanzhen")+"/ma" : 1,
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
