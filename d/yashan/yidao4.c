//模板
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "驿道");
	set("long", @LONG
驿道驿道走到这里逐渐开阔起来．但是人烟却很稀少．
你再往前走，可能还有一个小镇，也说不定呢？
LONG
	);
	set("outdoors", "yanshan");
	set("objects", ([
		"/d/lingxiao/npc/dizi_yashan" : random(2),
		]));
	set("exits", ([ 
		  "southwest" : __DIR__"yidao3.c",
                  "east" : __DIR__"yashanxi3.c",
		]));
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}

