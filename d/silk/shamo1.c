// Room: /d/xingxiu/shamo1.c
// Modified by iszt@pkuxkx, 2007-03-31

inherit ROOM;

#include "shamo.h"

void create()
{
	set("short","大沙漠");
	set("long", @LONG
这是一片一望无际的大沙漠。你一进来就迷失了方向。看来要走出这块沙漠
并非易事。
LONG);
	set("outdoors", "xingxiuhai");
	set("exits", ([
		"east" : __DIR__"silk4",
		"west" : __DIR__"shamo2",
		"south" : __FILE__,
		"north" : __FILE__,
	]));
	setup();
}