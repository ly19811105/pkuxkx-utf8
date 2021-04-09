// exercise.c

#include <ansi.h>
#include <skill.h>

inherit F_CLEAN_UP;

int exercising(object me);
int halt_exercise(object me);

int main(object me, string arg)
{
	int exercise_cost;
	string skill;
	object where;

	seteuid(getuid());
	where = environment(me);
	
	if (where->query("pigging"))
		return notify_fail("你还是专心拱猪吧！\n");

	if (me->is_busy() || me->query_temp("pending/exercising"))
		return notify_fail("你现在正忙着呢。\n");

	if( me->is_fighting() )
		return notify_fail("战斗中不能练内功，会走火入魔。\n");

	if( !stringp(me->query_skill_mapped("force")) )
		return notify_fail("你必须先用 enable 选择你要用的内功心法。\n");


 	if( (int)me->query("qi") < me->query("max_qi")/2)
		return notify_fail("你现在的气太少了，无法产生内息运行全身经脉。\n");

	if( (int)me->query("jing") * 100 / (int)me->query("max_jing") < 70 )
		return notify_fail("你现在精不够，无法控制内息的流动！\n");

    	me->set_temp("pending/exercise", 1);
 	me->set_temp("exercise_cost", 64);
	skill=me->query_skill_mapped("force");
 	message_vision(MAG"\n$N盘膝坐下，默运"+to_chinese(skill)+",一股内息自丹田引出,渐渐流向奇经八脉......\n\n"NOR, me);
	me->call_out("start",me,3);
        me->start_busy(5,(:halt_exercise,me:));
	return 1;
}
int start(object me)
{
	if(!me->is_busy()) return 0;
	tell_object(me,HIW"......你心中存想，缓缓催动体内气息运行周天。\n"
 	"          只觉体内一股热气直透上来,你进入了一种玄妙的境界......\n\n"NOR);    
        me->start_busy( (: exercising,me:), (: halt_exercise,me:) );
	return 1;
}

