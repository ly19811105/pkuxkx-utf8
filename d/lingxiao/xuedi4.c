// File         : xuedi4.c
// Created By   : iszt@pkuxkx, 2006-08-15

#include <ansi.h>
#include "snow.h"

inherit ROOM;

void create()
{
        set("short", "雪地");
        set("long", @LONG
这里是一片雪地，厚厚的积雪足以没膝，可见山上终年如此，而凌霄城处于
如此高寒之地，即便有独门的御寒之物，门下弟子也需要扎实的内功根基。北面
山上是一片浓密的松林，其中似乎有什么东西注视着你。
LONG);

        set("outdoors", "凌霄城");

        set("item_desc", ([
                "snow": (: snow :),
        ]));

        set("objects", ([
                __DIR__"npc/wolf" : 1,
        ]));

        set("exits", ([
                "east" : __DIR__"xuepo3",
                "northup" : __DIR__"songlin",
        ]));

        setup();
}

void init()
{
        add_action("do_look", "look");
        add_action("do_go", "go");
}

int do_look(string arg)
{
        if(arg != "northup")
                return 0;
        write("那边是一片浓密的松林，什么也看不到。\n");
        return 1;
}

int do_go(string dir)
{
        object me = this_player();
        object* ob = deep_inventory(me);
        int i;

        if(dir != "northup")
                return 0;
        if(!userp(me))
                return 1;
        for(i=sizeof(ob)-1; i>=0; i--)
                if(ob[i]->is_character())
                {
                        write("你带着"+ob[i]->name()+"，无法在雪地中行走。\n");
                        return 1;
                }

        message_vision("$N深一脚浅一脚的踏入了松林深处。\n", me);
        call_out("do_move", 1, me);
        me->start_busy(2);

        return 1;
}

int do_move(object me)
{
        object room;

        room = new(__DIR__"songlin");
        me->move(room);
        message_vision("$N方进入此地，惊觉自己已然陷身林海之中，找不到来时的路了！\n", me);

        return 1;
}
