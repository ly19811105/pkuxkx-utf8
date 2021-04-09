//Zine 25 Nov 2010

#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "望江亭");
        set("long", @LONG
这是长江岸边的一座小亭，虽然没有雕龙画凤，却是青山之畔，大江之滨的一处所在。
从这里望出去，只见滚滚长江东去，江面上白帆点点，一眼望不到边。你不禁胸中豪气
大生，只觉得这世间万事，都不过如此。
LONG
        );
        set("exits", ([
             "down" : __DIR__"dkb1",
        ]));
        set("objects",([
            "/d/jiaofei/npc/qqz.c":1,
        ]));
        setup();
}

void init()
{
  //  add_action("look_jiang","look");
}

int look_jiang(string arg)
{
    //if(arg == "jiang")
    //{
    
    //}
    return 0;
}