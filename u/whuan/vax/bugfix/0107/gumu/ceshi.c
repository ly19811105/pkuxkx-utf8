// Room: /d/gumu/ceshi.c 
 
inherit ROOM; 
void create() 
{ 
        set("short", "古墓侧室");
        set("long", @LONG
这里是古墓侧室，四周都是石壁，冷得仿佛要滴下水来，
室内异常的黑暗，只有一张寒玉床(bed)发出幽幽的光。微弱
的光线下，你似乎还看到一条细绳(string)悬在空中。
LONG
        );
	set("no_fight", 1);
     set("book_count",1);
        set("item_desc", ([ /* sizeof() == 2 */
  "bed" : "这是一块极地寒玉雕成的床，室内的阵阵寒意就是从床上发出的。 
那可不是什么人都能睡(shui)的哟。而且好象床底下似乎隐藏着什么。\n",
  "string" : "一条纤细的绳子横悬在室内，总不会是用来晾衣服的吧？\n",
]));
       
        set("exits", ([ /* sizeof() == 3 */
   "south" : __DIR__"zoudao2.c",
]));
        set("no_clean_up", 0);



}
void init()
{
        add_action("do_shui", "shui");
        add_action("do_search", "search");
}
int do_shui(string arg)
{
	  object me;
me = this_player();
if ( (arg != "bed") && (arg != "string") )
    return notify_fail("你打算站着睡觉吗？\n");
if( (int)me->query_skill("changhen-xinfa",1)<20)
    {
        write("你的长恨心法不够，不能睡寒玉床。\n");
	return 1;
	}
if( (int)me->query("max_neili",)<120)
    	{
            write("你内力不够，不能睡寒玉床。\n");
                return 1;
	}
if( (int)me->query("max_neili",)>1000)
   	{
           write("你内力已经较高了。睡寒玉床对你没用。\n");
                return 1;
	}
 if( me->is_busy() )
  return notify_fail("你上一个动作还没有完成呢。\n");  
 
else 	{
 //me->sleep();
message_vision("$N睡在寒玉床上，感到阵阵寒气传来，不得不运内力抵御. 渐渐地，$N睡着了。\n", me);
 me->start_busy(20);  
message_vision("$N感到体内内力四方游动，在抵御寒气的过程中有所增强！\n",me);
  call_out("end",20,me);
 return 1;	}

}
void end(object me)
{	// message_vision("$N睡在寒玉床上，感到阵阵寒气传来，不得不运内力抵御. 渐渐地，$N睡着了。\n", me);
  int i;
i=2*((int)me->query("qi")-50);
me->add("qi",-((int)me->query("qi")-50));
 me->add("neili",i);
if ((int)me->query("neili")>2*(int)me->query("max_neili"))
{me->add("max_neili",1);
me->set("neili",(int)me->query("max_neili"));}
 
 
 // me->set("jing", jing-50);
  //   message_vision("$N感到内力有所提高！\n",me);
}
int do_search(string arg)
{
        object me = this_player();
        object book;
        if (!arg || arg != "bed")
                return notify_fail("你要找什么？\n");
        if (!query("book_count"))
                return notify_fail("床底下空空如也,什么也没有。\n");
        else
        {
                 book = new("/d/gumu/obj/ynxj2");
                book->move(me);
                message_vision("$N从床底下搜出一本《玉女心经下册》。\n",me);
                set("book_count",0);
                return 1;
        }
        return 1;
}

