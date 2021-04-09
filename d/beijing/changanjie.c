// Room: /d/beijing/changanjie.c
#include <ansi.h>
#include "beijing_defs.h"
inherit ROOM;

void create()
{
	set("short", HIC"长安街"NOR);
	set("long",
CYN"这是繁华热闹的长安街，大街北面就是守卫森严的紫禁城
南门天安门了。这里时常有巡逻的侍卫盘查过路的行人。大街
两边是各种店铺，你看的眼都花了。\n"NOR
	);
	set("exits", ([ /* sizeof() == 3 */
  "north"  : "/d/beijing/zijin/tianansquare",
  "south" : __DIR__"zhengyangmen",
  "east"  : __DIR__"changanjie_e2",
  "west"  : __DIR__"changanjie_w2",
]));
	set("outdoors", "beijing");
	setup();
}

void init()
{
    if (random(5) == 1)
	HELPER->clonehere_with_limit(this_object(), "/d/beijing/npc/randomnpc.c", 8);
}
