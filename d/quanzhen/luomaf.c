// Room: /u/hacky/quanzhen/luomaf.c
// Made by: hacky

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "骡马房");
	set("long", @LONG
一进骡马房，就可以看见两边栓着几十匹骡马，右边全都是骏马，左边全都
栓的是骡子，马儿一见你进来，立刻仰天长鸣，似乎准备等待着出发。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "north" : __DIR__"zoulang4.c",
]));
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/horse.c" : 2,
  __DIR__"npc/zhangsan.c" : 1,
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
