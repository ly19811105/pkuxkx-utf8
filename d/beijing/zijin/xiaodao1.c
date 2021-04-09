// Room: /d/beijing/zijin/xiaodao1.c
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIY"宫中小道"NOR);
	set("long",
HIC"这是宫殿之间的夹道，静静的，偶尔有几个侍卫或太监走过。
小鸟停在树枝，叽叽喳喳叫个不停。东边的台阶可以通往中
和殿。\n"NOR
	);
	set("exits", ([ /* sizeof() == 3 */
  	"north" : __DIR__"houyoumen.c",
  	"south" : __DIR__"zhongyoumen",
  	"east" : __DIR__"zhonghedian",
]));
	set("outdoors", "beijing");

	setup();
	replace_program(ROOM);
}
