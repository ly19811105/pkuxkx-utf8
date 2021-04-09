//train2.c
//modified from xo
//by zoom
//2003.3.30

#include <ansi.h>

inherit ROOM;

void create()
{
set("short", "菜园");
set("long", @LONG
你来到了一个不小的菜园，园子里的菜地分成了好几畦，分别种着白菜，萝
卜，韭菜，边上有几个小棚子，养了一些鸡鸭。一些新手正在田间做些农活，另
一些新手在喂鸡喂鸭，大家说说笑笑，园子里好不热闹。你也来吧！[1;32m(work)[37;0m
LONG );
set("no_fight", 1);
set("exits",  ([
        "southeast"  : __DIR__"train2_center.c",
      ]));
        set("objects", ([
                __DIR__"npc/laozhe" : 1,
        ]));
        setup();
        replace_program(ROOM);
}