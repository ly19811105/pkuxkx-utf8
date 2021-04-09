// xiulian.c
// 修炼特殊内功

#include <ansi.h>
#include <skill.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    string skill;
    int my_skill;

    seteuid(getuid());
    if(me->is_busy()) return notify_fail("你现在正忙着呢。\n");
    if(me->is_fighting()) return notify_fail("战斗中不能练内功，会走火入魔。\n");
    if(me->query("lingjiu/last_xiulian_time"))
        return notify_fail("你现在正在恢复武功，没有精力研究武功。\n");
    if(!(skill = me->query_skill_mapped("force")))
        return notify_fail("你必须先用 enable 选择你要用的内功心法。\n");
    if(!SKILL_D(skill)->valid_learn(me)) return 0;
    
if ((string)me->query("family/family_name")!="少林派" && (string)me->query_skill_mapped("force")=="yijin-jing")
{
        return notify_fail("你不是少林高僧，无法修炼易筋经。\n");
}
if ((string)me->query("family/family_name")!="侠客岛" && (string)me->query_skill_mapped("force")=="xiake-shengong")
{
        return notify_fail("你私自修炼侠客神功，不怕被侠客岛发现么？\n");
}
    my_skill = me->query_skill(skill,1);
    if(my_skill < 100) 
        return notify_fail("你的"+to_chinese(skill)+"必须高于 100 级才能修炼。\n" );

    if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") )
        return notify_fail("由于缺乏实战经验，你无法领会更高深的武功。\n" );
    
if ((string)me->query_skill_mapped("force")=="yijin-jing")
{
    if((int)me->query("learned_points") > (int)me->query("potential") - my_skill*8)
        return notify_fail("易筋神功乃武林至尊，你的潜能必须大于 "+my_skill*8+" 才能修炼。\n");
    me->add("learned_points", my_skill*8);
}
else
{
    if((int)me->query("learned_points") > (int)me->query("potential") - my_skill*2)
        return notify_fail("你的潜能必须大于 "+my_skill*2+" 才能修炼。\n");
    me->add("learned_points", my_skill*2);
}
    me->set_temp("pending/xiulian", 30);
    
    //每次消耗潜能数等于skill级别，高等级时修炼不至于太难
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
        // skill 点潜能换(skill * 0.75 + 先天根骨)点
        // -advent注：原来这个设置太不合理，后期几百点潜能才能提高很少的点数，而且要花很长的时间
//        me->improve_skill(skill, me->query("con") + random(my_skill * 3/2));
        me->improve_skill(skill, my_skill * 2 * (3+random(pow(me->query("con")*1.0,0.5))));
        // 改成：skill电潜能换skill*(3+random(con^0.5))点
        // 按照平均根古为25算，潜能的效率大约为skill*5
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
