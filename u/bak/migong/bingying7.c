// This is a room made by roommaker.
// \d\migong\bingying7.c

inherit ROOM;

void create()
{
        set("short", "帅俯");
        set("long", @LONG
    这是蒙古兵的元帅大帐。蒙古大元帅蒙哥正和
他的几个亲兵在聊天。
//在盘查过往的行人。桥头的西面好像比东面杀声更响。

LONG   );

 set("objects", ([
      __DIR__"npc/boss7.c" : 1,
//      __DIR__"npc/sboss.c" : 1,
      __DIR__"npc/bing6.c" : 5,
      //__DIR__"npc/sbing1.c" : random(3),
      ]));
set("exits", ([
      //       "up"  : "/u/zhx/migong2/caoyuan.c",
             "east"  : __DIR__"migong7/exit",
         //    "west"  : __DIR__"migong4/entry",
]));
        setup();

}
