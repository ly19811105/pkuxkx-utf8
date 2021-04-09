// Room: nacheng.c

inherit ROOM;

void create()
{
	set("short", "南城");
	set("long", @LONG
这里是用黄土铺就的街道，街上的行人不多，看起来很冷清。偶尔有几
个身着异域服饰的行人走过，看起来是满族，鲜祖的居民。
LONG
	);

	set("exits", ([
		"south" : __DIR__"muqiao",
		"north" : __DIR__"jishi",
//                "west" : __DIR__"xrguan",
	]));

        set("objects",([
      //          __DIR__"npc/juren2" : 1,
      //          __DIR__"npc/juren3" : 1,
                __DIR__"npc/teng" : 1,
        ]));

        set("outdoors", "changbai");
        set("cost", 3);

	setup();
	replace_program(ROOM);
}

