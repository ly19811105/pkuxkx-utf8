//train3_keting.c
//by zoom
//2003.3.30

#include <ansi.h>

inherit ROOM;

void create()
{
set("short", "客厅");
set("long", @LONG
这里是新手学堂的客厅， 北墙贴着一张山水画，一看就知是名家手笔，倚
墙放着一张红木桌，两张太师椅。使者正陪着武师，两人各坐在一张太师椅上。
桌上放置着一盘盆景。 左右两边的廊柱下放着一排红木椅，间隔着放着几张茶
几，茶几上摆放一些时鲜花木。
LONG );
set("no_fight", 1);
set("exits",  ([
        "out"  : __DIR__"train3.c",
        "up"   : __DIR__"train4.c",
        "west"   : __DIR__"train3_xiuxi.c",
      ]));
        set("objects", ([
                __DIR__"npc/xmaster" : 1,
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        if (!wizardp(me) && me->query_temp("newbie/bai")!=5&&dir!="west"&&!mapp( this_player()->query("family") ))
                return notify_fail("既然来了，就好好练习一下吧。\n");
return ::valid_leave(me, dir);
} 


