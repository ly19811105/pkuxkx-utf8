// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", HIY"国师府大门"NOR);
	set("long", @LONG
这里是国师府的大门，不时有士兵来回巡弋着。
LONG );
	set("exits", ([
		"east"      : __DIR__"north_avenue2",
		//"west" : __DIR__"west_avenue1",
		//"north" : __DIR__"cishi",
		"west" : __DIR__"west_street2",
	]));
	set("outdoors", "lanzhou");
	setup();
}

