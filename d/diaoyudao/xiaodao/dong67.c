// Rewrote by iszt@pkuxkx, 2007-02-11
#include "dong.h"
inherit ROOM;

void create()
{
    setshort();
    setlong();

    set("exits", ([
        "north" : __DIR__"dong03",
        "south" : __DIR__"dong68",
    ]));
    setobject();

//  set("no_clean_up", 0);
 //   setobject();
    set("outdoors", "xiaodao");
    setup();
    replace_program(ROOM);
}
