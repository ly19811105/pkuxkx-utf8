// Room: jiedao2.c

inherit ROOM;

void create()
{
        set("short", "街道");
        set("long", @LONG
吐蕃国皇城的街道比起中原大城来要窄小些，也冷清许多。青石漫铺的路两
边已经被压出两道深深的车辙。压碎的青石板下裸露出的泥土呈现出脏乎乎的黑
色，被冻得硬邦邦的。看来吐蕃当今赞普大大重视军备于民生。东边漂来一阵酒
香，看来有家酒馆。西面是织造作坊。
LONG
        );

        set("exits", ([
                "north" : __DIR__"zanpugc",
                "south" : __DIR__"jiedao1",
                "east" : __DIR__"yixianglou",
                "west" : __DIR__"zuofang",
        ]));
        set("outdoors", "雪山");

   setup();
}

