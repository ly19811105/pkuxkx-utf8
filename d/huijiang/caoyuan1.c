// Room: /d/huijiang/caoyuan1.c
// by hubo

inherit ROOM;

void create()
{
	set("short", "草原");
	set("long", @LONG
柔嫩的青草就踩在脚下，天上浮云飘过，牧羊的姑娘轻哼着小曲，挥
动皮鞭驱赶着牛羊，远处天山山脉高不可攀，一边的湖水在静静的波动。几
头苍鹰张着翅膀在空中缓缓滑过。
LONG
	);
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/ox.c" : 1,
]));
	set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"damo6",
  "west" : __DIR__"caoyuan2",
  "east" : __DIR__"caoyuan3",
  "north" : __DIR__"buluo",
]));
	set("outdoors", "huijiang");
	setup();
}

