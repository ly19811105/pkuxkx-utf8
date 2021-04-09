// File         : gudi.c
// Created By   : iszt@pkuxkx, 2007-02-26
// whuan添加谜题
#include <ansi.h>
#include "snow.h"

inherit ROOM;

void create()
{
        set("short", HIW"谷底"NOR);
        set("long", @LONG
你睁开双眼，发现自己身处深谷之中。
LONG);

        set("outdoors", "凌霄城");

        set("item_desc", ([
                "snow": (: snow :),
        ]));

        set("exits", ([
                "southeast" : __DIR__"xueguan.c",
        ]));

        set("no_task",1);
       set("no_die",1);
        setup();
}
void init()
{
        add_action("do_look", "kan");
        add_action("do_look", "view");
        add_action("do_look", "observe");
        add_action("do_look", "look");
}
int do_look(string arg)
{
        object me = this_player();
        if (!me->query_temp("jinwudao/ask_axiu4") && !me->query_temp("jinwudao/ask_axiu3")) return 0;
        tell_object(me,"你仔细看了看四周，发现周围似乎有一些脚印，旁边的冰壁上有人刻着：“"+HIG"史小翠救阿绣于此！"+NOR"”\n");
        me->set_temp("jinwudao/ask_xiaocui1",1);
        return 0;
}        
