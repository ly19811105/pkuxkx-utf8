//by binlang
// xiaoyuan.c
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "小院");
        set("long", @LONG
这是绿柳山庄的小院，院中山石古拙，溪池清澈，花卉不多，甚是雅致。
院中有阁，四周池中种着七八株水仙一般的花卉，花作香气，香气优雅。
LONG
        );
        set("exits", ([
            "south" : __DIR__"lvliu1.c",
            "north" : __DIR__"zhengting.c",
            "west"  : __DIR__"xiangfang1.c",
			"east"  : __DIR__"lvliuxiaolu.c",
        ]));
//        set("objects", ([
//            __DIR__"npc/ding2" : 2,
//         ]) );
        set("no_mj_newbie",1);
        setup();
}
