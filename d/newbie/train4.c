//train4.c
//by zoom
//2003.3.30

#include <ansi.h>

inherit ROOM;

void create()
{
set("short", HIY"第四站:打斗指令"NOR);
set("long", @LONG
人在江湖，难免打打杀杀，学会了功夫，还要学以至用才成。让我来指导你
如何使用吧。各个门派的武功都不相同，但是特殊内功都有补精气的作用，不同的
内功还提供疗伤，加力，狮子吼等功夫；外功中很多功夫有特殊攻击，可以暂时让
对方busy，或者有比较高的杀伤力。另外拿兵器，穿护具，可以提高自己的攻防。
halt命令可以使自己退出战斗状态。指令verify <功夫名称> 可以让你查询某种功
夫的资料，这个是非常有用的。
LONG );
set("no_fight", 1);
set("exits",  ([
        "up"  : __DIR__"train5.c",
        "down"  : __DIR__"train3.c",
        "enter"  : __DIR__"train4_lianwu.c",
      ]));
        set("objects", ([
                __DIR__"npc/shizhe4" : 1,
        ]));
        setup();
}