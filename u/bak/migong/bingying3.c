// This is a room made by roommaker.
// \d\migong\bingying3.c

inherit ROOM;

void create()
{
        set("short", "兵营");
        set("long", @LONG
    这是一座兵营。门口站着几个蒙古兵和一个当
官摸样的人。他们正在划拳喝酒。

LONG   );

 set("objects", ([
      __DIR__"npc/boss3.c" : 1,
//      __DIR__"npc/sboss.c" : 1,
      __DIR__"npc/bing1.c" : 3,
      //__DIR__"npc/sbing1.c" : random(3),
      ]));
set("exits", ([
      //       "up"  : "/u/zhx/migong2/caoyuan.c",
             "east"  : __DIR__"migong3/exit",
             "west"  : __DIR__"xiaocun3/dongmen",
]));
        setup();

}
