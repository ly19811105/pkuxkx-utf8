//模板
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "牙山湾南路");
	set("long", @LONG
这里曾经还是一片繁华地，可是现在多处的地方
都已经是人去楼空，不过听说这里附近经常会有一些
美国商人在这里贩卖军火，从中牟取暴利，也许仗打
起来从他们那里获得军火是唯一的办法呢？
LONG
	);
	set("outdoors", "yanshan");
	set("objects", ([
		"/d/lingxiao/npc/dizi_yashan" : random(2),
		]));
	set("exits", ([ 
           "west" : __DIR__"zahuopu.c",
          "east" : __DIR__"haitan.c",
		  "north" : __DIR__"center.c",
		  "south" : __DIR__"wansouth2.c",
		]));
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}

