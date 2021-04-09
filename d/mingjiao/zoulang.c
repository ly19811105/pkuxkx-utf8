// zoulang.c 走廊
// by yuer
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "走廊");
        set("long", @LONG
        你走在一条走廊上，东西两边有几间雅室，人来人往很热闹。北边是大殿。
LONG
        );
        set("exits", ([
                "south" : __DIR__"guangchang",
                "north" : __DIR__"dadian",
                "west" : __DIR__"zoulang1",
                "east" : __DIR__"zoulang2",
        ]));
      set("objects",([
                CLASS_D("mingjiao") + "/weiyixiao.c" : 1,
                CLASS_D("mingjiao") + "/xiexun.c" : 1,
            ]));
        setup();
}
