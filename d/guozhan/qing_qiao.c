//Zine 国战

#include <ansi.h>
inherit __DIR__"room_config.c";

void create()
{
	set("short", "小桥" );
	set("long", "这里是一座小桥，连接南北。一只蜜蜂嗡嗡地在忙碌着。\n");
	set("exits", ([
		"north" : __DIR__"qing_path3",
        "south" : __DIR__"qing_path4",
        //"northeast" : __DIR__"qing_lin1",
        //"north": __DIR__"qing_path1",
	]) );
	set("objects", ([
		__DIR__"npc/bee":1
	]) );
    set("no_reset",1);
    set("no_clean_up", 1);
    set("side","清");
    set("hide",1);
    set("waterside",1);
    set("land_type","pingyuan");
    set("hardness",2);
    set("lower_layer","/d/guozhan/qing_qiaodi");
	setup();
}

