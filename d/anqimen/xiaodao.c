#include <ansi.h>　//by mudy
inherit ROOM;
void create()
{
        set("short", "小道");
        set("outdoors", "anqimen");
        set("long", ""
"这是一条青石道，通向暗器门。"+"\n"
        );
        set("exits", ([
			"north":"/d/xingxiu/xxroad1",
"southwest":"/d/anqimen/xiaodao1.c",
                 ]));
set("objects", ([
            ]));
        setup();

}
