//Zine 国战

#include <ansi.h>
inherit __DIR__"room_config.c";

void create()
{
	set("short", HIM "誓师坛" NOR);
	set("long", "这里是誓师坛，相传古时点兵誓师开拔的地方。这里插着一面旗帜。\n");
	set("exits", ([
		//"out" : __DIR__"ming_yingwai",
		//"up": __DIR__"ming_wanglou",
        "east" : __DIR__"ming_shan5",
	]) );
	/*set("objects", ([
		__DIR__"npc/wgargoyle":1
	]) );*/
    set("no_reset",1);
    set("no_clean_up", 1);
    set("flag","战神旗");
	setup();
}

