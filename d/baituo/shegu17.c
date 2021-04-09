//Cracked by Roath
// shegu.c 蛇谷
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;
string look_crack();

void create()
{
	set("short", "蛇谷树林");
	set("long", @LONG
这是白驼山蛇谷中的一处密林，杂草丛生，树木枝桠茂密，幽暗
阴森，古木盘根错节，有些树根间的裂缝(crack)中响着细碎的声音。
LONG
	);

	set("exits", ([ 
	    "west" : __DIR__"shegu18",
	    "southeast" : __DIR__"shegu16",
	]));

	set("item_desc", ([
	"crack" : (: look_crack :),
	]));

	set("objects", ([
	    "/d/baituo/obj/branch"+(1+random(4)) : 1,
	]));

	set("hide_snake", 1+random(3));
	set("grass", 1);
	set("crack", 1);

	set("cost", 2);
	set("outdoors","baituo");
	set("shegu", 1);
	setup();
}

#include "snake_room.h"
