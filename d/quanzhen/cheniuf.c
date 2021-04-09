// Room: /u/hacky/quanzhen/cheniuf.c
// Made by: hacky

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "[33m车牛房[2;37;0m");
	set("long", @LONG
这是用来放牛车的地方，房子不大，但里面整整齐齐的放着七、八辆车。一
个小道童正在给牛喂食。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "north" : __DIR__"zoulang5.c",
]));
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/daotong" : 1,
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
