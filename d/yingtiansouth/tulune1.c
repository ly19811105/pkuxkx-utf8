//Zine 
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "土路");
        set("long", @LONG
这是一条土路，往西是建康府。往北远远可以望见长江。东北面通向镇江
府，西面通向建康府。
LONG
        );

        set("exits", ([
               "southwest" : __DIR__"tulue2",
               "northeast" : __DIR__"tulune2",

        ]));

        set("outdoors", "yingtianfu");
        setup();
        
}
