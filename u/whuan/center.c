// Room: /city/guangchang.c 
// HSR 1997/9/16  
// whuan add auto backup at 2008/4/28 
#include <ansi.h> 
   
inherit ROOM;
   
void create()
{  
   set("short", "中央广场");
   set("long", @LONG   
这里是城市的正中心，一个很宽阔的广场，铺着青石地面。一些游手好闲的   
人在这里溜溜达达，经常有艺人在这里表演。中央有一棵大榕树，盘根错节，据 
传已有千年的树龄，是这座城市的历史见证。树干底部有一个很大的洞(shudong)。
你可以看到北边有来自各地的行人来来往往，南面人声鼎沸，一派繁华景象，东   
边不时地传来朗朗的读书声，西边则见不到几个行人，一片肃静。
LONG);  
   set("no_sleep_room",1);  
   set("outdoors", "city"); 
   
   set("item_desc", ([ 
   "shudong" : "这是一个黑不溜湫的大洞，里面不知道有些什么古怪。\n",  
   "baoku" : "你觉得一阵头晕，有一种想呕吐的感觉。\n", 
   ])); 
   
   set("exits", ([
                "east" : __DIR__"dongdajie1",   
                "south" : __DIR__"nandajie1",   
                "west" : __DIR__"xidajie1",
                "north" : __DIR__"beidajie1",   
                "up" : __DIR__"shangyuetai",    
                "down" : __DIR__"xiaojinku",    
   ])); 
   set("objects",([    
 "/clone/gift/gifttree":1,  
 "/clone/npc/camel1":1,
   ])); 
   
   setup();  
   "/clone/board/ct_b"->foo();   
}  
   
void init()  
{  
   object me=this_player();
   if (interactive(me))
   {
 remove_call_out("greeting");
 call_out("greeting", 1, me);
   }  
   add_action("do_enter", "enter");   
   add_action("do_none", "dz");  
   add_action("do_none", "dazuo");    
   add_action("do_none", "study");    
   add_action("do_none", "du");  
   add_action("do_none", "lian");
   add_action("do_none", "practice"); 
   add_action("do_none", "exercise"); 
   add_action("do_none", "tuna");
   add_action("do_none", "respirate");
   add_action("do_none", "xiulian");  
   add_action("do_climb", "climb");   
}  
void greeting(object ob)
{
   int news; 
   news=NEWS_D->query_new(ob);  
   if(news)  
   {    
   write(HIY+"您有"+HIG+chinese_number(news)+HIY"条系统新闻未读，请使用"   
    HIR"news new"+HIY"这个命令来阅读，这对您很重要。\n"+NOR);  
   }    
  if ((int)ob->query_skill("jinwu-dao", 1)>0)  
   {    
  ob->set_skill("lieyan-dao",ob->query_skill("jinwu-dao",1));    
  ob->delete_skill("jinwu-dao");
  tell_object(ob,"明教金乌刀法已经改成烈焰刀法。\n");    
  "/cmds/skill/enable.c"->main(ob,"blade lieyan-dao");    
  "/cmds/skill/enable.c"->main(ob,"parry lieyan-dao");    
  "/cmds/skill/wbei.c"->main(ob,"shenghuo-shengong lieyan-dao");    
   }    
   if (ob->query("mud_age")-ob->query("last_backup_mudage")>36000 
   && ob->query("combat_exp")>=200000)   
   {    
  "/cmds/usr/backup.c"->main(ob);
  tell_object(ob,HIY"系统帮您备份了档案。\n"NOR);    
   }    
   else if (ob->query("mud_age")-ob->query("last_backup_mudage")>36000 
   && ob->query("combat_exp")>=200000)    
  tell_object(ob,HIG"你有很长一段时间没有备份档案了，
  请使用"HIR+"backup"+HIG"命令来备份。\n"NOR);  
}   
int do_none()
{  
   write("中央广场，禁止刷屏！\n");   
   return 1; 
}  
   
int do_enter(string arg)    
{  
   object me;
   me = this_player(); 
   
   if( !arg || arg=="" ) return 0;    
   
   if(me->is_busy() || me->is_fighting())  
 return notify_fail("你先忙完了再钻洞吧。");    
   
   if( arg=="shudong" )
   {    
 message("vision",
    me->name() + "一弯腰往洞里走了进去。\n",    
    environment(me), ({me}) );   
 me->move("/d/gaibang/inhole");  
 message("vision",
    me->name() + "从洞外走了进来。\n",
    environment(me), ({me}) );   
 return 1;   
   }    
   
   if( arg=="baoku" )  
   {    
 message("vision",
    me->name() + "本来好端端在这里的，忽然消失了，好象人间蒸发了一样。\n",    
    environment(me), ({me}) );   
 me->move("/d/city/baoku"); 
 message("vision",
    me->name() + "不知道从哪里冒出来的，吓了你一跳。\n",  
    environment(me), ({me}) );   
 return 1;   
   }    
}  
int valid_leave(object me, string dir)
{  
   if(dir == "up" && me->query("age")>16 && !wizardp(me)) 
   return notify_fail("绿萼白了你一眼道：「都那么大了还来白吃，不害羞。」\n");
   return ::valid_leave(me, dir);
}  
   
int do_climb(string arg)    
{  
   object liumang;
   object me=this_player(); 
   
   if( !arg || arg != "tree" )   
 return notify_fail("爬什么？\n");    
   if( me->is_fighting() || me->is_busy() )
 return notify_fail("你现在正忙着呢。");   
   me->start_busy(random(3));    
   if( me->query("qi") < (int)(me->query("max_qi")/3) ) { 
 me->receive_damage("qi", (int)me->query("max_qi")*20/100);    
 return notify_fail("你身子发虚，一头栽了下来，哎呀！\n");
   }    
   if( (int)me->query_skill("dodge",1) < 50 ) { 
tell_object(me,"你小心翼翼的往上爬了一点，觉得头晕眼花，就赶紧爬了下来．\n"); 
me->improve_skill("dodge", 40-me->query("str"));
tell_object(me, "你领悟出一些基本轻功方面的窍门。\n");    
   } else {  
message_vision("$N像只小猴子一样在树上窜上窜下。\n", me); 
if (!random(5)) { 
message_vision(HIY"$N双臂平展，姿势优美的跳到了赏月台上。\n"NOR, me);    
me->move(__DIR__"shangyuetai");  
message_vision(HIC"$N蹭的一声，从树上跳到了赏月台里。\n"NOR, me);   
   }    
   }    
   me->receive_damage("qi", (int)me->query("max_qi")*10/100);  
   return 1; 
}  
