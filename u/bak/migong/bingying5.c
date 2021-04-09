// This is a room made by roommaker.
// \d\migong\bingying5.c

inherit ROOM;

void create()
{
        set("short", "大帐");
        set("long", @LONG
    这是兵营成片，你不由地停下了脚步。


LONG   );

 set("objects", ([
      __DIR__"npc/boss5.c" : 1,
//      __DIR__"npc/sboss.c" : 1,
      __DIR__"npc/bing4.c" : 3,
      //__DIR__"npc/sbing1.c" : random(3),
      ]));
set("exits", ([
      //       "up"  : "/u/zhx/migong2/caoyuan.c",
             "east"  : __DIR__"migong5/exit",
             "west"  : __DIR__"xiaocun5/dongmen",
]));
        setup();

}
