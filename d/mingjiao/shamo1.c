// by binlangc
//shamo1
#include <room.h>
inherit ROOM;
void create()
{
        set("short","大沙漠");
        set("long", @LONG
这是一片一望无际的大沙漠，连着明教和中原，
你一进来就迷失了方向，赶快离开吧。
LONG
        );
        set("exits", ([
                "south" :__DIR__"shamo3",
                "north" :__DIR__"shamo2",
                "east"  :__FILE__,
                "west"  :__FILE__,
        ]));
        set("outdoors", "mingjiao");
        setup();
}

int valid_leave(object me, string dir)
{
        if ( dir == "west")
                me->add_temp("mark/steps",1);
        if ( dir == "east")
                me->add_temp("mark/steps",-1);
        return ::valid_leave(me,dir);
}
