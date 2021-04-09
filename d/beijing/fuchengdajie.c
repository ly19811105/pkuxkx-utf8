// Room: /d/beijing/fuchengdajie.c
#include <ansi.h>
inherit ROOM;

void fix_exits_for_night(int is_night)
{
    if (is_night) {
	set("exits", ([ /* sizeof() == 3 */
	  "east" : __DIR__"beihai",
	  "south" : __DIR__"fuchengdajie_s",
	  "north" : __DIR__"fuchengdajie_n",
//	  "southeast" : __DIR__"west/fuyoujie2",
	]));
    } else {
	set("exits", ([ /* sizeof() == 3 */
	  "west" : __DIR__"fuchengmen",
	  "east" : __DIR__"beihai",
	  "south" : __DIR__"fuchengdajie_s",
	  "north" : __DIR__"fuchengdajie_n",
//	  "southeast" : __DIR__"west/fuyoujie2",
	]));
    }
}

void create()
{
	set("short", HIC"阜成门大街"NOR);
	set("long",
CYN"这是繁华热闹的阜成门外大街，大街街面宽阔，车水马龙，川流不息，人群
熙熙攘攘，来来往往。街边上耍枪买艺、百货小吃，应有尽有，帝都风貌可见一
斑。东边可以看见北海。\n"NOR
	);

	fix_exits_for_night(0);
	set("outdoors", "beijing");
	set("cost", 2);

	setup();
}
string GATE_OUT_DIR1 = "west";
string GATE_OUT_DIR2 = "";
#include "gate.h"
