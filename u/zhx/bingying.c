// This is a room made by roommaker.

inherit ROOM;

void create()
{
        set("short", "大草原");
        set("long", @LONG
这里是著名内蒙古大草原。
    你一走进来，只听得喊杀震天。这里宋军和蒙古兵正在撕
杀。满山边野，到处都是断掉的兵器和尸体。你看到如此
惨烈的情景，不由得发了疯，不辩东西南北地到处乱跑。

LONG   );

 set("objects", ([
      __DIR__"npc/boss.c" : 1,
      __DIR__"npc/sboss.c" : 1,
      __DIR__"npc/bing.c" : random(2),
      __DIR__"npc/sbing.c" : random(2),
      ]));
set("exits", ([
             "up"  : __DIR__"caoyuan20",
             "east"  : __DIR__"caoyuan17",
             "west"  : __DIR__"caoyuan18",
]));
        setup();

}
