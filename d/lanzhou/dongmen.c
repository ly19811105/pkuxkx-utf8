// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
#include "gate.h"
void create()
{
	set("short", "兰州东门");
	set("long", @LONG
这是兰州的东城门，城门正上方刻着几个西夏文字。城墙上贴着几张官府告
示(notice)。
LONG );
	set("item_desc",(["notice":(:look_notice:)]));
	set("exits", ([
		"west"      : __DIR__"east_avenue1",
		"southup" : __DIR__"wall8",
		"northup" : __DIR__"wall6",
		"south" : __DIR__"outwall8",
		"north" : __DIR__"outwall6",
	]));
	set("outdoors", "lanzhou");
	setup();
}
