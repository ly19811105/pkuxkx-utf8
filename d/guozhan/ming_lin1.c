//Zine 国战

#include <ansi.h>
inherit __DIR__"room_config.c";

void create()
{
	set("short", "山林" );
	set("long", "前方突然亮了起来，地势渐渐开阔。\n");
	set("exits", ([
		"north" : __DIR__"ming_lin2",
        "southwest" : __DIR__"ming_xiaolu",
        //"west" : __DIR__"flag1",
        //"northeast" : __DIR__"ming_lin1",
        //"north": __DIR__"ming_path1",
	]) );
	/*set("objects", ([
		__DIR__"npc/wgargoyle":1
	]) );*/
    set("no_reset",1);
    set("no_clean_up", 1);
    set("side","明");
    set("land_type","shanlin");
    set("hardness",0);
	setup();
}

