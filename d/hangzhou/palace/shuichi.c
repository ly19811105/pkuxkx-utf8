// Room: /hangzhou/nandajie2.c
// hubo 2008/4/19 

// Zine 2013 to 临安
inherit "/d/hangzhou/song_room";
#include <ansi.h>
#include "/d/song/xunshi.h"
void create()
{
	set("short", "莲池");
	set("long", @LONG
这里是一座莲池，满池的莲花正在盛开。
LONG
	);
        set("outdoors", "hangzhou");

	set("exits", ([
		"south" : __DIR__"jiashan",
		"east" : __DIR__"daqing",
		//"west" : __DIR__"wall1",
		//"north" : __DIR__"yudao1",
		//"enter" : __DIR__"chuigong2",
	]));
	set("objects", ([
		//__DIR__"npc/wujiang" : 1,
		//"/d/hangzhou/npc/songbing_z" : 1,
        ])); 
	setup();
}