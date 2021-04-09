// Room: /u/kiss/quanzhen/chenglt.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", GRN"承露台"NOR);
	set("long", @LONG
承露台形状十分古朴，顶子以一般的石头砌成，但是却给人以一种浑然天成
的感觉。亭子内部也没有任何的装饰，但却让人有一种返璞归真的感觉。
LONG
	);
    set("objects",([
    __DIR__"npc/bird.c" : 2 ,
   ]));
	set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"yingfg.c",
  "north" : __DIR__"zoulang21.c",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
