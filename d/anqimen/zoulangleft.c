
#include <ansi.h>　//by mudy
inherit ROOM;
void create()
{
        set("short", "走廊");
        set("long", ""
"这是一条走廊，通向内厅。"+"\n"
        );
        set("exits", ([
"southeast":"/d/anqimen/houtang",
"northeast":"/d/anqimen/neiting.c",
                 ]));
set("objects", ([
            ]));
        setup();

}