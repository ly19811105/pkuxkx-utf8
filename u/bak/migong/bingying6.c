// This is a room made by roommaker.
// \d\migong\bingying6.c

inherit ROOM;

void create()
{
        set("short", "关口");
        set("long", @LONG
    这是峡谷。两边悬崖万丈，无法攀登。前面有
一大队的蒙古兵和一个当官的在把守着。


LONG   );

 set("objects", ([
      __DIR__"npc/boss6.c" : 1,
//      __DIR__"npc/sboss.c" : 1,
      __DIR__"npc/bing5.c" : 4,
      //__DIR__"npc/sbing1.c" : random(3),
      ]));
set("exits", ([
      //       "up"  : "/u/zhx/migong2/caoyuan.c",
             "east"  : __DIR__"migong6/exit",
             "west"  : __DIR__"xiaocun6/dongmen",
]));
        setup();

}
