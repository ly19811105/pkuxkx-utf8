//Zine 国战

#include <ansi.h>
inherit __DIR__"room_config.c";

void create()
{
	set("short", "山林" );
	set("long", "这里很大的一处山林，但地势比北面的高山平缓得多了。\n");
	set("exits", ([
		"south" : __DIR__"ming_lin2",
        "north" : __DIR__"qing_shan5",
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
    set("hide",1);
    set("land_type","shanlin");
    set("hardness",0);
	setup();
}

