inherit ROOM;
#include <room.h>
void create()
{
        set("short", "厢房");
        set("long", @LONG

    此房小而整洁。墙上一小窗，窗外湖色尽收眼低。墙角立一琵琶，上覆红布，似
乎很久没有用过的样子。窗侧对联一幅，言道：


                [41m    [40m                  [41m    [40m 		
                [41m 易 [40m                  [41m 难 [40m
                [41m 求 [40m                  [41m 得 [40m
                [41m 无 [40m                  [41m 有 [40m
                [41m 价 [40m                  [41m 情 [40m
                [41m 宝 [40m                  [41m 郎 [40m
                [41m    [40m                  [41m    [40m

LONG
        );
        set("exits", ([ /* sizeof() == 4 */
           "south" : __DIR__"zoulang3",
]));
        set("objects", ([
                        ]) );


        setup();
        
}
