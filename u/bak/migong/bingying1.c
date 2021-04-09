// This is a room made by roommaker.
// \d\migong\bingying1.c

inherit ROOM;

void create()
{
        set("short", "小桥");
        set("long", @LONG
    这是一座小桥。桥上有两个蒙古兵的十夫长和几个蒙古兵
在盘查过往的行人。桥头的西面好像是个小村庄。

LONG   );

 set("objects", ([
      __DIR__"npc/boss1.c" : 2,
//      __DIR__"npc/sboss.c" : 1,
      __DIR__"npc/bing.c" : random(3),
//      __DIR__"npc/sbing.c" : random(3),
      ]));
set("exits", ([
      //       "up"  : "/u/zhx/migong2/caoyuan.c",
             "east"  : __DIR__"migong1/exit",
             "west"  : __DIR__"xiaocun1/dongmen",
]));
        setup();

}
