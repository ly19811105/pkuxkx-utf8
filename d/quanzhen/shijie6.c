// Room: /d/quanzhen/shijie6.c

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
  "southeast" : __DIR__"shijie7.c",
  "north" : __DIR__"shijie5.c",
]));
        set("objects",([
       __DIR__"npc/kid.c" : 2,
       ]));

     set("outdoors","quanzhen");
	set("no_clean_up", 0);
    set("loc",6);
	setup();
	
}

void init()
{
    add_action("do_sao","sao");
}