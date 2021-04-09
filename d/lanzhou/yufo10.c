// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
#include "/d/menggu/entry_migong.h"
void create()
{
	set("short", "后山小路"NOR);
	set("long", @LONG
这里玉佛寺的后山，两侧种植着一些竹子。
LONG );
	set("exits", ([
		"enter" : __DIR__"yufo9",
		"southup" : __DIR__"yufo11",

	]));
	set("entry_direction","southup");
	set("migong","/d/lanzhou/lanshan");
	set("migong_posi","north");
	set("look_refuse_msg","突然有个僧人出现，阻止了你的窥探。\n");
	set("enter_refuse_msg","突然有个僧人出现，阻止你进入后山。\n");
	set("outdoors", "lanzhou");
	setup();
}

