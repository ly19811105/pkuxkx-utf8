// Room: /u/kiss/quanzhen/ninglg.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIW"凝雪阁"NOR);
	set("long", @LONG
万物中雪为纯净，故世人多爱赏雪，而赏雪的最高境界为吹雪，雪花满天，
独行雪中，思接千载，视通万里，呼一丝热气，吹漫天飞雪，领略高手那一种寂
寞，以及那一种对生命的深层感触。吹雪楼的隅意，大概就在于此吧。这是全真
最大的一幢楼阁。西边是九仙楼，北边是吸景台，南边是九真楼，东边是飞峦阁。
LONG
	);
	set("exits", ([ /* sizeof() == 4 */
  "west" : __DIR__"jiuxianl.c",
  "north" : __DIR__"xijingt.c",
  "south" : __DIR__"jiuzhenl.c",
  "east" : __DIR__"feinuang.c",
]));
  set("objects",([
     __DIR__"npc/tan.c" : 1,
 ]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
