// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
#include "gate.h"
void create()
{
	set("short", "兰州西门");
	set("long", @LONG
这是兰州的西城门，城门正上方刻着几个西夏文字。城墙上贴着几张官府告
示(notice)，这里隐隐约约可以听见黄河奔腾的声音。
LONG );
	set("item_desc",(["notice":(:look_notice:)]));
	set("exits", ([
		"east"      : __DIR__"west_avenue1",
		"southup" : __DIR__"wall4",
		"northup" : __DIR__"wall1",
		"south" : __DIR__"outwall4",
		"north" : __DIR__"outwall1",
	]));
	set("outdoors", "lanzhou");
	setup();
}

