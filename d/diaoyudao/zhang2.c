// Room: /d/diaoyudao/zhang2.c 营帐
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
这里象是士兵居住的营帐，帐里挂满了蜘蛛网，显然是很久没人
进来过了，地上扔着些废弃的酒袋、吃剩下的鸡骨头......你在营帐
里仔细的搜寻着，想看看是否还有值钱的东西。
LONG
	);

	set("exits", ([
         "west" : __DIR__"junying1",
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
    if ((me->query_temp("marks/搜2")) && (!(ob = present("chai dao", me))))
        call_out("end1",3,me);
    if (!(me->query_temp("marks/搜2")) || (ob = present("chai dao", me)))
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
//	       me->delete_temp("marks/搜2");
               break;
      case 1:  message_vision("$N找到了一个全是窟窿的酒袋，你觉得不值钱又扔到了地上。\n",me);
               break;
      default: message_vision("$N累了个半死，结果什么都没有找到。\n",me);
               break;
    }
}

void end2(object me)
{
   object ob,obj;
   switch(random(2)){                   
     case 1:  ob=new("d/diaoyudao/npc/snake.c");
              ob->move(environment(me));
              message_vision(HIR "突然！窜出一条毒蛇，$N惊出了一身冷汗。\n"NOR,me);
              break;         
     default: message_vision("$N累了个半死，结果什么都没有找到。\n",me);
              break;
   }
}        
