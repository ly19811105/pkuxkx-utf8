// Room: /u/hacky/quanzhen/shaoxf.c
// Made by: hacky

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "烧香坊");
	set("long", @LONG
你来到了全真教的烧香坊，许多人正在这里烧香，祈求保佑。几个小道童正
在忙着帮人们烧香，屋子中间摆着一个功德箱，里面有几尊三清像，东边就是三
清殿。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "east" : __DIR__"sanqingdian.c",
]));
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/daotong.c" : 3,
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
