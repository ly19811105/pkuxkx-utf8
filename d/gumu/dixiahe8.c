// /d/xingxiu/dixiahe8.c
// Jay 3/17/96
#include "dixiahe.h"

void create()
{
        set("short", "地下河");
        set("long", @LONG
    这是一条地下河，表面上看起来很平静。河里有许多
漩涡，游起来该注意一下，别走进漩涡里去了。北边有些光亮，
好象到了岸了。
LONG
        );

        set("exits", ([
    /*    "northeast" : __FILE__,
        "southeast" : __FILE__,
        "southwest" : __FILE__,
        "northwest" : __FILE__,*/
        "north" : __DIR__"hean",
        "west" : __DIR__"dixiahe2",
        "south" : __DIR__"dixiahe6",
        "east" : __DIR__"dixiahe3",
        ]));
        setup();
//        replace_program(ROOM);
}
