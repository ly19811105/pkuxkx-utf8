// Room: /d/xingxiu/xxroad1.c

inherit ROOM;

void create()
{
        set("short", "大道");
        set("long", @LONG
你走在一条青石大道上。东面通向长安城。
LONG
        );
     /*   set("objects", ([
                  "/d/riyuejiao/npc/qinweibang" : 1,
        ]));*/

        set("exits", ([
//    "south":"/d/anqimen/xiaodao.c",
        "east" : "/d/changan/anyuanmen",
        "west" : __DIR__"xxroad2",
        "north" : "/d/changan/xiaodaonw1",
]));

        set("no_clean_up", 0);
        set("outdoors", "xingxiuhai");

        setup();
        replace_program(ROOM);
}

