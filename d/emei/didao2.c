// Room: /u/cuer/emei/didao2.c

inherit ROOM;

void create()
{
	set("short", "地道");
	set("long", @LONG
这是一间什麽也没有的空房间。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"shangu",
  "south" : __DIR__"didao1",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
