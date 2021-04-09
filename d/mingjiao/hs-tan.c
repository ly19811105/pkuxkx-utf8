// Room: /d/mingjiao/hs-tan.c

inherit ROOM;

void create()
{
	set("short", "洪水坛");
	set("long", @LONG
这里是明教的洪水旗坛，旗主正和几个旗众守旗。
    南边是厚土旗的地方。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"damen.c",
]));
	set("objects", ([ /* sizeof() == 2 */
  __DIR__"npc/hs_zhong.c" : 2,
  "/kungfu/class/mingjiao/tang" : 1,
]));
	set("no_clean_up", 0);
	set("outroom", "明教");

	setup();
	replace_program(ROOM);
}
