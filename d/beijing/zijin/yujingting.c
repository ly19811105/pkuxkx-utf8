// Room: /d/beijing/zijin/yujingting.c
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIY"御景亭"NOR);
	set("long",
HIC"这是建在堆秀山上的御景亭,堆秀山东西有蹬道可上,是园中可
以登临的最高点.登上此山原眺,西山在望;俯瞰,紫禁城尽收眼底，
九九重阳之节,皇帝在堆秀山登高。\n"NOR
	);
	set("exits", ([ /* sizeof() == 1 */
  	"down" : __DIR__"yuhuayuan",
]));
        set("outdoors", "beijing");

	setup();
	replace_program(ROOM);
}
