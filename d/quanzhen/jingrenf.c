// Room: /u/hacky/quanzhen/jingrenf.c
// Made by: hacky

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "[33m净人访[2;37;0m");
	set("long", @LONG
这是全真教招待客人的地方，房间里很干净，似乎刚刚打扫过，屋里的摆设
很简单：一张圆桌，一张木床。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"zoulang6.c",
]));
	set("objects", ([ /* sizeof() == 1 */
  CLASS_D("quanzhen")+"/sun":1,
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
