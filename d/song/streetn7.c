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
		"south" : __DIR__"streetn6",
		//"west" : __DIR__"heningbei",
		//"north" : __DIR__"streetn7",//吏部
		"west" : __DIR__"bujundu",//礼部
	]));

	setup();
}