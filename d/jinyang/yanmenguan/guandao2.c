#include <ansi.h>
inherit __DIR__"yanmenguan.c";

void create()
{
	set("short", "官道");
	set("long", @LONG
这是一条官道，前方是一段土路，不远处就是雁门关了。路上生长着很多野
草(cao)。
LONG
	);

    set("exits", ([
        "northeast" : __DIR__"guandao",        
        "south" : __DIR__"tulu",
        ]));
    set("item_desc", ([
		"cao" : "人马踏过，野草将会倒伏，这样很容易被追兵发现行踪，必须遮掩(zheyan)一下。\n", 
	]));
    set("road_no",2);
    set("objects", ([
		
        __DIR__"npc/mes" : 1,
		
	    ]));
	set("outdoors", "jinyang");
	setup();
	
}



