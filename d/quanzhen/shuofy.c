// Room: /u/hacky/quanzhen/shuofy.c
// Made by: hacky
#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIC"说法院"NOR);
	set("long", @LONG
这是说法院。大殿入口是朱红格扇，七宝玲珑。内里供奉的，是元始天尊、
太上道君和太上老君的神像,你看得眼花缭乱，东边是受道院，西边是精思院，
北边有道小木门。
LONG
	);
	set("exits", ([ /* sizeof() == 4 */
  "south" : __DIR__"zoulang10.c",
  "north" : __DIR__"tianzjt.c",
  "west" : __DIR__"jingsy.c",
  "east" : __DIR__"shoudy.c",
]));
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/wangchuy.c" : 1,
]));
	set("no_clean_up", 0);
 create_door("north","木门","south",DOOR_CLOSED);
	setup();
	replace_program(ROOM);
}
