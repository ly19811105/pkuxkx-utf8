// Room: /d/mingjiao/xiceting.c

inherit ROOM;

void create()
{
	set("short", "西侧厅");
	set("long", @LONG
这是绿柳山庄的西侧厅，室内放着几张非常古朴的桌子椅子。
    另有两个弟兄在此。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"yuan3",
  "east" : __DIR__"zhengting.c",
]));
	set("objects", ([ /* sizeof() == 2 */
  __DIR__"npc/wang.c" : 1,
  __DIR__"npc/zheng.c" : 1,
]));
	set("no_clean_up", 0);
    set("no_mj_newbie",1);
	setup();
	replace_program(ROOM);
}
