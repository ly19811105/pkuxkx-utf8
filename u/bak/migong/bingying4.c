// This is a room made by roommaker.
// \d\migong\bingying4.c

inherit ROOM;

void create()
{
        set("short", "关卡");
        set("long", @LONG
    蒙古兵在这里设了个关卡，防止有人偷袭。有几个蒙古
    兵和一个当官摸样的人正严阵以待，警惕地四处观望。

LONG   );

 set("objects", ([
      __DIR__"npc/boss4.c" : 1,
//      __DIR__"npc/sboss.c" : 1,
      __DIR__"npc/bing3.c" : 3,
      //__DIR__"npc/sbing1.c" : random(3),
      ]));
set("exits", ([
      //       "up"  : "/u/zhx/migong2/caoyuan.c",
             "east"  : __DIR__"migong4/exit",
             "west"  : __DIR__"xiaocun4/dongmen",
]));
        setup();

}
