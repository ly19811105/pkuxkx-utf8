// Room: /u/kiss/quanzhen/yutang.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIG"浴堂"NOR);
	set("long", @LONG
这是全真教沐浴的地方，几个道士正在这里洗澡，你走了半天了，身上一定
很脏了吧，那就赶紧来洗个澡(bath)吧。旁边有一个大牌子，写着：
                   女  士   止  步
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "north" : __DIR__"gengyis.c",
]));
       set("objects",([
         __DIR__"npc/yudao.c" :1,
            "/clone/npc/camel1" : 0,
         ]));
	set("no_clean_up", 0);
      set("no_fight", 1);

	setup();

}

void init()
{
   add_action("do_bath","bath");
 }


int do_bath( string arg )
{ 
        int intbusytime;
   object me;
   me=this_player();
  if(!arg)
{
  return notify_fail("你要给谁洗澡?\n");
 }
  if(me->query_temp("have_bath"))
 { return notify_fail("你不是刚刚洗过澡了么?遇到不要钱的水就想赚本啊。\n");
  }
        if(arg=me->query("id"))
        {   
                if (this_object()->query("last_visit") == me->query("id"))
                {
                        intbusytime = (int)this_object()->query("count");
                        this_object()->set("count",intbusytime + 1);
                }
                else
                {       
                        this_object()->set("last_visit",me->query("id"));
                        this_object()->set("count",0);
                        intbusytime = 0;
                }

   me->set_temp("have_bath",1);
     me->set("eff_qi",(int)me->query("max_qi"));
     me->set("qi",(int)me->query("max_qi"));
     me->set("eff_jing",(int)me->query("max_jing"));
     me->set("jing",(int)me->query("max_jing"));
     message_vision("$N痛痛快快的洗了一个热水澡,\n",me);
     message_vision("只感觉精神焕发,整个人仿佛脱胎换骨似的\n",me);
                me->start_busy(10 + intbusytime);
   return 1;
  }
}
