//train2.c
//modified from xo
//by zoom
//2003.3.30

#include <ansi.h>

inherit ROOM;

void create()
{
set("short", "小镇");
set("long", @LONG
这里是生活指令练习中心。 东面是当铺，西面是钱庄，南面是一家小店，
北面是休息室，西北是一个菜园，可以在那里赚钱。东北方是个茶馆，是专门
为新手准备的。这些都是新手练习常用生活指令的地方。
LONG );
set("no_fight", 1);
set("exits",  ([
        "east"  : __DIR__"train2_dangpu.c",
        "northwest"  : __DIR__"train2_caiyuan.c",
        "south"  : __DIR__"train2_xiaodian.c",
        "north"  : __DIR__"train2_xiuxi.c",
        "west"  : __DIR__"train2_qianzhuang.c",
        "northeast"  : __DIR__"train2_chaguan.c",
        "out"  : __DIR__"train2.c",
      ]));
        set("objects", ([
//                __DIR__"npc/xx" : 1,
        ]));
        setup();
        replace_program(ROOM);
}