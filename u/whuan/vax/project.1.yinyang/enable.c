// enable.c

#include <ansi.h>

inherit F_CLEAN_UP;

mapping valid_types = ([
	"array":        "阵    法",
	"dodge":        "轻    功",
	"force":        "内    功",
        "iron-cloth":   "基本硬功",
	"magic":        "法    术",
	"move":         "行    动",
	"parry":        "招    架",
	"spells":       "咒    文",
	"staff":        "杖    法",
//  兵器功夫
	"axe":		"斧　　法",
	"blade":        "刀    法",
	"club" :        "棍    法",
	"dagger":       "短 兵 刃",
	"fork":		"叉　　法",
	"halberd":      "戟    法",
        "hammer":       "锤    法",
	"hook":         "钩    法",
	"pestle":       "杵    法",
	"spear":        "枪    法",
	"stick":        "棒    法",
	"sword":        "剑    法",
	"throwing":     "暗    器",
	"whip":         "鞭    法",
//  空手功夫
	"unarmed":      "拳    脚",
	"finger":       "指    法",
	"hand":         "手    法",
	"cuff":         "拳    法",
	"claw":         "爪    法",
	"strike":       "掌    法",

]);

int main(object me, string arg)
{
	mapping map, pmap;
	string *types, *skill, ski, map_to;
	int i, modify;

	seteuid(getuid());

	if( !arg ) {
		map = me->query_skill_map();
		if( !mapp(map) || sizeof(map)==0 )
			return notify_fail("你现在没有使用任何特殊技能。\n");

		skill = keys(valid_types);
		write("以下是你目前使用中的特殊技能。\n");
		for (i=0; i<sizeof(skill); i++) {
			if( undefinedp(valid_types[skill[i]]) ) {
				map_delete(map, skill[i]);
				continue;
			}
			if( !me->query_skill(skill[i]) ) continue;
			modify = me->query_temp("apply/" + skill[i]);
			printf("  %-28s： %-20s  有效等级：%s%3d\n" NOR, 
				valid_types[skill[i]] + " (" + skill[i] + ")",
				undefinedp(map[skill[i]]) ? "无" : to_chinese(map[skill[i]]),
				(modify==0 ? "" : (modify>0 ? HIC : HIR)),
				me->query_skill(skill[i]));
		}
		return 1;
	}

	if( arg=="?" ) {
		write("以下是可以使用特殊技能的种类：\n");
		skill = sort_array(keys(valid_types), (: strcmp :) );
		for(i=0; i<sizeof(skill); i++) {
			printf("  %s (%s)\n", valid_types[skill[i]], skill[i] );
		}
		return 1;
	}

	if( sscanf(arg, "%s %s", ski, map_to)!=2 )
		return notify_fail("指令格式：enable|jifa [<技能种类> <技能名称>|none]\n");

	if( undefinedp(valid_types[ski]) )
		return notify_fail("没有这个技能种类，用 enable ? 可以查看有哪些种类。\n");
        
        if(me->query_skill_prepared(ski)
           ||me->query_wprepared(ski))
                return notify_fail("备了的技能不能被换掉。\n"); 

	if( map_to=="none" ) {
		me->map_skill(ski);
		me->reset_action();
		write("Ok.\n");
		return 1;
	} else if( map_to==ski ) {
		write("「" + to_chinese(ski) + "」是所有" + valid_types[ski] + "的基础，不需要 enable。\n");
		return 1;
	}

	if( !me->query_skill(map_to, 1) )
		return notify_fail("你不会这种技能。\n");

//      if( !me->query_skill(ski, 1) )
//              return notify_fail("你连「" + to_chinese(ski) + "」都没学会，更别提"
//                      + to_chinese(map_to) + "了。\n");

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
	// dewolf :: yinyang
    if( !YINYANG_D->skill_isvalid(me, map_to) )
	return notify_fail("不过以你的内功和天资无法支持"+to_chinese(map_to)+"这项"+SKILL_D(map_to)->query_yinyang()+"属性的技能。\n");
    
        if(me->query_skill(ski,1)==0)
                return notify_fail("你先学点基本功夫吧。\n");
	me->map_skill(ski, map_to);
	me->reset_action();
	write("Ok.\n");
	
	if( ski=="magic" ) {
		write("你改用另一种法术系，精力必须重新锻练。\n");
		me->set("jingli", 0);
		me->receive_damage("jing", 0);
	} 
	else if( ski=="force" ) {
		write("你改用另一种内功，内力必须重新锻练，功夫也必须重新激发。\n");
		me->set("neili", 0);
		me->receive_damage("qi", 0);
		
		// dewolf :: change force makes kungfu sweep
		if (pmap = me->query_skill_prepare())
		{
			skill = keys(pmap);
			for (i=0; i<sizeof(skill); i++)
			{
				me->prepare_skill(skill[i]);
			}
			me->reset_action();
		}
		if (pmap = me->query_skill_wprepare())
		{
			skill = keys(pmap);
			for (i=0; i<sizeof(skill); i++)
			{
				me->prepare_wskill(skill[i]);
			}
			me->reset_action();
		}
		if (pmap = me->query_skill_map())
		{
			skill = keys(pmap);
			for (i=0; i<sizeof(skill); i++)
			{
				if (skill[i]!="force")
					me->map_skill(skill[i]);
			}
			me->reset_action();
		}
		// end of sweep skill_map
		
		
//      } else if( ski=="spells" ) {
//              write("你改用另一种咒文系，法力必须重新修炼。\n");
//              me->set("mana", 0);
//              me->receive_damage("sen", 0);
	}

	return 1;
}
int help(object me)
{
	write(@HELP
指令格式 : enable|jifa [<技能种类> <技能名称> | none]
	   enable|jifa ?

这个指令让你指定所要用的技能，需指明技能种类和技能名称。如果不加参
数则会显示出技能种类及你目前所使用的技能名称 ，如果加一个？会列出
所有能使用特殊技能的技能种类。
 
HELP
	);
	return 1;
}
