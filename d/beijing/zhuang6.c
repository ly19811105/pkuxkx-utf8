#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "庄府大厅");
    set("long", @LONG
这是一间灵堂。堂上供了七八个牌位.看来一座灵堂上供的
是一家死人.一阵阴风吹过,蜡烛突然灭了.
LONG );
    set("exits", ([
		"west" : __DIR__"zhuang5",
    ]));
    set("objects", ([
		__DIR__"npc/dizi": 1,
    ]));

    setup();
    replace_program(ROOM);
}


