//Cracked by Roath
// Room: /lyddao1.c

inherit ROOM;

void create()
{
	set("short", "大道");
	set("long", @LONG
你走在一条碎石铺成的大道上，道两旁种着笔直通天的白杨树，放眼向
两侧望去，全是无边无际的田野，天边处仿佛有几座低矮的丘陵，为平坦的
大地增加了几许柔和的曲线。路上行人渐渐稀少起来。
LONG
	);

	set("exits", ([
		"south" : __DIR__"ningyuan",
		"northeast" : __DIR__"lyddao2",
	]));

        set("objects",([
                __DIR__"npc/juren2" : 1,
        ]));

        set("outdoors", "changbai");
        set("cost", 2);

	setup();
	replace_program(ROOM);
}

