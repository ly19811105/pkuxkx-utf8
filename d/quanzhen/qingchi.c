// Room: /u/kiss/quanzhen/qingchi.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short",GRN"清池"NOR);
	set("long", @LONG
一到清池，你的眼前仿佛全都变成了一片绿色，一大滩清澈见底的静水，那
么深，那么绿，有一种深不可测的感觉，水中鱼儿游来游去，好一片景致。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"zoulang17.c",
  "east" : __DIR__"mingmu.c",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
