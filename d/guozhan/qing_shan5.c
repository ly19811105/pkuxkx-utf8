//Zine 国战

#include <ansi.h>
inherit __DIR__"room_config.c";

void create()
{
	set("short", "蜿蜒山路" );
	set("long", "这里是一条蜿蜒的山路，东面是一个庞大的古建筑，南面是一片老林子。\n");
	set("exits", ([
		"south" : __DIR__"ming_lin3",
        "northeast" : __DIR__"qing_shan4",
        "east" : __DIR__"flag2",
        //"northeast" : __DIR__"ming_lin1",
        //"north": __DIR__"ming_path1",
	]) );
	/*set("objects", ([
		__DIR__"npc/wgargoyle":1
	]) );*/
    set("no_reset",1);
    set("no_clean_up", 1);
    set("side","清");
    set("hide",1);
    set("land_type","shandi");
    set("hardness",0);
	setup();
}

