//模板
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "西驿道");
	set("long", @LONG
这里行人渐多，偶尔你还可以看到一些清兵从
这里跑过，你知道这里一定里牙山湾不远了，边陲
重镇的气息已经逐渐呈现在你的面前了．．．．
LONG
	);
	set("outdoors", "yanshan");
	set("objects", ([
		  __DIR__"npc/qingbing.c": 1,
		]));
	set("exits", ([ 
		  "west" : __DIR__"yashanxi3.c",
		  "east" : __DIR__"yashanxi1.c",
		]));
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}

