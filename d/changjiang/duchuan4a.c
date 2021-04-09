// Room: /d/shaolin/duchuan.c
// Date: YZC 96/01/19

inherit ROOM;




void create()
{
	set("short", "长江渡船");
	set("long", @LONG
一叶小舟，最多也就能载七、八个人。一名六十多岁的老艄公
手持长竹篙，正在船尾吃力地撑着船。
LONG
	);

    set("no_task",1);
	set("outdoors", "changjiang");
	setup();
	
}


void init()
{
    int i;
    object * all=all_inventory(this_object());
    object clue;
    for (i=0;i<sizeof(all);i++)
    {
        all[i]->delete_temp("cjallowed");
    }
    
}

#include "event.h"