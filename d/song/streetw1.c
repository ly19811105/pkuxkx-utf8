// Room: /hangzhou/nandajie2.c
// hubo 2008/4/19 

// Zine 2013 to 临安
inherit "/d/song/song_extra_room";
#include <ansi.h>
void create()
{
	set("short", CYN+"青石街"+NOR);
	set("long", @LONG
这里是统一制式铺就的青石道路，连接和宁门北的中枢官署。
LONG
	);
        set("outdoors", "hangzhou");

	set("exits", ([
		//"westdown" : __DIR__"taimiao",
		"west" : __DIR__"yushitai",
		"south" : __DIR__"heningxi",
		"north" : __DIR__"streetw2",//吏部
		"east" : __DIR__"streetn3",//礼部
	]));

	setup();
}