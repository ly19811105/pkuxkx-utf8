//Zine 国战

#include <ansi.h>
inherit __DIR__"room_config.c";

void create()
{
	set("short", "水底" );
	set("long", "这里是一座小桥的水底，因为光线折射的关系，水上的人看不见这里，这里\n却能很清楚的观察到水上的一举一动。\n");
	set("exits", ([
		//"south" : __DIR__"ming_path3",
        //"north" : __DIR__"ming_path4",
        //"northeast" : __DIR__"ming_lin1",
        //"north": __DIR__"ming_path1",
	]) );
	/*set("objects", ([
		__DIR__"npc/wgargoyle":1
	]) );*/
    set("no_reset",1);
    set("no_clean_up", 1);
    set("side","明");
    set("upper_layer","/d/guozhan/ming_qiao");
	setup();
}

