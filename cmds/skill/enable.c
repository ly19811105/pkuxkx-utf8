 //修正没有基本技能也能enable的bug，同时去掉enable all
// enable.c

#include <ansi.h>

inherit F_CLEAN_UP;

mapping valid_types = ([

        "array":        "阵法",
        "dodge":        "轻功",
        "force":        "内功",
        "iron-cloth":   "硬功",
        "parry":        "招架",
//  兵器功夫
        "axe":          "斧法",
        "blade":        "刀法",
        "club" :        "棍法",
        "dagger":       "匕法",
        "fork":         "叉法",
        "halberd":      "戟法",
        "hammer":       "锤法",
        "pestle":       "杵法",
        "spear":        "枪法",
        "staff":        "杖法",
        "sword":        "剑法",
        "throwing":     "暗器",
        "whip":         "鞭法",
//  空手功夫
        "unarmed":      "拳脚",
        "finger":       "指法",
        "hand":         "手法",
        "cuff":         "拳法",
        "claw":         "爪法",
        "strike":       "掌法",
        "leg":          "腿法",
]);

int main(object me, string arg)
{
        mapping map, skills, wbei;
        string *skill, *weapon, *wtype, ski, map_to, old_map;
        int i, modify, tmp;

        seteuid(getuid());

        skill = sort_array(keys(valid_types), (: strcmp :));
        skill = sort_array(skill, -1);
        if (arg && wizardp(me)) {
                object ob = present(arg, environment(me));

                if (!ob) ob = find_living(arg);
                if (!ob) ob = LOGIN_D->find_body(arg);
                if (ob) {
                        me = ob;
                        arg = 0;
                }
        }

        if( !arg ) {
                map = me->query_skill_map();
                if( !mapp(map) || sizeof(map)==0 )
                        return notify_fail("你现在没有使用任何特殊技能。\n");

                write("以下是你目前使用中的特殊技能。\n");
                write(sprintf("\n  \t\t\t\t"HIR"基本功夫\n"NOR));
                if ( me->query_skill("force")>0 )
                {
                	modify = me->query_temp("apply/force");
                	write(sprintf("  %-44s： %-20s  有效等级：%s%3d\n" NOR, 
                                HIY"内功 (force)"NOR, 
                                undefinedp(map["force"]) ? "无" : to_chinese(map["force"]),
                                (modify==0 ? "" : (modify>0 ? HIC : HIR)),
                                me->query_skill("force")));
                  skill=skill-({"force"});
                }
                
                if ( me->query_skill("dodge")>0 )
                {
                	modify = me->query_temp("apply/dodge");
                	write(sprintf("  %-44s： %-20s  有效等级：%s%3d\n" NOR, 
                                HIC"躲闪 (dodge)"NOR, 
                                undefinedp(map["dodge"]) ? "无" : to_chinese(map["dodge"]),
                                (modify==0 ? "" : (modify>0 ? HIC : HIR)),
                                me->query_skill("dodge")));
                  skill=skill-({"dodge"});
                }
                
                if ( me->query_skill("parry")>0 )
                {
                	modify = me->query_temp("apply/parry");
                	write(sprintf("  %-44s： %-20s  有效等级：%s%3d\n" NOR, 
                                HIM"招架 (parry)"NOR, 
                                undefinedp(map["parry"]) ? "无" : to_chinese(map["parry"]),
                                (modify==0 ? "" : (modify>0 ? HIC : HIR)),
                                me->query_skill("parry")));
                  skill=skill-({"parry"});
                }
                
                if ( me->query("recent_weapon") &&
                	   arrayp(me->query("recent_weapon")) )
                {
                	write(sprintf("\n  \t\t\t\t"HIB"常用兵器\n"NOR));
               	  weapon=me->query("recent_weapon");
                	if ( sizeof(wbei=me->query_wprepare() )==2 )
                	{
                		wtype=keys(wbei);
                		if ( member_array( wtype[0], weapon ) <0 )
                			weapon=weapon+({wtype[0]});
                		if ( member_array( wtype[1], weapon ) <0 )
                			weapon=weapon+({wtype[1]});
                	}
                	for ( i=0;i<sizeof(weapon);i++)
                	{
                		if ( !me->query_skill(weapon[i]) )
                		{
                			skill=skill-({weapon[i]});
                			continue;
                		}
                		
                		if( undefinedp(valid_types[weapon[i]]) ) 
                		{
                      map_delete(map, weapon[i]);
                      skill=skill-({weapon[i]});
                      continue;
                    }
                    modify = me->query_temp("apply/" + weapon[i]);
                    if ( sizeof(wbei)==2 && wbei[weapon[i]] )
                    	write(sprintf("  %-28s： %-36s  有效等级：%s%3d\n" NOR, 
                            valid_types[weapon[i]] + " (" + weapon[i] + ")",
                            undefinedp(map[weapon[i]]) ? "无" : to_chinese(map[weapon[i]])+HIG"[互备]"NOR,
                            (modify==0 ? "" : (modify>0 ? HIC : HIR)),
                            me->query_skill(weapon[i])));
                    else
                      write(sprintf("  %-28s： %-20s  有效等级：%s%3d\n" NOR, 
                            valid_types[weapon[i]] + " (" + weapon[i] + ")",
                            undefinedp(map[weapon[i]]) ? "无" : to_chinese(map[weapon[i]]),
                            (modify==0 ? "" : (modify>0 ? HIC : HIR)),
                            me->query_skill(weapon[i])));
                    skill=skill-({weapon[i]});
                  }
                }
                
                if ( me->query_skill_prepare() &&
                	   mapp(me->query_skill_prepare()) &&
                	   sizeof(me->query_skill_prepare())>0 )
                {
                	write(sprintf("\n  \t\t\t\t"YEL"常用拳脚\n"NOR));
                	weapon=keys(me->query_skill_prepare());
                	for ( i=0;i<sizeof(weapon);i++)
                	{
                		if ( !me->query_skill(weapon[i]) )
                		{
                			skill=skill-({weapon[i]});
                			continue;
                		}
                		
                		if( undefinedp(valid_types[weapon[i]]) ) 
                		{
                      map_delete(map, weapon[i]);
                      skill=skill-({weapon[i]});
                      continue;
                    }
                    
                    modify = me->query_temp("apply/" + weapon[i]);
                    if ( sizeof(weapon) > 1 )
                    	write(sprintf("  %-28s： %-36s  有效等级：%s%3d\n" NOR, 
                            valid_types[weapon[i]] + " (" + weapon[i] + ")",
                            undefinedp(map[weapon[i]]) ? "无" : to_chinese(map[weapon[i]])+HIG"[互备]"NOR,
                            (modify==0 ? "" : (modify>0 ? HIC : HIR)),
                            me->query_skill(weapon[i])));
                    else
                      write(sprintf("  %-28s： %-20s  有效等级：%s%3d\n" NOR, 
                            valid_types[weapon[i]] + " (" + weapon[i] + ")",
                            undefinedp(map[weapon[i]]) ? "无" : to_chinese(map[weapon[i]]),
                            (modify==0 ? "" : (modify>0 ? HIC : HIR)),
                            me->query_skill(weapon[i])));
                    skill=skill-({weapon[i]});
                  }
                }
                
                if ( sizeof(skill) > 0 )
                {
                  write(sprintf("\n  \t\t\t\t"HIW"其他功夫\n"NOR));
                	for ( i=0;i<sizeof(skill);i++)
                	{
                        if( undefinedp(valid_types[skill[i]]) ) {
                                map_delete(map, skill[i]);
                                continue;
                        }
                        if( !me->query_skill(skill[i]) ) continue;
                        modify = me->query_temp("apply/" + skill[i]);
                        write(sprintf("  %-28s： %-20s  有效等级：%s%3d\n" NOR, 
                                valid_types[skill[i]] + " (" + skill[i] + ")",
                                undefinedp(map[skill[i]]) ? "无" : to_chinese(map[skill[i]]),
                                (modify==0 ? "" : (modify>0 ? HIC : HIR)),
                                me->query_skill(skill[i])));
                  }
                }
                return 1;
        }

        if( arg=="?" ) {
                write("以下是可以使用特殊技能的种类：\n");
                skill = sort_array(keys(valid_types), (: strcmp :) );
                for(i=0; i<sizeof(skill); i++) {
                        write(sprintf("  %s (%s)\n", valid_types[skill[i]], skill[i] ));
                }
                return 1;
        }

//        if((me->query_temp("no_enable") || me->is_busy() || me->is_perform() || me->is_exert())&&arg)

        if(me->query_temp("no_enable") &&arg)
                return notify_fail("你现在不能激发特殊技能。\n");
        if (me->query_temp("pending/xiulian"))
                return notify_fail("你正在修炼武功，不能更换技能。\n");
		if (me->query_temp("pending/exercise"))
                return notify_fail("你正在修炼内力，不能更换技能。\n");
 /*
        if (arg == "all") {
                skills = me->query_skills();
                if (!skills) return notify_fail("你目前并没有学会任何技能。\n");
                i = sizeof(skill);
                while (i--) {
                        ski = skill[i];
                        modify = sizeof(skills);
                        tmp = 0;
                        while (modify--) {
                                if (SKILL_D(keys(skills)[modify])->valid_enable(ski)
                                && values(skills)[modify] > tmp) {
                                        map_to = keys(skills)[modify];
                                        tmp = values(skills)[modify];
                                }
                        }
                        if (tmp) {
                                me->force_me("enable " + ski + " " + map_to);
                        }
                }
                if (me->query_skill_mapped("force")) {
                        if ((tmp = (me->query_skill("force") / 2)) > 200)
                                tmp = 200;
                        me->force_me("enforce " + tmp);
                }
                write("技能准备完毕。\n");
                return 1;
        }

        if (arg == "none") {
                skills = me->query_skill_map();
                if (!skills) return notify_fail("你目前并没有激发任何技能。\n");
                skill = keys(skills);
                i = sizeof(skill);
                while (i--) {
                        if (skill[i] == "force") continue;
                        me->map_skill(skill[i]);
                        write("你决定使用基本的" + valid_types[skill[i]] + "。\n");
                }
                me->force_me("enforce none");
                me->force_me("prepare none");
                return 1;
        }
*/
        if( sscanf(arg, "%s %s", ski, map_to)!=2 )
                return notify_fail("指令格式：enable|jifa [<技能种类> <技能名称>|none]\n");

        if(me->query_skill_prepared(ski)
           ||me->query_wprepared(ski))
                return notify_fail("备了的技能不能被换掉。\n"); 

        if( undefinedp(valid_types[ski]) )
                return notify_fail("没有这个技能种类，用 enable ? 可以查看有哪些种类。\n");

        if ( me->query_skill_mapped(ski)==map_to )
          return notify_fail("你已经激发了该技能，不需要重新激发了。\n");

        if ( ski=="force" &&
             time()-me->query("enable_cd")<=(70-me->query("con")) )
                return notify_fail("当前内功正在运行中，现在切换容易走火入魔，还请稍等再切换内功吧。\n");

        if ( ski=="force" && me->query_temp("kuihua.guiming"))
                return notify_fail("当前内功正在特殊运行中，现在切换容易走火入魔，还请稍等再切换内功吧。\n");

		old_map = me->query_skill_mapped(ski);

        if( map_to=="none" ) {
// 增加一个 disable_skill() 函数入口，用于某技能被取消激发时执行操作。by lordstar 20171030
				if (old_map && find_object(SKILL_D(old_map)))
					SKILL_D(old_map)->disable_skill(me);

                me->map_skill(ski);
                me->reset_action();
                write("你决定使用基本的" + valid_types[ski] + "。\n");
                if ( ski=="force" )
                {
                  me->add_busy(random(3)+1);
                  me->set("enable_cd", time());
                  write("放弃使用内功将会影响你的最大内力和最大精力。\n");
                }
                return 1;
        } else if( map_to==ski ) {
                write("「" + to_chinese(ski) + "」是所有" + valid_types[ski] + "的基础，不需要 enable。\n");
                return 1;
        }

                if( !me->query_skill(map_to, 1) || !me->query_skill(ski, 1) )
                return notify_fail("你不会这种技能。\n");

        if( !find_object(SKILL_D(map_to)) && file_size(SKILL_D(map_to)+".c") < 0)//判断是否是自创武功
        {
                if(!PLAYER_SKILL_D(map_to)->valid_enable(ski) )
                return notify_fail("这个技能不能当成这种用途。\n");
        }
        else
        {
                if(!SKILL_D(map_to)->valid_enable(ski) )
                return notify_fail("这个技能不能当成这种用途。\n");
        }

        if (me->query_skill_prepared(ski) && me->query_skill_prepared(ski) != map_to)
                return notify_fail(to_chinese(map_to) + "与你现有的组合不符。\n");
        
        write("你决定用" + to_chinese(map_to) +"作为你的" + valid_types[ski] + "。\n");

// 增加一个 disable_skill() 函数入口，用于某技能被取消激发时执行操作。by lordstar 20171030
		if (old_map && find_object(SKILL_D(old_map)))
			SKILL_D(old_map)->disable_skill(me);
        if (ski=="force" && map_to != me->query_skill_mapped(ski))
        {
                me->add_busy(random(3)+1);
                me->set("enable_cd", time());
                write("切换新内功将会影响你的最大内力和最大精力。\n");
        }

        me->map_skill(ski, map_to);
        me->reset_action();
        
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : enable|jifa [<技能种类> <技能名称> | none]
           enable|jifa ?

这个指令让你指定所要用的技能，需指明技能种类和技能名称。如果不加参
数则会显示出技能种类及你目前所使用的技能名称，如果加一个？会列出所
有能使用特殊技能的技能种类。
 
HELP
        );
        return 1;
}
