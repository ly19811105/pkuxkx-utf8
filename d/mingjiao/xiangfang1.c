//by binlang.c
// xiangfang1.c
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "西厢房");
        set("long", @LONG
这是绿柳山庄的西厢房，房中布置整齐。
正中有一张床，可在此睡觉。
LONG
        );
        set("exits", ([
            "east"  : __DIR__"xiaoyuan.c",
        ]));
        set("sleep_room",1);
        set("no_mj_newbie",1);
        setup();
}
