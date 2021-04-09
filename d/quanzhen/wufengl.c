// Room: /u/hacky/quanzhen/wufengl.c
// Made by: hacky

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIW"午凤楼"NOR);
	set("long", @LONG
这里是一间别致的房间，房顶是金色花纹，四周几根柱子，皆刻着一些龙凤，
也许午凤因此得名，这里整整齐齐的放着一些蒲团，再向北就是乘云阁了。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"zoulang25.c",
  "north" : __DIR__"chengyg.c",
]));
      set("objects",([
     __DIR__"npc/tong-ren.c" : 1,
 ]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
