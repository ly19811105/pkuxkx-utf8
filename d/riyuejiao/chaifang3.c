//chaifang2.c	柴房
//by bing
#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short","柴房");
	set("long",@LONG 
这里原先是一所柴房，现在已经被烧得面目全非，到出是残余
的灰烬，空气中弥漫着一股呛人的烟气，偶尔还能听到木头清脆的
爆裂声，还有剩余的火苗在顽强的燃烧着。
LONG
	);
        set("number",random(5)-3);
	set("exits", ([
		"east" : __DIR__"cunlu3",
	]));
	setup();

}


void init()
{
    object me=this_player();
    int i,count=0;
    object chai;
    object *all=all_inventory(this_object());
    add_action("do_get","get");
    add_action("do_search","search");
    for (i=0;i<sizeof(all);i++)
    {
        if (all[i]->query("is_chai"))
        {
            count=1;
        }
    }
    if (userp(me)&&me->query("rynewbiejob/chufang/start")&&count<1)
    {
        chai=new(__DIR__"obj/chai");
        chai->move(this_object());
    }
}

int do_get(string arg)
{
    object me=this_player();
    if (arg=="all")
    {
        tell_object(me,"这里只能一件一件拿东西。\n");
        return 1;
    }
    if (arg=="chai huo"||arg=="chai"||arg=="chaihuo")
    {
        if (!me->query("rynewbiejob/chufang/start"))
        {
            tell_object(me,"一根柴火也偷，真是辱没你在江湖的威名啊。\n");
            return 1;
        }
        if (present("chai huo",me))
        {
            tell_object(me,"你身上不是有一根柴火了吗？\n");
            return 1;
        }
    }
}

int do_search()
{
  object me = this_player();
  object ob,obj; 
  int jing;    
  if( me->is_busy() )
  return notify_fail("你上一个动作还没有完成呢。\n");                       
  jing=me->query("jing");
  if(jing<30)                    
  return notify_fail("你无法集中精力找东西！\n");
  message_vision("$N开始在灰烬中搜索，希望能发现点什么。\n",me);

  me->start_busy(2); 
  me->set("jing", jing-10); 
  call_out("end",3,me);
  return 1;
}  
                 
void end(object me)
{
 object ob;
 if (query("number") == 0)
	{
		message_vision("$N累了个半死，结果什么都没有找到。\n",me);
		return;
	}
 switch(random(10)){                   
 case 0:
 case 1:  message_vision("$N发现了一只烧熟了的老鼠，闻了闻觉得不好，扔在了一边\n",me);
          break;
 case 2:
 case 3:
 case 4:
 case 8:
 case 9:
 case 7:  message_vision("$N累了个半死，结果什么都没有找到。\n",me);
          break;  
 case 6:  ob=new(__DIR__"obj/riyuedao.c");
          ob->move(me);
          message_vision("$N翻了翻残余的树枝，忽然兴奋地叫了一声，捡起一把" + HIR "日月神刀" NOR + "。\n",me);
	  set("number",0);
          break;         
 case 5:  ob=new(__DIR__"obj/riyuejian.c");
          ob->move(me);
          message_vision("$N翻了翻残余的树枝，忽然兴奋地叫了一声，捡起一把" + HIG "日月神剑" NOR + "。\n",me);
	  set("number",0);
          break;         
 default: message_vision("$N累了个半死，结果什么都没有找到。\n",me);
          break;
 }
}        
