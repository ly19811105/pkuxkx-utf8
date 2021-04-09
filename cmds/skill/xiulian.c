// xiulian.c
// 修炼特殊内功

#include <ansi.h>
#include <skill.h>

inherit F_CLEAN_UP;
/*已经整合到/feature/kungfu.c里面，请修改该文件对应变量
mapping family_force=       //门派和内功映射关系，只能修炼本门内功或者公共武学的内功，无门派的可以修炼百姓内功
([
  "武当派":({"taiji-shengong"}),
  "少林派":({"hunyuan-yiqi","yijin-jing"}),
  "峨嵋派":({"linji-zhuang"}),
  "丐帮":({"huntian-qigong"}),
  "华山派":({"huashan-neigong","zixia-shengong","hunyuan-gong"}),
  "雪山派":({"xueshan-neigong"}),
  "全真派":({"xiantian-gong"}),
  "天地会":({"cangming-gong"}),
  "天龙寺":({"beiming-shengong","kurong-shengong","shanjue"}),
  "白驼山":({"hamagong"}),
  "大轮寺":({"longxiang-boruo"}),
  "日月神教":({"riyue-shengong","kuihua-shengong"}),
  "神龙教":({"shenlong-xinfa"}),
  "星宿派":({"huagong-dafa","beiming-shengong","xiaowuxiang-gong"}),
  "朝廷":({"bixue-xinfa"}),
  "古墓派":({"yunu-xinfa"}),
  "灵鹫宫":({"bahuang-gong","beiming-shengong","xiaowuxiang-gong"}),
  "明教":({"guangming-shenghuogong"}),
  "姑苏慕容":({"shenyuan-gong"}),
  "桃花岛":({"bihai-shengong"}),
  "百姓":({"taiyi-shengong"}),
  "侠客岛":({"xiake-shengong"}),
  "公共武学":({"jiuyin-shengong","chuforce","xixing-dafa"}) ]);
*/
int main(object me, string arg)
{
    string skill;
    int my_skill;
    int xl_time, fpot, outpar;
    
    seteuid(getuid());
    if(!stringp(arg))
           {
            return notify_fail("指令参数错误！正确的格式是：xiulian <技能名称>\n");
           } 
           
    if(me->is_busy()) return notify_fail("你现在正忙着呢。\n");
        
    if(me->is_fighting()) return notify_fail("战斗中不能练内功，会走火入魔。\n");
        
    if(me->query("lingjiu/last_xiulian_time"))
        return notify_fail("你现在正在恢复武功，没有精力研究武功。\n");

    skill=(string)arg;
    
        if( !me->query_skill(skill, 1) )
                return notify_fail("你不会这种技能。\n");

    //判断是否是内功，否则不能修炼
    if( !find_object(SKILL_D(skill)) && file_size(SKILL_D(skill)+".c") < 0)//判断是否是自创武功
            {
                if(!PLAYER_SKILL_D(skill)->valid_enable("force") )
                   return notify_fail("你只能修炼内功！\n");
            }
          else
            {
                   if(!SKILL_D(skill)->valid_enable("force") )
                   return notify_fail("你只能修炼内功！\n");
            }
               
    if(!SKILL_D(skill)->valid_learn(me)) 
      return 0;
      
//门派检查，非本门非公共武学非出师前功夫不能修炼    
    outpar=F_KUNGFU->valid_xiulian(me, skill);
    if ( outpar<0 )
      return 0;
        
    my_skill = me->query_skill(skill,1);
    if(my_skill < 100) 
        return notify_fail("你的"+to_chinese(skill)+"必须高于 100 级才能修炼。\n" );

    if( my_skill >= me->query_skill_limit() )//破坏公式美感，但是至少不会溢出了。 byZine
        return notify_fail("由于缺乏实战经验，你无法领会更高深的武功。\n" );
    
    if((int)me->query("learned_points") > (int)me->query("potential") - my_skill*2)
        return notify_fail("你的潜能必须大于 "+my_skill*2+" 才能修炼。\n");
    fpot=F_KUNGFU->xiulian_pot(my_skill, outpar*30);
// 增加一道检查，防止修炼实际消耗的潜能过多，导致修炼结束之后hp显示的潜能变成负值。by lordstar@2017/10/11
    if((int)me->query("learned_points") > (int)me->query("potential") - fpot)
        return notify_fail("你的潜能必须大于 "+fpot+" 才能修炼。\n");
    me->add( "learned_points", fpot );
    
    xl_time=to_int(30 - (int)me->query("con")/2);
    
    if (xl_time>30 ) xl_time=30;
    if (xl_time<10 ) xl_time=10;
        
    me->set_temp("pending/xiulian", xl_time);
    
    //每次消耗潜能数等于skill级别，高等级时修炼不至于太难
    message_vision(HIM"\n$N盘膝坐下，运起丹田之气，开始修炼"+to_chinese(skill)+"......\n\n"NOR, me);
    me->start_busy("do_xiulian","halt_xiulian");
    me->set_temp("xiulian_skill",skill);
    return 1;
}

int do_xiulian(object me)
{
    string skill;
    int my_skill;
    int my_con, factor;
    int imp_skill;
    object *all;
    my_con=(int)me->query("con")/2+(int)me->query("int")/2+5;
    if (my_con >=40) my_con=40;
    if (my_con <=10) my_con=10;
    //防止中途换内功
    if(!(skill = me->query_temp("xiulian_skill"))) return 0;
    my_skill = me->query_skill(skill,1);
    
    if ( !random(to_int(my_con/3))) 
    {
        tell_object( me, 
        MAG"......你摧动真气沿体内经脉流动，在百会、人中、神阕、丹田、会阴、命门、玉枕等要穴\n"+
        "      间不住流转，然后散之于四肢体骸......\n\n"NOR);
    }
    else if (!random(to_int(my_con/2)))
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
        if (present("shi bei",environment(me))&&present("shi bei",environment(me))->query("is_shibei")&&present("shi bei",environment(me))->query("is_bonus_xiulian"))//大明堪舆
        {
            if (!me->query("mingpin")&&!me->query("ming/tj/pin")&&present("shi bei",environment(me))->query("pin")>=1)
            {
                all=all_inventory(environment(me));
        all = filter_array(all, (: userp :));
                if (sizeof(all)>5)//享受福利的人不可太多
                {
                    tell_object(me,WHT+"人多吵杂，你实在无法静下心来默念石碑上的经文！\n"+NOR);
          factor=100;
                }
                else
                {
                    tell_object(me,HIC+"你默念石碑上的经文，对于本身的修为有着极大的助益！\n"+NOR);
                    factor=110-present("shi bei",environment(me))->query("pin");
                }
            }
        }
        else if (environment(me)->get_xiulian_bonus(me))
          factor=environment(me)->get_xiulian_bonus(me);
        else
          factor=100;
        
        if (wizardp(me))
          tell_object(me,"修炼加成效果:"+factor+"。\n");
        
        if (stringp(environment(me)->get_xiulian_bonus_desc(me)))
        {
          message_vision(environment(me)->get_xiulian_bonus_desc(me),me);
        }
        
        F_KUNGFU->xiulian_improve(me, my_con, factor);
        me->delete_temp("pending/xiulian");
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
    if ( !random(20) )
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


