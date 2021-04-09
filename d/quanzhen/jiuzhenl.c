// Room: /u/kiss/quanzhen/jiuzhenl.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "九真楼");
	set("long", @LONG
九真楼里颇有些肃静的感觉，房间很空旷，没有什么东西，北边是凝灵阁，
南边是受道院。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"ninglg.c",
  "south" : __DIR__"shoudy.c",
]));
     set("objects",([
     __DIR__"npc/tong-ren.c" : 1,
    ]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
