// Room: /u/kiss/quanzhen/zhaitang.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "斋堂");
	set("long", @LONG
这是全真教的斋堂，房子中间摆着几张桌子、几把椅子。桌上放着几个大碗，
你一定是饿了吧，那就赶紧坐下(zuo) 吃饭吧。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"zhaichu.c",
  "south" : __DIR__"zoulang6.c",
]));
	
        set("objects",([
"/d/pker/npc/liyu":1
        ]));

	setup();
 }
void init()
{
    add_action("do_zuo","zuo");
	
}

 int do_zuo()
{
   
   object me=this_player();
   if((string)me->query("family/family_name")!="全真派")
  
      return notify_fail("怎么，你想白吃啊！\n");
        if( me->query("food")<350)  me->set("food",me->max_food_capacity());
        if( me->query("water")<350)  me->set("water",me->max_water_capacity());
   message_vision("$N吃饱喝足，站了起来.\n",me);
  return 1;
}

