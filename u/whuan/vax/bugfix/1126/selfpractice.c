// practice.c

#include <ansi.h>
#include <msg.h>

inherit F_CLEAN_UP;
nosave string skillname;
nosave int skill_basic;
int check_valid_create(string skillname);
int main(object me, string arg)
{
        object where = environment(me);
        int skill;

        seteuid(getuid());
		if(!where->query("createskill_room"))
		return notify_fail("只有在侠客岛或自创帮派的闭关室中，清心寡欲，忘却俗事才能练习自创武功!\n");

        if (me->is_busy())
                return notify_fail("你现在正忙着呢。\n");

        if( me->is_fighting() )
                return notify_fail("你已经在战斗中了，学一点实战经验吧。\n");

        if( !arg ) return (__DIR__"enable")->main(me, arg);

        if( !stringp(skillname = me->query_skill_mapped(arg)) )
                return notify_fail("你只能练习用 enable 指定的特殊技能。\n");


        skill_basic = me->query_skill(arg, 1);
        skill = me->query_skill(skillname, 1);

        if( skill < 1 )
                return notify_fail("你好像还没有学过这项技能吧？最好先去请教别人。\n");
        if( skill_basic < 1 )
                return notify_fail("你对这方面的技能还是一窍不通，最好从先从基本学起。\n");

 //here add something.....
        if(check_valid_create(skillname)==0)
                return notify_fail("这不是你创建的功夫呀？\n");


        if( skill_basic + (int)me->query("int")/5 <= skill )
                return notify_fail("由于你的悟性的限制，只有提高基础功夫才能继续修练。\n");

        if( !PLAYER_SKILL_D(skillname)->valid_learn(me) ) return 0;

        message_vision("$N开始练习" + to_chinese(skillname) + "。。。。。。\n\n",me);
        me->set_temp("practicing");
        me->set_temp("practice");
        me->set_temp("pending/practice",60);
        me->start_busy("do_practice","halt_practice");
        return 1;

/*
        if( PLAYER_SKILL_D(skillname)->practice_skill(me) ) {

//original num is skill_basic/5 now to 4
//it should be adrusted properly

        me->improve_skill(skillname, random(to_int(skill_basic/30) + 1), skill_basic > skill? 0: 1, 1);
        write( HIY "你练习了一会儿" + to_chinese(skillname) + "，似乎有所进步！\n" NOR);
		me->start_busy(5);
                return 1;
        }
        else return 0;
*/
}
int check_valid_create(string skillname)
{
string file,*list,playername;
object me;

me=this_player();
file=read_file(PLAYER_SKILL_D(skillname+".c"));
if(!file)
     return 0;
list = explode(file, "\n");
playername=geteuid(me);

if(list[1]!="// "+playername)
      return 0;
if(list[0]!="// THIS IS PLAYER'S OWN SKILL (write by maxim@nju_fengxue)")
           return 0;

return 1;
}
int do_practice(object me)
{
        mixed action;
        object weapon, mu;
        int skill,i,point,k;
        string msg, str1, str2, str, arg, *limbs;
        arg=me->query_temp("practicing");
        point=me->query_temp("pending/practice");
        weapon=me->query_temp("weapon");
//        skill = me->query_skill(skillname,1);
        mu = present("mu ren", environment(me));
        limbs = mu->query("limbs");

        if( !PLAYER_SKILL_D(skillname)->valid_learn(me) ) return 0;
        msg=HIG+"$N正在习练"+to_chinese(skillname)+"的一些技巧......"+NOR;
        if(weapon)
        me->set_temp("practice", (: call_other, PLAYER_SKILL_D(skillname), "query_action", me, weapon :) );
        else
        me->set_temp("practice",(: call_other, PLAYER_SKILL_D(skillname), "query_action" :) );
        action = me->query_temp("practice");
        msg=action["action"];
        if(!stringp(msg))  msg="$N正在认真地习练"+to_chinese(skillname)+"的一些技巧......";
        msg=HIG+""+msg+"\n"+NOR;
        if(weapon) msg = replace_string(msg, "$w", weapon->query("name"));
        msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
        if (me->query_skill(skillname,1)> 1)
        message_vision(msg, me, mu);

        message_vision(HIR + "$N突然领悟了"+to_chinese(skillname)+"的一些技巧！\n"+NOR,me);
        me->add("jing", - 20);
        me->add("neili", - 20);
        me->improve_skill(skillname, random(to_int(skill_basic/30) + 1), skill_basic > skill? 0: 1, 1);

        me->add_temp("pending/practice",-1);
        if(me->query("neili") < 200
        ||me->query("jing") < 100
        ||me->query_temp("pending/practice")<10)
        {
        msg = sprintf(HIG"\n$N松了一口气,暂停了练习%s.\n"NOR, to_chinese(skillname));
        message_vision(msg,me);
        me->delete_temp("practicing");
        me->delete_temp("practice");
        me->delete_temp("pending/practice");
        return 0;
        }
        return 1;
}
int halt_practice(object me)
{
        me->delete_temp("practicing");
        me->delete_temp("pending/practice");
        me->delete_temp("skillname");
        me->delete_temp("practice");
        if ((int)me->query("neili")<100)
        {
        me->set("neili",0);
        message_vision("$N猛地一收招，突然觉得无法控制内力的流动，一下晕了过去。\n", me);
        me->unconcious();
        }
        else
        me->add("neili",-100);
        message_vision("$N猛地一收招，停止了出招。\n", me);
        return 1;
}
int help(object me)
{
        write(@TEXT
指令格式：selfpractice <技能种类>

这个指令让你练习某个自己创建的技能，这个技能必须是经过 enable 的专业技能。
勤加练习是使你的所学「青出于蓝胜于蓝」的唯一途径，当然，在这之前你必须从
实际运用中获得足够的经验以提升你的基本技能。

例如：selfpractice unarmed, selfpractice sword......

其他相关指令 : createskill,selfpractice

TEXT
        );
        return 1;
}

