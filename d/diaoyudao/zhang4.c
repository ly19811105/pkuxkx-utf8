// Room: /d/diaoyudao/zhang4.c 营帐
// hongdou 98.09.20

#include <ansi.h>
inherit ROOM;

void init()
{
	add_action("do_search", "search");
}

void create()
{
	set("short", "营帐");
	set("long", @LONG
这间营帐几乎已经没有了顶棚，完全暴露在天空下，由于阳
光照射和雨水的滋润，帐里已经长出了野草，并且非常旺盛。你
用脚在草丛中搜寻着，看看草中藏着什么东西。
LONG
	);

	set("exits", ([
          "west" : __DIR__"junying2",
            ]));

	set("outdoors", "diaoyudao");
	setup();
}

int do_search()
{
    object me = this_player();
    object ob,obj;
    int jing;    
    if(!(me->query_temp("marks/搜1")) && !(me->query_temp("marks/搜2")) &&
	!(me->query_temp("marks/搜3")) && !(me->query_temp("marks/搜4")))
       {   me->set_temp("marks/搜"+(random(4)+1),1); }
    if( me->is_busy() )
    return notify_fail("你上一个动作还没有完成呢。\n");                       
    jing=me->query("jing");
    if(jing<30)                    
    return notify_fail("你无法集中精力找东西！\n");
    message_vision("$N开始在帐篷里乱翻，希望能找到一些值钱的东西。\n",me);
    me->start_busy(2); 
    me->set("jing", jing-10); 
    if ((me->query_temp("marks/搜4")) && (!(ob = present("chai dao", me))))
        call_out("end1",3,me);
    if (!(me->query_temp("marks/搜4")) || (ob = present("chai dao", me)))
        call_out("end2",3,me);
    return 1;
}  
                 
void end1(object me)
{
    object ob,obj;
    switch(random(3)){                   
      case 2:  message_vision("$N找到了一把破柴刀，放在身上。\n",me);
               obj=new(__DIR__"obj/chaidao");
               obj->move(me);
//	       me->delete_temp("marks/搜4");
               break;
      case 1:  message_vision("$N找到了一件破军服，你觉得不值钱又扔到了地上。\n",me);
               break;
      default: message_vision("$N累了个半死，结果什么都没有找到。\n",me);
               break;
    }
}

void end2(object me)
{
   object ob,obj;
   switch(random(2)){                   
     case 1:  ob=new("d/diaoyudao/npc/xiyi.c");
              ob->move(environment(me));
              message_vision("$N惊出了一只大蜥蜴。\n",me);
              break;         
     default: message_vision("$N累了个半死，结果什么都没有找到。\n",me);
              break;
   }
}        
