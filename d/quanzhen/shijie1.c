// Room: /u/hacky/quanzhen/shijie1.c
// Made by: hacky
// modified by Zine Qz newbiejob
#include <ansi.h>
inherit ROOM;
#include "sao.h"
void create()
{
	set("short", "石阶");
	set("long", @LONG
你走在一条又窄又陡的石阶上，一边是悬崖，一边是峭壁，你不禁有些害怕。
上面就是重阳宫。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"shijie2.c",
  "northup" : __DIR__"gongmen",
]));
    set("loc",1);
	set("no_clean_up", 0);
     set("outdoors","quanzhen");

	setup();
}

void init()
{
    add_action("do_sao","sao");
}
