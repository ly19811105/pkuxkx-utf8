//Zine 国战

#include <ansi.h>
inherit __DIR__"room_config.c";

void create()
{
	set("short", "小桥" );
	set("long", "这里是一座小桥，连接南北。桥上的蚂蚁似乎在搬家。\n");
	set("exits", ([
		"south" : __DIR__"ming_path3",
        "north" : __DIR__"ming_path4",
        //"northeast" : __DIR__"ming_lin1",
        //"north": __DIR__"ming_path1",
	]) );
	set("objects", ([
		__DIR__"npc/ant":1
	]) );
    set("no_reset",1);
    set("no_clean_up", 1);
    set("side","明");
    set("hide",1);
    set("waterside",1);
    set("land_type","pingyuan");
    set("hardness",2);
    set("lower_layer","/d/guozhan/ming_qiaodi");
	setup();
}

