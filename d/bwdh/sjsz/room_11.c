//Cracked by Roath
// group bwdh/room 11
// Apache 09/27/98

#include <ansi.h>
inherit ROOM;
#include "sjsz_room.h"

void create() {
    set("short", HIM"西厅"NOR);
    set("long", @LONG
这里是比武场的西厅，四周静悄悄的。空气中已经弥漫
者一股杀气，使你感到不寒而栗。
LONG
    );
    set("exits", ([
        "west"      : __DIR__"room_02",
        "south"     : __DIR__"room_12",
        "northeast" : __DIR__"room_10",
    ]));
    create_room();
    setup();
}

void init() {
    init_room();
}
