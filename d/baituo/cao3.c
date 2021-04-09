//room:cao2.c
inherit ROOM;
void create()
{
  set("short","草丛");
  set("long",
        "这里是乱草丛。四面都是齐腰高的蒿草，你不知道该怎么走才能\n"
    "走出去了。\n"
    "    这里到处都是毒蛇，真是有白驼山庄的特色呀！\n"
    "    你突然发现西边的蒿草似乎长得比较低矮，有些还被踩倒了，似\n"
    "乎有人经常从那里走！\n"
      );
  set("exits",([
      "west"  :   __DIR__"zhulin",
      "north" :   __DIR__"cao"+(random(3)+1),
      "east"  :   __DIR__"cao"+(random(3)+1),
       "south" :   __DIR__"cao"+(random(2)+1),
     ]));
 set("objects",([
      __DIR__"npc/qingshe" : random(2),
      __DIR__"npc/jinshe" : random(2),
      __DIR__"npc/snake" : random(2),
      ]));
 set("outdoors","baituo");
 setup();
 replace_program(ROOM);
}
