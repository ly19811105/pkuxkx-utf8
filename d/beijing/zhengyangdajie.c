//Cracked by Roath
// Room: /d/beijing/zhengyangdajie.c
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIC"正阳门外大街"NOR);
	set("long",
CYN"这里是京城繁华热闹的地段，街面比外城的要宽阔些，车马人群也多了起来。
街边上有耍枪买艺的、也有些小摊子卖点煎饼果子之类的小吃。往北可以看到正
阳门的城楼，往南是永安门方向。\n"NOR
	);
	set("exits", ([ /* sizeof() == 3 */
  "north" : __DIR__"zhengyangmen",
  "south" : __DIR__"qianmen2",
  "west"  : __DIR__"tianqiao",
  "east"  : __DIR__"zhengyangdajie2",
  "northwest" : __DIR__"changjie",
]));

	set("objects", ([
	__DIR__"npc/foodseller" : 1,
	]));
    
	set("no_clean_up", 0);
	set("outdoors", "beijing");
	set("cost", 2);
	setup();
	replace_program(ROOM);
}
