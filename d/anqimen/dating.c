
#include <ansi.h>　//by mudy
inherit ROOM;
void create()
{
        set("short", "大厅");
        set("long", ""
"这里是暗器门的大厅，大厅装修得金碧辉煌，可见暗器\n"
"门真的是富可敌国。\n"
        );
        set("exits", ([
"south":"/d/anqimen/damen",
"north":"/d/anqimen/houtang.c",
                 ]));
set("objects", ([
	__DIR__"npc/xiuzhongjian":1,
            ]));
        setup();

}