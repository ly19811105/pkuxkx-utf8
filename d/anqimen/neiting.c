
#include <ansi.h>　//by mudy
inherit ROOM;
void create()
{
        set("short", "内厅");
        set("long", ""
"    这里是暗器门的内厅，是暗器门门主会见重要人物的地方。"+"\n"
        );
        set("exits", ([
"southwest":"/d/anqimen/zoulangleft",
"southeast" : "/d/anqimen/zoulangright.c",
"north":"/d/anqimen/menzhushi.c",
                 ]));
set("objects", ([
	__DIR__"npc/duomingbiao":1,
            ]));
        setup();

}