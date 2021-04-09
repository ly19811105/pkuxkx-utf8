//闯王宝藏
//by steel
#include "ansi.h"
//#include <mimi.h>
inherit ROOM;
void create()
{
     set("short",HIR"闯王宝藏"NOR);
     set("long",@LONG
     你走进了一个密洞,洞内异常的干燥,四周光线昏暗,地上有几具骷髅,
周围散落着一些兵刃,显然这些人死前搏斗过。洞南边的石壁(bi)上似乎
刻着几行小字。洞的北壁上好象有个转盘(pan)似的。
LONG
       );
     set("item_desc",([
        "bi":HIB"余自起事以来，纵横天下十数载，誓杀天下之污吏。后苟居帝\n"
"位，然不意用人不淑，以至满人犯吾华夏，心何憾哉！乃遣密臣藏宝于此\n"
"以备东山再起之用，然不知吾能再斩满狗于漠北否。天若亡我，如之奈何!\n"
"此间金银，皆取于中原之豪富，不可谓之不义。后世小子进得此洞，可尽\n"
"取之，以济天下。若存私窥之心，必遭天遣！\n"NOR,
   ]) );
    set_temp("breaken",0);

        set("number1",1);
        set("number2",1);
        set("number3",1);             
//    set("exits/up", __DIR__"bingya");
    set("objects",([
//          __DIR__"npc/corpse":3,
    ]) );
  setup();
}

void init()
{
   add_action("do_break","break");
   add_action("do_search","search");
   add_action("do_turn","turn");
}

int do_break(string str)
{
   object ob;//room,gold
   ob=this_player();
   if(!str||str!="bi") return 0;
//   if(this_object()->query_temp("breaken")) return notify_fail("石壁已破!\n");
   if((int)ob->query("neili") < 8000)
   {
     message_vision(HIR"结果只听一声闷哼，$N被石壁的反弹力震得眼前一黑....\n"NOR, this_player());
                this_player()->set("neili",0);
                this_player()->unconcious();
        return 1;
   }
//   this_object()->set_temp("breaken",1);
   message_vision(HIW"$N只听一声轰响，石壁被捅穿了，原来里面有一个大洞\n"NOR, this_player());

	if((int)this_player()->query("闯王")<1)
	{
		this_player()->add("combat_exp", 5000);
		this_player()->set("闯王",1);
	}
    this_object()->set("exits/south", __DIR__"midong2");

    this_player()->add("neili",-1000);

  return 1;
}
int do_turn(string arg)
{
    object ob;
    if(!arg) return 0;
    if(arg == "pan")
    {
    	if(objectp(present("flesh corpse", this_object())) || objectp(present("big zombie", this_object())))
    	return notify_fail("你还是先解决掉僵尸再说吧。\n");

    	this_object()->set("exits/up",__DIR__"bingya");
    	tell_room(this_object(), YEL"只听见轧轧声响，头顶上露出个大洞!\n"NOR);
    	call_out("close", 10);
    	return 1;
    }
}

int close()
{
   this_object()->delete("exits/up");
   tell_room(this_object(), YEL"只听见轧轧声响，大洞又合上了!\n"NOR);
   return 1;
}

int do_search()
{
  object me = this_player();
  object ob,obj; 
  int jing;    
  if (me->query_temp("asked_yyd")<1)
  return notify_fail("瞎找什么呢。\n");  
  if( me->is_busy() )
  return notify_fail("你上一个动作还没有完成呢。\n");                       
  jing=me->query("jing");
  if(jing<30)                    
  return notify_fail("你无法集中精力找东西！\n");
  message_vision("$N开始到处搜索，希望能发现点什么。\n",me);

  me->start_busy(2); 
  me->set("jing", jing-10); 
  call_out("end",3,me);
  return 1;
}  
                 
void end(object me)
{
 object ob,bb;
 int i, mount=3;
   if ( query("number3") )
	{
	message_vision("$N正想搜寻什么，忽然出现了几个僵尸．\n" ,me);
 	set("number3", 0);
 	for( i=1;i<=mount;++i )
    		{
 		bb=new(__DIR__"npc/corpse");
   		bb->move(this_object());
   		bb->kill_ob(me);
   		}
	return;
    	}
  else if (query("number1") == 0 && query("number2") == 0 )
        {
                message_vision("$N累了个半死，结果什么都没有找到。\n",me);
                return;
        }
 switch(random(10)){                   
 case 0:
 case 1:  
 case 2:
 case 3:
 case 4:
 case 8:
 case 9:
 case 7:  message_vision("$N累了个半死，结果什么都没有找到。\n",me);
          break;  
 case 6:  if (query("number1")){
          ob=new("/d/reborn/jinyong/obj/yuan-dao.c");
          ob->move(me);
          message_vision("$N找到了一把"+HIC"鸳刀"NOR+"。\n",me);
          set("number1",0);
          }
          break;         
 case 5:  if (query("number2")){
          ob=new("/d/reborn/jinyong/obj/yang-dao.c"); 
          ob->move(me);
          message_vision("$N找到了一把"+HIM"鸯刀"NOR+"。\n",me);
          set("number2",0);
          }
          break;         
 default: message_vision("$N累了个半死，结果什么都没有找到。\n",me);
          break;
 }
} 
