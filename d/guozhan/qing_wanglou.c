//Zine 国战

#include <ansi.h>
inherit __DIR__"room_config.c";

void create()
{
	set("short", HIG "大清了望塔" NOR);
	set("long", "这里清军大营的了望塔，这里可以对整个形势一目了然(liao)。\n");
	set("exits", ([
		
		"down": __DIR__"qing_ying",
	]) );
	/*set("objects", ([
		__DIR__"npc/wgargoyle":1
	]) );*/
    set("no_reset",1);
    set("no_clean_up", 1);
    set("wanglou",1);
	set("land_type","non_horse");
    setup();
}

