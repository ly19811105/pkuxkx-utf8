// Room: /d/beijing/zijin/longzong.c
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIY"隆宗门"NOR);
	set("long",
HIC"这儿是靠近皇帝住所养心殿和军机处的一道重要禁门。除奏事、
待旨或被召见的官员准许通过外，王公大臣亦不得随便出入。\n"NOR
	);
	set("exits", ([ /* sizeof() == 2 */
  	"west" : __DIR__"cininggong",
  	"east" : __DIR__"xiaohuayuan",
]));
	set("outdoors", "beijing");
	setup();
	replace_program(ROOM);
}
