// Room: /hangzhou/gongdian2.c
// hubo 2008/4/19

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "宫殿走廊");
        set("long", @LONG
这好象是一个古代宫殿的走廊，满地都是白骨和骷髅，你每走一步都心
跳加快。
LONG);
        set("exits", ([
                "out" : __DIR__"gongdian1",
                "north" : __DIR__"gongdian3",    
]));

       set("objects", ([
                        "/d/guiyunzhuang/obj/kulou.c" : 3,
                        "/d/guiyunzhuang/obj/baigu.c" : 2,
           ]));  
          
   setup();
}
