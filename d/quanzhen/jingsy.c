// Room: /u/kiss/quanzhen/jingsy.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIW"精思院"NOR);
	set("long", @LONG
精思院是全真教用来修练的地方，许多全真的弟子正在这里研读道学心法，
一些资历更老的道长则在这里领悟全真高深的武学。
LONG
	);
	set("exits", ([ /* sizeof() == 3 */
  "west" : __DIR__"zoulang25.c",
  "north" : __DIR__"xiaoyaol.c",
  "east" : __DIR__"shuofy.c",
]));
       set("objects",([
      __DIR__"npc/gx-beast" : 1,
    ]));
	set("no_clean_up", 0);

  set("lingwu_family", "全真派");
	setup();
}
