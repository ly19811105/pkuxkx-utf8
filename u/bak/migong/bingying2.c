// This is a room made by roommaker.
// \d\migong\bingying2.c

inherit ROOM;

void create()
{
        set("short", "小兵营");
        set("long", @LONG
    这是一座小兵营。门口站着几个蒙古兵和一个当
官摸样的人。

LONG   );

 set("objects", ([
      __DIR__"npc/boss2.c" : 1,
//      __DIR__"npc/sboss.c" : 1,
      __DIR__"npc/bing1.c" : 3,
      //__DIR__"npc/sbing1.c" : random(3),
      ]));
set("exits", ([
      //       "up"  : "/u/zhx/migong2/caoyuan.c",
             "east"  : __DIR__"migong2/exit",
             "west"  : __DIR__"xiaocun2/dongmen",
]));
        setup();

}
