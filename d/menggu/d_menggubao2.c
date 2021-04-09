// Room: menggubao.c
// created by Zine 30 Aug 2010
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "蒙古包");
	set("long", @LONG
这里是一顶蒙古包，草原上的牧人都住在里面。
LONG
	);

	set("exits", ([
		"southeast" : __DIR__"helin_path1",
		"southwest" : __DIR__"d_menggubao0",
		//"northeast" : __DIR__"d_menggubao2",
        "northwest" : __DIR__"d_menggubao1",
        //"north" : __DIR__"d_menggubao1",
        "south" : __DIR__"d_menggubao3",
	]));
		set("no_robber",1);
		set("sleep_room", "1");
        set("outdoors", "menggu_m");
	set("objects", ([
        	__DIR__"npc/muyangren" : random(2),
	]));
	setup();
}
