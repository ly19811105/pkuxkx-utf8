
#include <ansi.h>　//by mudy
inherit ROOM;
void create()
{
        set("short", "小道");
        set("outdoors", "anqimen");
        set("long", ""
"这是一条青石道，通向暗器门。你一想到暗器门令人毛骨悚然的暗器不禁发毛。"+"\n"
        );
        set("exits", ([
"northeast":"/d/anqimen/xiaodao",
"westup":"/d/anqimen/zaixiang.c",
                 ]));
set("objects", ([
            ]));
        setup();

}
