//模板
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "西驿道");
	set("long", @LONG
驿道走到这里更加开阔起来了．偶尔路上还可以看到
一些行人，但大家都行色匆匆，你不免感到几分寂聊．
LONG
	);
	set("outdoors", "yanshan");
	set("objects", ([
		"/d/lingxiao/npc/dizi_yashan" : random(2),
		]));
	set("exits", ([ 
		  "west" : __DIR__"yidao4.c",
		  "east" : __DIR__"yashanxi2.c",
		]));
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}

