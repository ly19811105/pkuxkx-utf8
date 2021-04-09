// Room: /d/gumu/ceshi.c 
#include <ansi.h>
#include "/d/gumu/bonus.h"
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

		setup();



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
if (arg=="string")
    return notify_fail("你的功力似乎不足以这样。\n");
if( (int)me->query_skill("yunu-xinfa",1)<20&&me->query("combat_exp")>10000)
    {
        write("你的玉女心法不够，不能睡寒玉床。\n");
	return 1;
	}
if ( me->query("family/family_name")!="古墓派" )
{
  write("旁边传来古墓弟子走动的声音，你感觉在这里修炼内功似乎并不是一个好的选择。\n");
  return 1;
}	
if( (int)me->query("max_neili",)<120&&me->query("combat_exp")>10000)//新手任务
    	{
            write("你内力不够，不能睡寒玉床。\n");
                return 1;
	}
/*if( (int)me->query("max_neili",)>1000)
   	{
           write("你内力已经较高了。睡寒玉床对你没用。\n");
                return 1;
	}
*/   //现在加入了和内力大小有关的完成时间，假如10000内力，需要(random(100)+15)*2获得内力升级，可以回归小说，高内力也允许睡床了。Zine Nov 11 2010
 if( (int)me->query("qi",)<200 &&me->query("combat_exp")>10000)
   	{
           write("你的气血太低。睡寒玉床对你有害无益。\n");
                return 1;
	}
 if( me->is_busy() )
  return notify_fail("你上一个动作还没有完成呢。\n");  
 
else 	{
 //me->sleep();

 me->add_busy(2);  
write("你躺在寒玉床上，开始运功抵御寒气。\n");
  call_out("checkst",2,me);
 return 1;	}

}

int checkst(object me)  //by Zine Nov 11 2010 原先的start_busy(20)有bug,玩家可以用解busy离开后继续获得寒玉床好处
{
    
    string* desc=({"你睡在寒玉床上，感到阵阵寒气传来，不得不运内力抵御。\n","你潜运内力，试图抵御寒气，却未能成功。\n","你的内力和寒气相互融合，成功只在一线之间。\n","你感到体内内力四方游动，在抵御寒气的过程中有所增强！。\n",});
    string* color=({HIW,WHT,HIC,CYN}),msg;
    int max,min,n,exp,pot,neili,jingli;
	if (!me||!living(me)) return 1;
    if ((me->query_temp("hanyuchuang")>15+random(me->query("max_neili")/100)&&me->query("combat_exp")>10000)
        ||(random(me->query_temp("hanyuchuang"))>20 && me->query("combat_exp")<=10000))
    {
        if (base_name(environment(me))!="/d/gumu/ceshi")
        {
            tell_object(me,"你不知道自己为何离开了寒玉床，难道是梦游？\n");
            return 1;
        }

        else
        {
            if (me->query("combat_exp")<=10000&&me->query("family/family_name")=="古墓派") //newbie Job Zine
            {
                if (me->query("combat_exp")<5000)
                {
                    n=3;
                }
                else if (me->query("combat_exp")<8500)
                {
                    n=4;
                }
                else
                {
                    n=6;
                }
                me->add("qi",-random(10));
                message_vision(HIW"$N冻得瑟瑟发抖，却发觉自己的功力有了进境。\n"NOR,me);
                exp=n*(int)me->query_temp("hanyuchuang")*2/3;
                pot=random(exp);
				msg=HIW"对抗寒气中，你增加了经验EXP点，潜能POT点！\n"NOR;
                bonus(me,2,exp,pot,0,msg);
				me->set_temp("hanyuchuang",0);
                return 1;

            }
            me->set_temp("hanyuchuang",0);
            if (me->query("qi")-50 > me->query("max_neili")*2-me->query("neili"))
            {
                max=(int)me->query("qi")-50;
                min=(int)me->query("max_neili")*2-(int)me->query("neili");
                if (min<0){min=0;}
                me->add("qi",-(min)/2);
                me->add("neili",min+1);
                
            }
            if (me->query("qi")-50 <= (me->query("max_neili")*2-me->query("neili")))
            {
                me->add("neili",((int)me->query("qi")-50)*2+1);
                me->add("qi",-((int)(me->query("qi")-50)));
                
            }
            
            if ((int)me->query("neili")>2*(int)me->query("max_neili"))
            {
                me->add("max_neili",1);
                me->add("exercised_neili",1);
                me->set("neili",(int)me->query("max_neili"));
            }
            write (HIW"你只觉得寒气与你内力完全融合，运转一周天。\n");
            return 1;
         
        }
    }
    else
    {
        if (base_name(environment(me))!="/d/gumu/ceshi")
        {
            tell_object(me,"你不知道自己为何离开了寒玉床，难道是梦游？\n");
            return 1;
        }
        tell_object(me,color[random(sizeof(color))]+desc[random(sizeof(desc))]+NOR);
        me->add_temp("hanyuchuang",1);
        me->start_busy(2);
        call_out("checkst",1+random(2),me);
        //if (me->query("combat_exp")<=10000) //newbie Job Zine
        //{
        //}
        return 1;
    }
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
		{
	         write("你要找什么？\n");
			 return 1;
		}
        if (!query("book_count"))
	{
                write("床底下空空如也,什么也没有。\n");
				return 1;
	}
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

