#include <ansi.h>
inherit __DIR__"yanmenguan.c";

void create()
{
	set("short", YEL"土路"NOR);
	set("long", @LONG
这里一条土路，东面是一条大河。
LONG
	);

    set("exits", ([
        "east" : __DIR__"hebian",   
        "west" : __DIR__"huanglu0",
        "northwest" : __DIR__"huanglu1",
        "southwest" : __DIR__"huanglu2",
        ]));
    set("road_no",18);
    set("objects", ([
		
        __DIR__"npc/mes" : 1,
		
	    ]));
	set("outdoors", "jinyang");
	setup();
	
}

int gene_path()
{
    object ob=this_object();
    string * dirs=({"west","northwest","southwest"});
    string dir=dirs[random(sizeof(dirs))];
    ob->set("yanmen/step1",dir);
    dir=dirs[random(sizeof(dirs))];
    ob->set("yanmen/step2",dir);
    dir=dirs[random(sizeof(dirs))];
    ob->set("yanmen/step3",dir);
    return 1;
}


