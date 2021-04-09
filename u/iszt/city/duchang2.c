// Room: /city/duchang.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "赌场");
	set("long", @LONG
	这里有四条走廊通向不同的房间。
LONG
	);

	set("exits", ([
//                 "east" : "/inherit/room/eproom",
                "east" : __DIR__"puke-room",
//                 "west" : "/inherit/room/wproom",
                "west" : __DIR__"piggy",
		"south" : "/inherit/room/sproom",
		"north" : "/inherit/room/nproom",
		"down" : __DIR__"duchang",
	]));

	setup();
	replace_program(ROOM);
}

