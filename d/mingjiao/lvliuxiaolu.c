#include <room.h>
inherit ROOM;
void create()
{
	set("short", "小路");
	set("long", @LONG
这是绿柳山庄旁的一条小路，紧贴着山庄的外墙，路旁花草繁茂，香气袭人。
LONG);
	set("exits", ([
		"west"  :__DIR__"xiaoyuan",
	]));
	set("objects",([
		__DIR__"npc/xiaosi.c" : 1,
	]));
	set("no_mj_newbie",1);
	setup();
}

