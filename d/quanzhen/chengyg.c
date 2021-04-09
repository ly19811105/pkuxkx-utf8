// Room: /u/kiss/quanzhen/chengyg.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "乘云阁");
	set("long", @LONG
此阁的四壁贴满了历代骚人墨客的题词，不知是谁把崔颢的那首<<黄鹤楼>>
也题在上面：昔人已乘黄鹤去，此地空余黄鹤楼。黄鹤一去不复返，白云千载空
悠悠。晴川历历汉阳树，芳草萋萋鹦鹉洲。日暮乡关何处是，烟波江上使人愁。
LONG
	);
	set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"lianqit.c",
  "south" : __DIR__"wufengl.c",
  "west" : __DIR__"yanlingg.c",
  "east" : __DIR__"youxiang.c",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
