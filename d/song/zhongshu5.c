// Room: /hangzhou/nandajie2.c
// hubo 2008/4/19 

// Zine 2013 to 临安
inherit "/d/song/song_extra_room";
#include <ansi.h>
void create()
{
	set("short", "中书值房");
	set("long", @LONG
这里中书省的正官的值房。
LONG
	);
        //set("outdoors", "hangzhou");

	set("exits", ([
		//"westdown" : __DIR__"taimiao",
		//"south" : __DIR__"zhongshucourt",
		//"north" : __DIR__"zhongshu3",
		"west" : __DIR__"zhongshu2",//吏部
		//"east" : __DIR__"zhongshu5",//礼部
	]));
	set("objects", ([
          __DIR__"npc/zhongshuling" : 1,
        ]));
	setup();
}