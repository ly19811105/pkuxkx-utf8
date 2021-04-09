#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "长廊");
    set("long", @LONG
这是条长长的走廊。四处黑沉沉的.
LONG );
    set("exits", ([
		"north" : __DIR__"zhuang9",
		"south" : __DIR__"zhuang5",
    ]));
    set("objects", ([
		__DIR__"npc/dizi": 1,
    ]));

    setup();
    replace_program(ROOM);
}


