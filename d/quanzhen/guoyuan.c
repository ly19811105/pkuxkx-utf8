// Room: /u/kiss/quanzhen/guoyuan.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", GRN"果园"NOR);
set("outdoors","quanzhen");
	set("long", @LONG
你走到了一个很大的果园，里面栽着各种各样的果树，结着各种各样诱人的
果实，有梨子、苹果、橘子，新鲜诱人，你不禁想摘(zhai)几个来吃了。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"yaopu.c",
  "east" : __DIR__"qichao.c",
]));
	set("no_clean_up", 0);

	setup();
}

void init()
{
 add_action("do_zhai","zhai");
 }

int do_zhai(string arg)
{
 object me=this_player();
 object obj1,obj2,obj3;
 if(!arg||arg=="")
 return notify_fail("你要摘什么?\n");

 if(arg!="梨子"&&arg!="苹果"&&arg!="橘子")
 return notify_fail("这儿可没有你要的东西!\n");

 if(me->query_temp("have_food")>=7)
 return notify_fail("你也太贪心了吧!!!\n");

 if(arg=="梨子") {
 message_vision("$N从梨子树上摘下一个梨子。\n",me);
 obj1=new(__DIR__"npc/obj/lizi.c");
 obj1->move(me);
 me->add_temp("have_food",1);
 return 1;}

 if(arg=="苹果") {
 message_vision("$N从苹果树上摘了一个苹果。\n",me);
 obj2=new(__DIR__"npc/obj/pingguo.c");
 obj2->move(me);
 me->add_temp("have_food",1);
 return 1; }

 if(arg=="橘子") {
 message_vision("$N从橘子树上摘了一个橘子。\n",me);
 obj3=new(__DIR__"npc/obj/juzi.c");
 obj3->move(me);
 me->add_temp("have_food",1);
 return 1;
}
} 
 
 
