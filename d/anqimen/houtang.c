
#include <ansi.h>　//by mudy
inherit ROOM;
void create()
{
        set("short", "后堂");
        set("long", ""
"这里是暗器门的后堂，你一走进来就感到这里好像机关"+"\n"
"重重似的，让你感到有几分害怕。\n"
        );
        set("exits", ([
"south":"/d/anqimen/dating",
"northwest":"/d/anqimen/zoulangleft.c",
"northeast":"/d/anqimen/zoulangright.c",
                 ]));
set("objects", ([
            ]));
        setup();

}