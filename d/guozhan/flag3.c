//Zine 国战

#include <ansi.h>
inherit __DIR__"room_config.c";

void create()
{
	set("short", HIB "落魂坡" NOR);
	set("long", "这里是落魂坡，相传古时大战在这里死过很多人。这里插着一面旗帜。\n");
	set("exits", ([
		//"out" : __DIR__"ming_yingwai",
		"north": __DIR__"qing_path4",
        "south" : __DIR__"ming_path4",
	]) );
	/*set("objects", ([
		__DIR__"npc/wgargoyle":1
	]) );*/
    set("no_reset",1);
    set("no_clean_up", 1);
    set("flag","战魂旗");
    set("land_type","shandi");
	setup();
}

