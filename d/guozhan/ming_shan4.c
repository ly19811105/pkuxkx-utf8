//Zine 国战

#include <ansi.h>
inherit __DIR__"room_config.c";

void create()
{
	set("short", "崎岖山路" );
	set("long", "这里是一条崎岖的山路，两端都看不见尽头。\n");
	set("exits", ([
		"south" : __DIR__"ming_shan3",
        "northwest" : __DIR__"ming_shan5",
        //"northeast" : __DIR__"ming_lin1",
        //"north": __DIR__"ming_path1",
	]) );
	/*set("objects", ([
		__DIR__"npc/wgargoyle":1
	]) );*/
    set("no_reset",1);
    set("no_clean_up", 1);
    set("side","明");
    set("hide",1);
    set("land_type","shandi");
    set("hardness",1);
	setup();
}

