// book.c
// by aiai for xiakedao
/*

Note:
	Check a param in save.c.
*/

#include <ansi.h>

inherit ITEM;

int to_read(string);
void create()
{
	set_name(HIC"侠客行"NOR, ({ "book" }));
     set_weight(6000000);
        set("no_get",1);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long",
			"这是一本刻在石头上的旧书，上面只有一些字迹\n"
			"写的似乎是唐朝李太白的诗句《侠客行》。\n");
		set("value", 1000);
		set("material", "stone");
			
	}
}

void init()
{
object me;
me=this_player();

 add_action("to_read","read");
 add_action("to_read","study");
}                           


int to_read(string arg)
{ 	object me;
      int lvl1,lvl2,lvl3,lvl4,part1,part2,part3,part4,wholepart,seed,times,realtimes;
      int imp;//每次提升的点数，改成和int成反比，修改理由，平衡int的用途
      string book,fail_msg;
	me = this_player();
      imp=me->query("int");
      imp=60-imp;
      imp = imp * SPEWEEK_D->query_learn_bonus()/100; //special week
   if(!arg || (sscanf(arg, "%s %d",book,times) < 1 ))
   {
		return notify_fail("指令格式：read book [次数]\n");
   }
        if (times<1) return notify_fail("你至少要读一次！\n");

     if  (! me->query("xkdling")) return notify_fail("你没有受到邀请，你是怎么混上来的。\n");
	if ( (int)me->query_skill("literate", 1) < 1)
		return notify_fail("你是个文盲，先学点文化(literate)吧。\n");

        if ((int)me->query("jing")< 100)
          {
                 tell_object(me,"你已经很累了，歇歇在读吧,身体要紧。\n");
                 return 1;
                 
          }
        realtimes = times;
        fail_msg = "";
         if ((me->query("jing")-100)/100 < times)
        {
        	realtimes = me->query("jing")/100;
        	fail_msg = "你已经很累了，歇歇在读吧,身体要紧。\n";
        }
	me->add("jing",-100*realtimes);
       	message_vision("$N正专心看着一本石书。\n", me);
        lvl1=(int)me->query_skill("xiake-jianfa",1);
        lvl2=(int)me->query_skill("xiake-strike",1);
        lvl3=(int)me->query_skill("xiake-shengong",0);
        lvl4=(int)me->query_skill("xiake-quanjiao",1);
        part1=lvl2+lvl3+lvl4;
        part2=lvl1+lvl3+lvl4;
        part3=(lvl1+lvl2+lvl4)*3.0/4.0;
        part4=lvl1+lvl2+lvl3;
        wholepart=part1+part2+part3+part4;
        wholepart=random(wholepart);
        if(wholepart<part1)
        {seed=1;}
        else if(wholepart<part1+part2)
        {seed=0;}
        else if(wholepart<part1+part2+part3)
        {seed=2;}
        else
        {seed=3;}
        switch(seed) 
	{
	    case 1:
                 if ( (int)me->query_skill("xiake-jianfa", 1) < 100000)
		{
        if (random(2) == 0)
        {
            me->improve_skill("xiake-jianfa", imp*realtimes );
			write("你认真思索着书中的字句，渐渐领略出一些剑法的奥秘。\n");
        } else {
             me->improve_skill("xiake-daofa", imp*realtimes );
                         write("你认真思索着书中的字句，渐渐领略出一些刀法的奥秘。\n");
        } 
		}
		break;
	    case 0:
               if ( (int)me->query_skill("xiake-strike", 1) < 100000)
		{
            me->improve_skill("xiake-strike", imp*realtimes );
			write("你认真思索着书中的字句，渐渐领略出一些掌法的奥秘。\n");
		}
		break;
            case 2:
//                     write("你认真思索着，但是似乎没能领略出书中的要义。\n");
            me->improve_skill("xiake-shengong", imp*realtimes );
                     write("你认真思索着书中的字句，渐渐领略出一些侠客神功的奥秘。\n");
		break;
            case 3:
            me->improve_skill("xiake-quanjiao", imp*realtimes );
                     write("你认真思索着书中的字句，渐渐领略出一些拳脚的奥秘。\n");
		break;
	}       
	if (fail_msg != "")  tell_object(me,fail_msg);
	return 1;

}
