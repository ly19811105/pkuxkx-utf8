inherit ROOM;
#include <room.h>
void create()
{
        set("short", "客房");
        set("long", @LONG

    屋小幽雅，正中一张小几，几上有琴，琴上无弦。旁边一圆凳，凳上鸳
鸯垫。屋角木床。墙角挂着一幅小篆对联：

                [41m    [40m                  [41m    [40m 		
                [41m 焚 [40m                  [41m 惜 [40m
                [41m 琴 [40m                  [41m 香 [40m
                [41m 煮 [40m                  [41m 怜 [40m
                [41m 鹤 [40m                  [41m 玉 [40m
                [41m 从 [40m                  [41m 几 [40m
                [41m 来 [40m                  [41m 个 [40m
                [41m 有 [40m                  [41m 知 [40m
                [41m    [40m                  [41m    [40m
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
		"north" : __DIR__"zoulang2",
]));
        set("objects", ([
// need npc
                        ]) );
      set("sleep_room",1);


        setup();
        

}
