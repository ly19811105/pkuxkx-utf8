// Room: /d/quanzhen/shijie3.c

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
  "southdown" : __DIR__"shijie4.c",
  "northup" : __DIR__"shijie2.c",
]));
        set("objects", ([
      __DIR__"npc/mosheng" : 1,
        ]));
	set("no_clean_up", 0);
     set("outdoors","quanzhen");
    set("loc",3);
	setup();
	
}

void init()
{
    add_action("do_sao","sao");
}