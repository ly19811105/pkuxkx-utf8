// Room: /u/kiss/quanzhen/lianqit.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "练气台");
	set("long", @LONG
人说道家最重内功心法，练气台就是全真教众教用来练气的地方，地上整整
齐齐的摆着十几个蒲团，旁边写有马珏与谭处端当年所作的两句：
        一住行窠五十年，蓬头白日走如颠。
南边就是乘云阁。

LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"chengyg.c",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
