//洛阳，扩展地图
//by kiden
//2006-9-8
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", HIC"长乐坊"NOR);
        set("long", @LONG
在大门上挂者一块黑色的帘子，帘子上绣了个大大的“赌”字，原来
这里是一个赌场，就开在路边，好招摇呀！走进赌场，却发现里面的布置
如此繁华，热闹。金钱敲击之声不绝于耳，押注时的的吆喝声充斥了每个
人的耳朵，古语曰“十赌九输“，一旦踏进这里就难以回头了，不输个倾
家荡产，妻离子散你是不知道后悔的，只有少数几个赢家才是赌徒们羡慕
的对象和内心的希望。
LONG
        );
        set("item_desc", ([
        ]) );

        set("exits", ([
               "east" : __DIR__"nandajie1",             
        ]));
        set("objects", ([
                __DIR__"npc/randomnpc2" : random(5),
        ]));

//        set("outdoors", "luoyang");
        setup();
        replace_program(ROOM);
}
