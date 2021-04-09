//洛阳，扩展地图
//by kiden
//2006-9-8
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", HIC"四海钱庄"NOR);
        set("long", @LONG
四海钱庄乃洛阳城最大的钱庄。也是非常有名的老字号。老板正是中
国第一巨贾，红顶商人胡雪源，乃山西人氏，这家钱庄从他的爷爷的爷爷
的爷爷的爷爷那辈开始办起，一直传到他手里，声誉非常好，在全国各地
都有分店。它发行的银票通行全国。钱庄的门口挂有一块牌子(paizi)。
LONG
        );
        set("item_desc", ([
                "paizi" : @TEXT
     本钱庄提供以下服务：
      存钱        deposit或者cun
      取钱        withdraw或者qu
      钱币兑换    convert或者duihuan
      查帐        check或者chazhang
TEXT
        ]) );

        set("exits", ([
               "north" : __DIR__"xidajie1",  
               "south" : __DIR__"yanhuapu", 
        ]));
        set("objects", ([
        __DIR__"npc/hu":1,
//                __DIR__"npc/hu" : 1,
        ]));

        setup();
        replace_program(ROOM);
}

