//train2.c
//modified from xo
//by zoom
//2003.3.30

#include <ansi.h>

inherit F_HOCKSHOP;

void create()
{
set("short", "当铺");
set("long", @LONG
这是一家以买卖公平著称的当铺，一个五尺高的柜台挡在你的面前，柜台上摆
着一个牌子(paizi)，柜台后坐着当铺老板，一双精明的眼睛上上下下打量着你。
当铺是玩家交易物品的地方，如果什么想找什么东西，可以先到当铺看看，尤其
是扬州的当铺，东西是很全的哦。
[1;32m[提示]:可以用look 指令查看牌子(look paizi)
       这里可以使用的命令有(dang)、(shu)、(list)、(sell)、(buy)[37;0m。
LONG );
set("no_fight", 1);
set("exits",  ([
        "west"  : __DIR__"train2_center.c",
      ]));
        set("item_desc", ([
                "paizi" : "公平交易\n卖东西：sell id(或name) [number]\n买东西：buy id(或name)\n当东西：pawn(dang) id\n赎东西：retrieve(shu) piao\n看可卖物品：list\n估价：value id\n",
        ]));

        set("objects", ([
//                __DIR__"npc/xx" : 1,
        ]));
        setup();
		unique_id=7;
		setup_shop();

}