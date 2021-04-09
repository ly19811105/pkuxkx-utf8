// Room: /d/quanzhen/shijie4.c

inherit ROOM;
#include "sao.h"
void create()
{
	set("short", "石阶");
	set("long", @LONG
你走在一条又窄又陡的石阶上，一边是悬崖，一边是峭壁，你不禁有些害怕。
上面就是重阳宫。路边有一些薄荷(bohe)。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "southeast" : __DIR__"shijie5.c",
  "northup" : __DIR__"shijie3.c",
]));
       set("objects", ([
       __DIR__"npc/mosheng.c" : 1,
          ]));
       set("item_desc", ([
		"bohe" : "薄荷清凉醒脑，可以入药，一般生长在山间。你可以摘(zhai)下来。\n", 
	    ]));
	set("no_clean_up", 0);
     set("outdoors","quanzhen");
    set("loc",4);
	setup();
	
}

void init()
{ 
	add_action("do_zhai","zhai"); 
    add_action("do_sao","sao");
}

int do_zhai()
{
    object me=this_player();
    object gc;
    if (me->is_busy() || me->is_fighting())
    {
		return notify_fail("你正忙着哪！\n");
    }
    if (me->query_temp("薄荷"))
    {
        return notify_fail("薄荷已经被摘完了。\n");
    }
    me->set_temp("薄荷",1);
    gc=new("/d/taishan/obj/bohe");
    gc->move(me);
    message_vision("$N摘下了一片薄荷。\n",me);
    return 1;
}