// selfthinking.c

#include <ansi.h>
#include <skill.h>

inherit F_CLEAN_UP;

int check_valid_create(string skillname);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
string skill_name;
string skillname;
int skill, skill_basic;
object ob;
int  gin_cost;
object env=environment(me);

	 if(!env->query("createskill_room")) 
	 return notify_fail("你只能在侠客岛的闭关室练习自创武功!\n");

        if (me->is_busy())
                return notify_fail("你现在正忙着呢。\n");

        if( me->is_fighting() )
                return notify_fail("临阵磨枪？来不及啦。\n");

 if( !arg ) return (__DIR__"enable")->main(me, arg);

 if( !stringp(skillname = me->query_skill_mapped(arg)) )
 return notify_fail("你只能练习用 enable 指定的特殊技能。\n");

      //here add something.....
        if(check_valid_create(skillname)==0)
                return notify_fail("这不是你创建的功夫呀？\n");

        skill_basic = me->query_skill(arg, 1);
        skill = me->query_skill(skillname, 1);

        if( skill < 1 )
                return notify_fail("你好像还没有学过这项技能吧？请先创出这种武功。\n");
        if( skill_basic < 1 )
                return notify_fail("你对这方面的技能还是一窍不通，最好从先从基本学起。\n");
        if( skill_basic < skill )
             return notify_fail("你的基本功火候未到，必须先打好基础才能继续提高。\n");

        if( !PLAYER_SKILL_D(skillname)->valid_learn(me) ) return 0;

        gin_cost = 800 / (int)me->query("int");
/*
        if( !skill ) {
                gin_cost *= 2;
                me->set_skill(skillname,0);
        }
*/
        if( (int)me->query("learned_points") >= (int)me->query("potential") )
                return notify_fail("你的潜能已经发挥到极限了，没有办法再成长了。\n");

        printf("你开始用心思考有关「%s」的疑问。\n", 
                to_chinese(skillname));


        if( (int)me->query("jing") > gin_cost ) 
		{
                if( (string)PLAYER_SKILL_D(skillname)->type()=="martial"
//changed by maxim 
//to let player have enough potential
/////
//I think should change the npc's degree
// to let npc lower.because player can't have enough degree..as their exp.. 
//can have more skillpower also skills low then ever?
//so player need not use voidsense ?

//but I really din't change it...
//it should be discuss...
//sigh

                &&      skill * skill * skill / 10 > (int)me->query("combat_exp") ) 
				{
                        printf("也许是缺乏实战经验，你的「%s」无法继续提高。\n", to_chinese(skillname));
                } 
				else {
                        if(skill_name = PLAYER_SKILL_D(skillname)->query_skill_name(skill))
                                printf("你经过用心思考，对「%s」这一招似乎有些心得。\n", skill_name);
                        else
                                printf("你经过用心思考，似乎有些心得。\n");

                        me->add("learned_points", 1);

				        me->improve_skill(skillname,random(to_int(skill_basic/20) + 1), 0, 1);

					 }
        } 
		else {
                gin_cost = me->query("jing");
                write("你今天太累了，结果什么也没有学到。\n");
        }

        me->receive_damage("jing", gin_cost );
		me->start_busy(5);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : selfthinking <技能>

这个指令让你思考某个自己创建的技能，这个技能必须是经过 enable 的专业技能。
勤加练习是使你的所学「青出于蓝胜于蓝」的唯一途径，当然，在这之前你必须从
实际运用中获得足够的经验以提升你的基本技能。这个命令比selfpractice成长速
度快，但是要消耗潜能。

例如：selfthinking unarmed, selfthinking sword......

其他相关指令 : createskill,selfpractice
 
HELP
        );
        return 1;
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


