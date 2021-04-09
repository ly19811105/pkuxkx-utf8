// practice.c

#include <ansi.h>

inherit F_CLEAN_UP;

int check_valid_create(string skillname);
int main(object me, string arg)
{
        object where = environment(me);
        string skillname;
        int skill, skill_basic;

        seteuid(getuid());
		if(!where->query("createskill_room")) 
		return notify_fail("你只能在侠客岛的闭关室练习自创武功!\n");

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
           

        if( skill_basic < skill )
                return notify_fail("你的基本功火候未到，必须先打好基础才能继续提高。\n");

        if( !PLAYER_SKILL_D(skillname)->valid_learn(me) ) return 0;
        
        if( PLAYER_SKILL_D(skillname)->practice_skill(me) ) {

//original num is skill_basic/5 now to 4
//it should be adrusted properly

        me->improve_skill(skillname, random(to_int(skill_basic/30) + 1), skill_basic > skill? 0: 1, 1);
        write( HIY "你练习了一会儿" + to_chinese(skillname) + "，似乎有所进步！\n" NOR);
		me->start_busy(5);
                return 1;
        }
        else return 0;
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

int help(object me)
{
        write(@TEXT
指令格式：selfpractice <技能种类>

这个指令让你练习某个自己创建的技能，这个技能必须是经过 enable 的专业技能。
勤加练习是使你的所学「青出于蓝胜于蓝」的唯一途径，当然，在这之前你必须从
实际运用中获得足够的经验以提升你的基本技能。

例如：selfpractice unarmed, selfpractice sword......

TEXT
        );
        return 1;
}

