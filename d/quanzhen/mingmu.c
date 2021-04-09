// Room: /u/kiss/quanzhen/mingmu.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "名木");
	set("long", @LONG
你走到了一片栽满了各种各样的树木(shu) 的地方，有些你甚至叫不上名字，
郁郁匆匆。西边就是清池，远远望去，一滩碧水，东边是药圃。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"qingchi.c",
  "east" : __DIR__"yaopu.c",
  "north" : __DIR__"xiaolu1.c",
]));
    set("item_desc",([
      "shu":"一片密密的树丛。\n"
     ]));
	set("no_clean_up", 0);
     
	setup();
  
}

