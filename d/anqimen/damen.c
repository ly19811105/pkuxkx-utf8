
#include <ansi.h>　//by mudy
inherit ROOM;
void create()
{
        set("short", "暗器门");
        set("long", ""
"这里是暗器门的大门，你一抬头就可以看到大门上面\n"
"挂着一块匾，匾上写着几个大字[暗器门]。相传暗器门中\n"
"高手如云，而且暗器门财雄势大，江湖人都忌他们三分。\n"
"看来你还是少惹为妙！\n"
        );
        set("exits", ([
"south":"/d/anqimen/zaixiang",
"north":"/d/anqimen/dating.c",
                 ]));
set("objects", ([
"/d/anqimen/npc/kanmenren.c" : 1,
            ]));
        setup();

}