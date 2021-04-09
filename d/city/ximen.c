// Room: /city/ximen.c
// YZC 1995/12/04 

inherit ROOM;
#include <ansi.h>
#include "dating.h"
string look_gaoshi();

void create()
{
	set("short", "西门");
	set("long", @LONG
这是西城门，几年前曾经遭到土匪的攻打，因此显得有些破败。城门正上方
勉勉强强可以认出「西门」两个大字，城墙上贴着几张通缉告示(gaoshi)。西边
是郊外，骑马的、坐轿的、走路的，行色匆匆。东边是城里。
LONG);
        set("outdoors", "city");

	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));
    set("gate","西");
	set("exits", ([
//		"south":"/u/canexpand/seed.c",
        "northwest" : "/d/xinyang/guandaoe3",
		"east" : __DIR__"xidajie3",
//      	"westup" : "/d/pker/shanlu42",
	]));
        set("objects", ([
                "d/city/npc/wujiang1"+random(2) : 1,
                __DIR__"npc/bing" : 2,
        ]));
	setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n扬州知府\n程药发\n";
}

void init()
{
    add_action("do_dating","dating");
    add_action("do_answer","answer");
}