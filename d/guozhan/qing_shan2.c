//Zine 国战

#include <ansi.h>
inherit __DIR__"room_config.c";

void create()
{
	set("short", "蜿蜒山路" );
	set("long", "这里是一条蜿蜒的山路，两端一眼望不到头。\n");
	set("exits", ([
		"southeast" : __DIR__"qing_shan3",
        "northeast" : __DIR__"qing_shan1",
        //"northeast" : __DIR__"qing_lin1",
        //"north": __DIR__"qing_path1",
	]) );
	/*set("objects", ([
		__DIR__"npc/wgargoyle":1
	]) );*/
    set("no_reset",1);
    set("no_clean_up", 1);
    set("side","清");
    set("hide",1);
    set("arrow",1);
    set("land_type","shandi");
    set("hardness",2);
	setup();
}

