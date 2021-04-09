// Room: /ningyuan.c

inherit ROOM;

void create()
{
	set("short", "宁远");
	set("long", @LONG
这里是关外驻防的军事重镇。城高河宽，守备森严，城楼上不但有大量
的官兵驻防，甚至还有几门红衣火炮，架设其上。城门旁几名官兵正在检察
来往行人的物品，不时传来几声叱骂之声。
LONG
	);

	set("exits", ([
		"southwest" : __DIR__"guandao3",
		"north" : __DIR__"lyddao1",
	]));

        set("objects", ([
                 "/d/beijing/npc/bj_bing" : 4,
        ]));


        set("outdoors", "changbai");
        set("cost", 2);

	setup();
	replace_program(ROOM);
}

