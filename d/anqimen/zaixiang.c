
#include <ansi.h>　//by mudy
inherit ROOM;
void create()
{
        set("short", "窄巷");
        set("outdoors", "anqimen");
        set("long", ""
"这是一个窄巷，前面就是暗器门的总舵。"+"\n"
        );
        set("exits", ([
"eastdown":"/d/anqimen/xiaodao1",
"north":"/d/anqimen/damen.c",
"west":"/d/anqimen/shop.c",
                 ]));
set("objects", ([
	"/d/anqimen/npc/guishou.c":1,
            ]));
        setup();

}
