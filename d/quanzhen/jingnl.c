// Room: /u/kiss/quanzhen/jingnl.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "静念楼");
	set("long", @LONG
你一走进这间房子，就感到一种出奇的安静，几位道长正在这里打坐，你可
别打扰他们哦。房子的四壁上刻着一首词：
              自别后遥山隐隐，更那堪远山粼粼。
              见杨柳飞绵滚滚，对桃花醉脸醺醺。
              透内阁香风阵阵，掩重门暮雨纷纷。
北边是迎风阁。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "north" : __DIR__"yingfg.c",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
