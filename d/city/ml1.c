// Room: /city/milin.c

inherit ROOM;

void create()
{
	set("short", "青竹林");
	set("long", @LONG
	这是一片茂密的青竹林，一走进来，你仿佛迷失了方向。
LONG
	);

	set("exits", ([
		"east" : __DIR__"ml2",
		"west" : __FILE__,
		"south" : __DIR__"dongmen",
		"north" : __FILE__,
	]));
	setup();
	replace_program(ROOM);
}
