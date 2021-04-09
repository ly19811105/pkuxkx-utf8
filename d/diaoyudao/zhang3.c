// Room: /d/diaoyudao/zhang3.c 营帐
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
你掀开千疮百孔的帐廉走了进来，一股霉气迎面扑来，地上凌乱地
扔着一些破锅、破碗。看来大军开拔时，已将有用的东西全带走了，剩
下的只是些没用的废物，但你仍鬼迷心窍地到处搜寻。
LONG
	);

	set("exits", ([
         "east" : __DIR__"junying2",
         ]));

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
    if ((me->query_temp("marks/搜3")) && (!(ob = present("chai dao", me))))
        call_out("end1",3,me);
    if (!(me->query_temp("marks/搜3")) || (ob = present("chai dao", me)))
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
//	       me->delete_temp("marks/搜3");
               break;
      case 1:  message_vision("$N找到了一口漏底的锅，你觉得不值钱又扔到了地上。\n",me);
               break;
      default: message_vision("$N累了个半死，结果什么都没有找到。\n",me);
               break;
    }
}

void end2(object me)
{
   object ob,obj;
   switch(random(2)){                   
     case 1:  ob=new("d/diaoyudao/npc/wugong.c");
              ob->move(environment(me));
              message_vision(HIR"突然！爬出一只有毒的大蜈蚣，$N惊出了一一身冷汗。\n",me);
              break;         
     default: message_vision("$N累了个半死，结果什么都没有找到。\n",me);
              break;
   }
}        
