// Room: /u/hacky/quanzhen/xuanzt.c
// Made by: hacky

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIY"崇玄台"NOR);
	set("long", @LONG
这里是全真教的练武场，你老远就听见了一阵阵的兵器碰撞声，尹志平正在
指导几个小道童练功，你也一起来练练吧。
LONG
	);
	set("exits", ([ /* sizeof() == 4 */
  "south" : __DIR__"sanqingdian.c",
  "north" : __DIR__"chongxt.c",
  "west" : __DIR__"zoulang2.c",
  "east" : __DIR__"zhoulang1.c",
]));
	set("objects", ([ /* sizeof() == 4 */
  __DIR__"npc/yin.c" : 1,
  __DIR__"npc/tong-ren.c" : 1,
  __DIR__"npc/liangong" : 2,
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
