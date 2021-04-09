//模板
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "旧屋");
	set("long", @LONG
这里是一个旧屋，主人不在，门也没锁，
门没锁倒不是因为这里民风如何如何纯朴，
只是因为屋里已经没有任何值钱的东西了，
根本没有必要去花钱配一把锁。
LONG
	);
	set("objects", ([
		"/d/lingxiao/npc/dizi_yashan" : random(2),
		]));
	set("exits", ([ 
		  "north"  : __DIR__"wanxi1.c",
		]));
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}

