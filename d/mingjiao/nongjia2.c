// Room: /d/mingjiao/nongjia2.c

inherit ROOM;

void create()
{
	set("short", "里屋");
	set("long", @LONG
这是这家农户住的里屋，屋内昏暗，
    一个老婆婆正在哄着几个小孩。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"nongjia",
]));
	set("no_clean_up", 0);
    set("objects",([
   __DIR__"npc/oldwoman" :1,
__DIR__"npc/kid.c" :2,
]));

	setup();
	replace_program(ROOM);
}
