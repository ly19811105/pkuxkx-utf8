//洛阳，扩展地图
//by kiden
//2006-9-8
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "荒地");
        set("long", @LONG
一望无际的大漠，满眼黄沙，疾风摧残着一切生命。
LONG
        );

        set("exits", ([
			"west" : __DIR__"33",
"north" : __DIR__"44",
"northwest" : __DIR__"34",

        ]));
        set("no_task",1);
        setup();
        replace_program(ROOM);
}


