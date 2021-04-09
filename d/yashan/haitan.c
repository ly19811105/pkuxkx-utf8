//模板
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "海滩");
	set("long", @LONG
从这里，你可以看到茫茫的黄海，海面
上虽然现在是风平浪静，偶尔还可以看到几
只海鸥在海面上为了同一条鱼互相争食，弱
小一点的海鸥发出凄厉的叫声，不禁让你想
到我们如画的山河即将受到外敌的入侵，而
清政府却如此软弱，你不禁低头叹了一声气，
你手中的拳头握得更紧了......
LONG
	);
	set("outdoors", "yanshan");
	set("objects", ([
		"/d/lingxiao/npc/dizi_yashan" : random(2),
		]));
	set("exits", ([ 
		  "west"  : __DIR__"wansouth1.c",
		]));
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}

