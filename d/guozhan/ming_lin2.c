//Zine 国战

#include <ansi.h>
inherit __DIR__"room_config.c";

void create()
{
	set("short", "山林" );
	set("long", "此处树冠遮蔽，一点光也透不下来，如果遭遇敌人，肯定是一场乱战。\n");
	set("exits", ([
		"north" : __DIR__"ming_lin3",
        "south" : __DIR__"ming_lin1",
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
    set("hunzhan",1);
    set("land_type","shanlin");
    set("hardness",2);
	setup();
}

