//Zine 国战

#include <ansi.h>
inherit __DIR__"room_config.c";

void create()
{
	set("short", "小路" );
	set("long", "这里是一条弯弯曲曲的小路，南边是明军大营，东北，西北和正北分别不知\n通向何处。\n");
	set("exits", ([
		"south" : __DIR__"ming_yingwai",
        "northwest" : __DIR__"ming_shan1",
        "northeast" : __DIR__"ming_lin1",
        "north": __DIR__"ming_path1",
	]) );
	/*set("objects", ([
		__DIR__"npc/wgargoyle":1
	]) );*/
    set("no_reset",1);
    set("no_clean_up", 1);
    set("side","明");
    set("land_type","pingyuan");
    set("hardness",0);
	setup();
}

