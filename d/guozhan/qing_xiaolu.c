//Zine 国战

#include <ansi.h>
inherit __DIR__"room_config.c";

void create()
{
	set("short", "小路" );
	set("long", "这里是一条弯弯曲曲的小路，北边是清军大营，东南，西南和正南分别不知\n通向何处。\n");
	set("exits", ([
		"south" : __DIR__"qing_path1",
        "southwest" : __DIR__"qing_lin1",
        "southeast" : __DIR__"qing_shan1",
        "north": __DIR__"qing_yingwai",
	]) );
	/*set("objects", ([
		__DIR__"npc/wgargoyle":1
	]) );*/
    set("no_reset",1);
    set("no_clean_up", 1);
    set("side","清");
    set("land_type","pingyuan");
    set("hardness",0);
	setup();
}

