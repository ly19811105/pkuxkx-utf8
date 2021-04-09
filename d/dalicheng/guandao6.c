// Room: /d/dalicheng/guandao6.c

inherit ROOM;

void create()
{
	set("short", "官道");
	set("long", @LONG
这是一条蜿蜒崎岖的山间土路，是由中原通向大理的官道。此处属川南，向
西南去的盘山路通上云贵山区，继而可达南昭大理国，此去向北不远就是成都。
LONG
	);
	set("no_clean_up", 0);
	set("cost", 3);
	
	set("outdoors", "dali");
	set("exits", ([ /* sizeof() == 2 */
		  "southwest" : __DIR__"guandao5",
                  "north" : "/d/tianlong/dlroad4",
		]));
	setup();
	replace_program(ROOM);
}
