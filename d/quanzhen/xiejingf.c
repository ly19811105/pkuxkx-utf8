// Room: /u/kiss/quanzhen/xiejingf.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIB"写经房"NOR);
	set("long", @LONG
写经房是全真教编写经书的地方，房中有几个道童正在忙着抄写经书，屋里
摆着五、六张长方桌，上面堆着高高的一叠经书，旁边一副对联，乃马珏所作:
        手握灵珠常奋笔，心开天籁不吹箫。
南边是经楼，东边是钟阁。
LONG
	);
	set("exits", ([ /* sizeof() == 3 */
  "west" : __DIR__"zoulang10.c",
  "south" : __DIR__"jinglou.c",
  "east" : __DIR__"zhongge.c",
]));
   set("objects",([
   __DIR__"npc/jingdao" : 1,
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
