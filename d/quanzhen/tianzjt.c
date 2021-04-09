// Room: /u/kiss/quanzhen/tianzjt.c
// Made by: kiss
#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIW"天尊"NOR+RED"讲经堂"NOR);
	set("long", @LONG
这是天尊讲经堂，这里的地上整整齐齐的排放着数十个黄布蒲团，北首有一
个红木讲坛，讲坛上放着几本旧经书。东西边各放着一对美轮美奂的大花瓶，上
插檀香数支，香烟缭绕，氤氲芬芳，室内一片祥和之气。这里是一个讲经说法的
地方。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"shuofy.c",
  "north" : __DIR__"jiuxianl.c",
]));
set("objects",([
__DIR__"npc/hao":1,
]));
	set("no_clean_up", 0);
create_door("south","木门","north",DOOR_CLOSED);
	setup();
	replace_program(ROOM);
}
