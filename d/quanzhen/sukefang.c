// Room: /u/hacky/quanzhen/sukefang.c
// Made by: hacky

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "俗客房");
	set("long", @LONG
这里是招待俗客的地方，现在全真教越来越兴旺，上门来拜访的人也越来越
多，所以这间俗客房就一直没有空着。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"zhoulang1.c",
]));

	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
