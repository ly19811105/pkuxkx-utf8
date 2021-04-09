// Room: /u/kiss/quanzhen/yanzhenl.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "延真楼");
	set("long", @LONG
你信步前行，推开半掩着的楼门，踏入一静寂之所在，只见高堂之上，赫然
挂着一匾定睛望去，写着延真楼三字。环顾屋内，几位中年道人盘膝而座。似在
合力钻研一玄妙剑阵。你刚想走近，竟被一股无形罡气逼得连连后退。这里的南
面是走廊，北面是延灵阁。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"yanlingg.c",
  "south" : __DIR__"zoulang14",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
