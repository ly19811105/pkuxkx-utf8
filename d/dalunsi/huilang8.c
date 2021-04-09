// Room: huilang8.c

inherit ROOM;

void create()
{
        set("short", "遮雨廊");
        set("long", @LONG
一道不算太宽的长廊，通向几座主要的大殿，廊顶和廊柱上满布壁画，描写
了历史人物事迹和佛教故事，色彩艳丽，形象逼真。
LONG
        );

        set("exits", ([
                "east" : __DIR__"boluomiyuan",
                "westup" : __DIR__"zhudubadian",
                "south" : __DIR__"huilang6",
        ]));
        set("outdoors", "雪山");

        setup();
}

