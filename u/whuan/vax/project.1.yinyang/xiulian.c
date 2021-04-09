// xiulian.c
// 修炼特殊内功

#include <ansi.h>
#include <skill.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    string skill, my_yinyang;
    int i, max_force, max_skill_ptr;
    string *skills;
    int my_skill;

    seteuid(getuid());
    if(me->is_busy()) return notify_fail("你现在正忙着呢。\n");
    if(me->is_fighting()) return notify_fail("战斗中不能练内功，会走火入魔。\n");
    if(me->query("lingjiu/last_xiulian_time"))
        return notify_fail("你现在正在恢复武功，没有精力研究武功。\n");
    if(!(skill = me->query_skill_mapped("force")))
        return notify_fail("你必须先用 enable 选择你要用的内功心法。\n");
    if(!SKILL_D(skill)->valid_learn(me)) return 0;
    // dewolf :: yinyang
    if( find_object(SKILL_D(skill)) && file_size(SKILL_D(skill)+".c") > 0)//判断是否是非自创武功
    {
      if( !YINYANG_D->skill_isvalid(me, skill) )
	  return notify_fail("以你的内功和天资无法支持这项 "+SKILL_D(skill)->query_yinyang()+" 属性的技能。\n");
     // deny multi-force
      if (SKILL_D(skill)->valid_enable("force") && ((int)me->query_skill(skill,1)) >= 100)
      {
        my_yinyang = "没有";
	 max_force = -1;
	 max_skill_ptr = -1;
	 // max special_force
	 skills = me->query_skills();
	 for (i=0;i<sizeof(skills);i++)
	 {
	   if (find_object(SKILL_D(skills[i]))
	       && file_size(SKILL_D(skills[i])+".c") > 0
	       && SKILL_D(skills[i])->query_yinyang() != "没有"
              && ((int)me->query_skill(skills[i],1)) >= 100
              && SKILL_D(skills[i])->valid_enable("force") 
              && ((int)me->query_skill(skills[i],1)) > max_force )
          {
            my_yinyang = SKILL_D(skills[i])->query_yinyang();
            max_force = (int)me->query_skill(skills[i],1);
	     max_skill_ptr = i;
          }
        }
        if (my_yinyang != "没有" && my_yinyang != SKILL_D(skill)->query_yinyang() && max_skill_ptr >= 0)
        {
          return notify_fail("你的体质已经适应了"+skills[max_skill_ptr]+"的经脉运行，再强行修炼"
		+SKILL_D(skill)->query_yinyang()+"属性的内功会走火入魔。\n");
        }
      }
    }
    my_skill = me->query_skill(skill,1);
    if(my_skill < 200)
        return notify_fail("你的"+to_chinese(skill)+"必须高于 200 级才能修炼。\n" );

    if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") )
        return notify_fail("由于缺乏实战经验，你无法领会更高深的武功。\n" );
    
    if((int)me->query("learned_points") > (int)me->query("potential") - my_skill/10)
        return notify_fail("你的潜能必须大于 "+my_skill/10+" 才能修炼。\n");
    
    me->set_temp("pending/xiulian", 30);
    //每次消耗潜能数等于skill级别，高等级时修炼不至于太难
    me->add("learned_points", my_skill/10);
    message_vision(HIM"\n$N盘膝坐下，运起丹田之气，开始修炼"+to_chinese(skill)+"......\n\n"NOR, me);
    me->start_busy("do_xiulian","halt_xiulian");
    return 1;
}

int do_xiulian(object me)
{
    string skill;
    int my_skill;
    //防止中途换内功
    if(!(skill = me->query_skill_mapped("force"))) return 0;
    my_skill = me->query_skill(skill,1);
    
    if ( !random(7)) 
    {
        tell_object( me, 
        MAG"......你摧动真气沿体内经脉流动，在百会、人中、神阕、丹田、会阴、命门、玉枕等要穴\n"+
        "      间不住流转，然后散之于四肢体骸......\n\n"NOR);
    }
    else if (!random(11))
        tell_object(me,HIW"......你心中默念内功心法，缓缓催动体内气息运行周天。\n"
		"      只觉体内一股热气直透上来，你进入了一种玄妙的境界......\n\n"NOR);    
	if(me->is_fighting() && !random(20) )
    {
		tell_object(me, HIR "由于你在战斗中强行修炼内功，你走火入魔了！\n" NOR );
        log_file("static/xiulian_zouhuo",
        sprintf("%s(%s) 修炼内功走火于%s,%s等级掉一级。\n", 
        me->query("name"),me->query("id"),ctime(time()), to_chinese(skill) ));
        me->set_skill(skill, my_skill-1);
        return 0;
    }
        
    if (me->query_temp("pending/xiulian") < 2)
    {
        // skill 点潜能换(skill*0.75 + 后天根骨*5)点
        me->improve_skill(skill, me->query_con()*5 + random(my_skill * 3/2));
        message_vision( HIG"$N从玄幻之境回过神来，顿觉内功修为增进不小。\n"NOR, me );
        return 0;
    }
    me->add_temp("pending/xiulian", -1 );
    return 1;
}

int halt_xiulian(object me)
{
    string skill;
    if(!(skill = me->query_skill_mapped("force"))) return 0;
    
    me->delete_temp("pending/xiulian");
    tell_object(me,HIR"你强行将内力纳入丹田,缓缓吐了口气,站了起来.\n"NOR);
    if ( !random(30) )
    {
        tell_object(me,HIY"你由于强行中断修炼，不禁一阵头昏目眩......你走火了！\n"NOR);
        log_file("static/xiulian_zouhuo",
        sprintf("%s(%s) 修炼内功走火于%s,%s等级掉一级。\n", 
        me->query("name"),me->query("id"),ctime(time()), to_chinese(skill) ));
        me->set_skill(skill,me->query_skill(skill,1)-1);
    }
    return 1;
}

int help(object me)
{
    tell_object(me,@HELP
    修炼内功是后期提高特殊内功的唯一途径，修炼有可能走火，
所以最好在安全的地方修炼以避免走火。
HELP
    );
    return 1;
}
