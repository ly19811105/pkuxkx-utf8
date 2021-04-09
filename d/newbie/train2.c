//train2.c
//modified from xo
//by zoom
//2003.3.30

#include <ansi.h>

inherit ROOM;

void create()
{
set("short", HIB"第二站:生活指令"NOR);
set("long", @LONG
在江湖上闯荡，先要照顾好自己。吃喝不在话下，还要学会如何赚钱，交易
等等。这里有个小镇子(enter)，麻雀虽小，五脏具全，好好练习一下吧。
LONG );
//    新手学堂专门派出精灵来指点新手，本站的是生活精灵，有什么不懂的可以
//问她[41m[1;37m(ask jing ling about [帮助|<主题>])[37;0m。
set("no_fight", 1);
set("exits",  ([
        "up"  : __DIR__"train3.c",
        "down"  : __DIR__"train1.c",
        "enter"  : __DIR__"train2_center.c",
      ]));
        set("objects", ([
                __DIR__"npc/shizhe2" : 1,
        ]));
        setup();
        replace_program(ROOM);
}