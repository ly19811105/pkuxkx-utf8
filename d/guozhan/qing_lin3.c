//Zine 国战

#include <ansi.h>
inherit __DIR__"room_config.c";

void create()
{
	set("short", "山林" );
	set("long", "这里很大的一处山林，但地势比东南面平缓得多了。\n");
	set("exits", ([
		"southwest" : __DIR__"ming_shan5",
        "northeast" : __DIR__"qing_lin2",
        //"west" : __DIR__"flag1",
        //"northeast" : __DIR__"ming_lin1",
        //"north": __DIR__"ming_path1",
	]) );
	/*set("objects", ([
		__DIR__"npc/wgargoyle":1
	]) );*/
    set("no_reset",1);
    set("no_clean_up", 1);
    set("side","清");
    set("hide",1);
    set("land_type","shanlin");
    set("hardness",0);
	setup();
}

