//yxiang2.c
//by hehe
//2003.3.5

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "厢房");
    set("long", @LONG
燕子坞的厢房，摆设了精致的家具，不时有仆人过来打扫房间。
LONG
    );

    set("exits", ([
		"north" : __DIR__"yxiang4",
		"east" : __DIR__"yyuan1",
    ]));

	set("objects", ([
		"/d/murong/npc/binu" : 2,
		]));

    setup();

}
