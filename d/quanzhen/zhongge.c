// Room: /u/kiss/quanzhen/zhongge.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIW"钟阁"NOR);
	set("long", @LONG
步入阁楼，但闻钟声萦绕，久而不绝。只见一座大钟悬于殿上，钟身通体暗
红，绝非一般材料制成。一小道士想是专司此钟，竟练得一副耳聪目明，想来此
钟必有玄妙。南面是走廊，西面是写经房。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"xiejingf.c",
  "north" : __DIR__"zoulang23.c",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
