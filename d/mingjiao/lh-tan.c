// Room: /d/mingjiao/lh-tan.c

inherit ROOM;

void create()
{
	set("short", "烈火坛");
	set("long", @LONG
这里是明教的烈火旗坛，烈火旗旗主正和几个旗众守旗。
    这儿地势险要，危峻无比。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"damen",
]));
	set("objects", ([ /* sizeof() == 2 */
  "/kungfu/class/mingjiao/xin" : 1,
    __DIR__"npc/lh_zhong.c" :2,
]));
	set("no_clean_up", 0);
	set("outroom", "明教");

	setup();
	replace_program(ROOM);
}
