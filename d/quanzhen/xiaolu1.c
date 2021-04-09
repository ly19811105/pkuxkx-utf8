// Room: /d/quanzhen/xiaolu1.c

inherit ROOM;

void create()
{
	set("short", "小树林");
	set("long", @LONG
这是一片茂密的小树林，郁郁葱葱的长着许多树木，北边好象有一片空地。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
		"south" : __DIR__"mingmu.c",
		"north" : __DIR__"xiaolu2.c",
]));
        set("objects",([
         __DIR__"npc/bee.c" : 1,
    ]));

	setup();
	replace_program(ROOM);
}
