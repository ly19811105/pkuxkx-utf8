// Room: /u/kiss/quanzhen/xijingt.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIC"吸景台"NOR);
	set("long", @LONG
吸景台典雅大方，但是最令人不解的是，台子的正中间是以玉栏杆围着的深
井，也许，亭子的主人是为了把五行的奥妙在这里略施一二吧！台中的水温而不
寒，据说是终年不冻，也不知是也不是！
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"ninglg.c",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
