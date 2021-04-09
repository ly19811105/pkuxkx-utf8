// Room: /u/kiss/quanzhen/sanhuat.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", CYN"散花台"NOR);
	set("long", @LONG
散花台濒临湖畔，湖水波光粼粼，映在散花台里，给本已古色古香的台子更
增添了一分庄重与华丽。特别是亭顶内的纯水墨绘八骏图中八匹神采奕奕的骏马，
在波光的映衬下真是宛若活了一般！
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"feinuang.c",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
