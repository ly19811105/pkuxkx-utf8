// workroom.c -> for pretty's 书房

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "碧竹轩");
        set("long", @LONG
一进入这间小屋，你不禁眼前为之一亮。小屋不大，却布置得
雅致而脱俗。屋内没有那些多余的东西，墙上几幅写意的山水画，
窗前的一张檀木案，一张圆凳以及靠墙的一个小书架构成了这间书
房的全部。窗外几竿绿竹掩映，更为这间小屋增添了无数的情趣。
在这里，你会忘记尘世中的一切。
LONG
        );
        
        set("no_fight", 1);
        set("no_steal", 1);
        set("no_drop", 1);
        set("valid_startroom", 1);

        set("exits", ([
                "west"   : __DIR__"bedroom.c",
        ]));

        setup();
}

void init()
{
        add_action("do_out", "out");
}

int do_out(string arg)
{
        object where;
        string path;
        string *sep;
        object me = this_player(1);
        if (arg) return 0;
        me->move("/d/city/guangchang");
        return 1;
}
