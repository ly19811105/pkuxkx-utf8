// Room: /d/mingjiao/shijie1.c

inherit ROOM;

void create()
{
	set("short", "石阶");
	set("long", @LONG
你走在一条坚实的石阶上。一边是峭壁，一边是悬崖，
    抬头隐约可见笼罩在云雾中的明教总舵光明顶，向东有一条小胡同。
LONG
	);
	set("exits", ([ /* sizeof() == 3 */
  "south" : __DIR__"xiaozhen",
  "east" : __DIR__"hutong.c",
  "northwest" : __DIR__"shijie2",
]));
	set("no_clean_up", 0);
	set("outdoors", "mingjiao");

	setup();
	replace_program(ROOM);
}
