//train2.c
//modified from xo
//by zoom
//2003.3.30

inherit ROOM;

void create()
{
        set("short", "钱庄");
        set("long", @LONG
这是一家老字号的钱庄，已有几百年的历史，在全国各地
都有分店。它发行的银票信誉非常好，通行全国。这里是专门
为新手练习而开设的。
    在对面的墙上挂了块牌子(paizi)，上面写的是这里能用的
指令，练习一下吧，要是没钱，就先去菜园赚点吧。
[1;32m[提示]：可以用look 指令查看牌子(look paizi)[37;0m
LONG );
set("no_fight", 1);
        set("no_clean_up", 0);
        set("item_desc", ([
                "paizi" : @TEXT
     本钱庄提供以下服务：
      存钱        deposit或者cun
      取钱        withdraw或者qu
      钱币兑换    convert或者duihuan
      查帐        check或者chazhang
TEXT
        ]) );
set("exits",  ([
        "east"  : __DIR__"train2_center.c",
      ]));
        set("objects", ([
                __DIR__"npc/qboss" : 1,
        ]));
        setup();
        replace_program(ROOM);
}