int exercising(object me)
{
	string skill;
	int skill_gain,gift_gain;
	int myint,mykar,mycon;
	int exercise_cost = (int)me->query_temp("exercise_cost");
	int neili_gain = (int)me->query_skill("force") / 8;
	skill=me->query_skill_mapped("force");
	myint=me->query("int");
	mykar=me->query("kar");
	mycon=me->query("con");
	
	if(!random(30)) {
		if(me->query("eff_qi")<me->query("max_qi")) me->add("eff_qi",1);
		if(me->query("eff_neili")<me->query("max_neili")) me->add("eff_neili",1);
		if(me->query("eff_jing")<me->query("max_jing")) me->add("eff_jing",1);
		if(me->query("eff_jingli")<me->query("max_jingli")) me->add("eff_jingli",1);
	}
	if ( random( 11 ) > 9 )
       	tell_object( me,
	HIW"......你的内息在体内沿着经脉要穴不断运转，感觉你的内力\n"
        "	正在不断的凝集......\n\n"NOR );
        else if ( random( 10 )<1)
       	tell_object( me,
	HIC"......你只觉天地之精慢慢渗入体内,在百会、人中、神阕、丹田、会阴、命门等要穴\n"
        "	间不住流转，然后散之于四肢体骸......\n\n"NOR);
	if(me->is_fighting()&&!random(30))
	{
            	switch ( random( 4 ) )
		{
            		case 0 :
                	tell_object(me, HIY "你觉得内息有些混乱。\n" NOR );
			break;
            		case 1 :
                	tell_object(me, HIY "你感觉到内力有失控的迹象。\n" NOR );
			break;
            		case 2 :
                	tell_object(me, HIY "你觉得有些胸闷头痛，心里很烦躁。\n" NOR );
                	break;
                   	case 3:
                 	tell_object(me, HIR "由于你在战斗中强行修炼内功，你走火入魔了！\n" NOR );
			break;
		}
		log_file("static/zouhuo",sprintf(" %s(%s) 走火入魔于%s,共失去%d点内力\n", me->query("name"),me->query("id"),ctime(time()),me->query("max_neili")*1/7));   
 		me->set("max_neili",me->query("max_neili")*6/7);
		me->set("eff_neili",me->query("eff_neili")*6/7);
 		me->set_temp("pending/exercise", 0);
		return 0;
	}
 	if ( !random( 30 ) )  {
		/*内功修为领悟的进度跟定力、悟性、根骨、内功级别、最大内力有关*/
		gift_gain=4*me->query_int()+3*me->query("con");
		gift_gain=sqrt(gift_gain);
		skill_gain=sqrt(me->query_skill("force",1)+me->query("max_neili")/10);
		if(skill_gain<1) skill_gain=1;
		skill_gain=gift_gain*skill_gain;
		me->improve_skill("force",skill_gain/2);
		me->improve_skill(skill,skill_gain/4);
	}
	if ( exercise_cost >= 10 )
	{
		me->add("neili",2+neili_gain*(5*me->query("kar")+2*me->query("con")+2*me->query("int"))/150);
		if ((int)me->query("neili") > (int)me->query("max_neili") * 2)
            	if ((int)me->query("max_neili") < (int)me->query_skill("force") * 10) 
		{
                        me->add("max_neili", 1);
			me->add("eff_neili",1);
     			me->set("neili", me->query("neili")-(int)me->query("max_neili"));
			me->set_temp("add_neili",1);
		}
         	me->add_temp( "exercise_cost", -1 );
		return 1;
	}
 	if(!me->query("renduermai")&&(me->query_skill(skill,1)>300)&&(random(mykar)+random(myint)+random(mycon))/3)>(20+random(10)))  
 	{
  		tell_object( me, HIC"你突然觉得体内的真气流动不同寻常，体内任督二脉\n"
        	"正在慢慢地融合......\n\n"NOR );
 		if( !random(10) )
		{
            		tell_object( me, HIW"终于，你体内的真气冲破十二重楼，完全汇交融合为一体，只觉得全身\n"
                	"内力充盈，你的任督二脉已经被打通了！\n"NOR );   
			me->add("int",2);
			me->add("per",2);
			me->add("con",2);
			me->add("dex",2);
			me->add("kar",2);
			me->add("str",2);
			me->set("renduermai",1);
   			me->set_temp("pending/exercise", 0);
			return 0;
		}
	}	
      	me->set_temp("pending/exercise", 0);
	message_vision( HIG"$N将散入经脉的真气收回丹田，深深吸了口气，站了起来。\n"NOR, me );
	if(me->query_temp("add_neili")) {
		me->delete_temp("add_neili");
     		tell_object(me,HIC"你感觉内力充盈，显然内功又有进境。\n"NOR );
                return 0;
	} else {
            	if ((int)me->query("neili") < (int)me->query("max_neili") * 2)
                return 0;
         	else {
               		if ((int)me->query("max_neili") > (int)me->query_skill("force") * 10) {
				if(!random(7)) {
 					tell_object(me, RED "你觉得体内的真气突然失去控制，蹿入全身各处经脉，\n"
     					"你浑身如针刺一般，痛苦之至。\n" NOR);
					tell_object(me,HIR "\n你因强行修炼内力，控制不住自己的内息，走火入魔了。\n"NOR );
					log_file("static/zouhuo",sprintf(" %s(%s) 走火入魔于%s,共失去%d点内力\n", me->query("name"),me->query("id"),ctime(time()),me->query("max_neili")*1/5));   
					me->unconcious();
					me->set_skill(skill,me->query_skill(skill,1)-1);
					me->set_skill("force",me->query_skill("force",1)-1);
 					me->set("max_neili",me->query("max_neili")*4/5);
					me->set("eff_neili",me->query("eff_neili")*4/5);
                         		me->set("neili", (int)me->query("max_neili"));
                          		return 0;
				}
				me->set("neili",me->query("max_neili"));
 				tell_object(me,"你只觉内息在体内不断膨胀，而不能再收入丹田，似乎内力修为已经达到了瓶颈。\n");
                        	me->set("neili", (int)me->query("max_neili"));
                        	return 0;
			}
		}
	}
	return 1;
}
int halt_exercise(object me)
{
	tell_object(me,HIC"你强行将内力纳入丹田,缓缓吐了口气,站了起来.\n"NOR);
   	if ( !random( 20) )
	{
		tell_object(me,HIY"你由于强行中断修炼，不禁一阵头昏目眩......\n"NOR);
		log_file("static/zouhuo",sprintf(" %s(%s) 走火入魔于%s,共失去%d点内力\n", me->query("name"),me->query("id"),ctime(time()),me->query("max_neili")*1/10));   
		me->set("max_neili",me->query("max_neili")*9/10);
		me->set("eff_neili",me->query("eff_neili")*9/10);
 		me->set("neili",me->query("eff_neili"));
         	me->set_temp("pending/exercise", 0);
        	return 1;
	}
	if ((int)me->query("neili") > (int)me->query("max_neili") * 2)
	me->set("neili", (int)me->query("max_neili") * 2);
	me->set_temp("pending/exercise", 0);
	return 1;
}

int help(object me)
{
        tell_object(me,@HELP
指令格式 : exercise|dazuo [<耗费「气」的量> 必须多于 10]

运气练功，控制体内的气在各经脉间流动，藉以训练人体肌肉骨骼的耐
力、爆发力，并且用内力的形式将能量储备下来。

HELP
        );
        return 1;
}
