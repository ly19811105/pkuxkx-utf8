//Zine 国战

#include <ansi.h>
inherit __DIR__"room_config.c";

void create()
{
	set("short", HIC "点将台" NOR);
	set("long", "这里是点将台，相传古时拜将的地方。这里插着一面旗帜。\n");
	set("exits", ([
		//"out" : __DIR__"ming_yingwai",
		//"up": __DIR__"ming_wanglou",
        "west" : __DIR__"qing_shan5",
	]) );
	/*set("objects", ([
		__DIR__"npc/wgargoyle":1
	]) );*/
    set("no_reset",1);
    set("no_clean_up", 1);
    set("flag","战歌旗");
	setup();
}

