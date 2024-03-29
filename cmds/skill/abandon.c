// abandon.c
// modified by vast for 自创武功
// modified by jpei for yes/no 05162008

inherit F_CLEAN_UP;
#include <ansi.h>
protected int delete_skill(string arg, object me, string skill);
int main(object me, string arg)
{
        int i, flag;
        string *skillname;
        mapping skills;

        if( !arg || arg=="" )
                return notify_fail("你要放弃哪一项技能？\n");

        if( !find_object(PLAYER_SKILL_D(arg)) && file_size(PLAYER_SKILL_D(arg)+".c") < 0)//判断是否是非自创武功
        if( !find_object(SKILL_D(arg)) && file_size(SKILL_D(arg) + ".c") < 0)//判断是否是自创武功
                return notify_fail("没有这项技能，请检查是否输入有误。\n");

        skills = me->query_skills();
        for (i = sizeof(skillname = keys(skills)) - 1; i >= 0; i--)
                if (skillname[i] == arg) flag = 1;
        if (flag != 1)
                return notify_fail("你并没有学过这项技能。\n");
 
        if (me->is_busy())   
                return notify_fail("你正忙着呢。\n"); 
        me->start_busy(1); 
        
        //暂时不判断skills level，存在自创功夫
        write("\n注意！你将要放弃"HIW+to_chinese(arg)+"("+arg+")"NOR" ，确定吗？[Y|N] >");
        input_to("delete_skill", me, arg); 
 
        return 1;
}

protected int delete_skill(string arg, object me, string skill)
{
        int i, flag;
        string basename, *skillname,*baseskillname;
        mapping skillmaxim, skills;

        if( arg[0]=='y' || arg[0]=='Y' ){ 
                //检查此功夫是否已经wbei
                flag = 0;
                skills = me->query_wprepare();
                if (sizeof(skills)>0){
                        baseskillname = keys(skills);
                        for (i = sizeof (skillname = values(skills))-1;i>=0;i--)
                                if ( (skillname[i] == skill)||(baseskillname[i] == skill) )  flag = 1;
                        if (flag){
                                for (i = sizeof (skillname = keys(skills))-1;i>=0;i--)
                                        me->prepare_wskill(baseskillname[i]);
                                write("你解除了当前的兵器功夫组合。\n");
                        }
                }
                //检查此功夫是否已经bei
                flag = 0;
                skills = me->query_skill_prepare();
                if (sizeof(skills)>0){
                        baseskillname = keys(skills);
                        for (i = sizeof (skillname = values(skills))-1;i>=0;i--)
                                if ( (skillname[i] == skill)||(baseskillname[i] == skill) )  flag = 1;
                        if (flag){
                                for (i = sizeof (skillname = keys(skills))-1;i>=0;i--)
                                        me->prepare_skill(baseskillname[i]);
                                write("你解除了当前的拳脚功夫组合。\n");
                        }
                }
                //检查此功夫是否已经enable
                skills = me->query_skill_map();
                if (sizeof(skills)>0){
                        baseskillname = keys(skills);
                        for (i = sizeof (skillname = values(skills))-1;i>=0;i--)
                                if ( (skillname[i] == skill)||(baseskillname[i] == skill) )  me->map_skill(baseskillname[i]);
                }
                me->reset_action();
        
                //判断是否是非自创武功
                if( !find_object(PLAYER_SKILL_D(skill)) && file_size(PLAYER_SKILL_D(skill)+".c") < 0){
                        if( !me->delete_skill(skill) )
                                return notify_fail("你并没有学过这项技能。\n"); 
                        write("\n你决定放弃继续学习"+ to_chinese(skill) +"("+skill+")。\n\n");
                }else{
                        if( !me->delete_skill(skill) )
                                return notify_fail("你并没有学过这项技能。\n");
                        skillmaxim = me->query("skillmaxim");
                        basename = "/cmds/skill/createskill.c"->get_header_skillbasename(skill + ".c");
                        map_delete(skillmaxim, basename);
                        log_file( "CREATESKILL", sprintf("%s(%s) 放弃学习 %s(%s) (%s)\n",
                            me->query("name"),
                            me->query("id"),
                            "/cmds/skill/createskill.c"->get_header_skillchname(arg + ".c"),
                            arg,
                            ctime(time()) ) );  
                        write("\n你决定放弃继续学习"+ to_chinese(skill) +"("+skill+")。\n\n");
                        CHINESE_D->remove_translate(arg);
                        seteuid(ROOT_UID);
                        rm(PLAYER_SKILL_D(skill)+".c");
                        seteuid(getuid());
                }
        }else{
                write("\n你决定保留"+ to_chinese(skill) +"("+skill+")。\n\n");
        }
        return 1;
}


int help()
{
        write(@TEXT
指令格式：abandon|fangqi <技能名称>

放弃一项你所学过的技能，注意这里所说的「放弃」是指将这项技能从你人物
的资料中删除，如果你以后还要练，必须从０开始重练，请务必考虑清楚。

这个指令使用的场合通常是用来删除一些「不小心」练出来的技能，由于每个
人有着不同的天赋，所修习的武功也不会相同。如果样样都学，到头来只会样
样不精。
TEXT
        );
        return 1;
}

