// skills.c

#include <ansi.h>

inherit F_CLEAN_UP;

string *skill_level_desc = ({
	RED "初学乍练" NOR,
	HIB "略知一二" NOR,
	HIB "渐有所悟" NOR,
	HIM "平平常常" NOR,
	HIM"初入佳境" NOR,
	HIM "出类拔萃" NOR,
	MAG "出神入化" NOR,
	MAG "卓然大家" NOR,
	YEL "超群绝伦" NOR,
	YEL "独步天下" NOR,
	HIY "震古烁今" NOR,
        HIY "一代宗师" NOR,
        CYN "超凡入圣" NOR,
        CYN "返璞归真" NOR,
        GRN "深不可测" NOR 
             
});

string *knowledge_level_desc = ({
	RED "新学乍用" NOR,
	HIB "初窥门径" NOR,
	HIB "略知一二" NOR,
	HIM "平淡无奇" NOR,
	HIM "茅塞顿开" NOR,
	HIM "触类旁通" NOR,
	MAG "运用自如" NOR,
	MAG "心领神会" NOR,
	YEL "登堂入室" NOR,
	YEL "卓尔不群" NOR,
	HIY "满腹经纶" NOR,
        HIY "博古通今" NOR,
        CYN "举世无双" NOR,
        CYN "旷古绝伦" NOR,
        GRN "深不可测" NOR
});

string skill_level(string, int);

int main(object me, string arg)
{
	object ob;
	mapping skl, lrn, map;
	string *sname, *mapped;
	int i;

	seteuid(getuid());

	if(!arg)
		ob = me;
	else{
		ob = present(arg, environment(me));
//        if ( ob->query("SPSKILLS",1)  ) return ob->skills();		 
		if (!ob) ob = find_player(arg);
		if (!ob) ob = find_living(arg);
                if (!ob||!me->visible(ob)) return notify_fail("你要察看谁的技能？\n");
	}

	if( ob!=me && !wizardp(me) && !ob->is_apprentice_of(me)
	&& !me->is_apprentice_of(ob) && me->query("marry/lover") != ob->query("id") )
		return notify_fail("只有巫师，夫妻，或有师徒关系的人能察看他人的技能。\n");

	skl = ob->query_skills();
	if(!sizeof(skl)) {
		write( (ob==me ? "你" : ob->name()) + "目前并没有学会任何技能。\n");
		return 1;
	}
	write( (ob==me ? "你" : ob->name()) +"目前所学过的技能：\n\n");
	sname  = sort_array( keys(skl), (: strcmp :) );
	
	map = ob->query_skill_map();
	if( mapp(map) ) mapped = values(map);
	if( !mapped ) mapped = ({});

	lrn = ob->query_learned();
	if( !mapp(lrn) ) lrn = ([]);
	
	for(i=0; i<sizeof(skl); i++)
	{
       	if( !find_object(SKILL_D(sname[i])) && file_size(SKILL_D(sname[i])+".c") < 0)//判断是否是自创武功
		{
		printf("%s%s%-40s" NOR " - %-10s %3d/%5d\n", 
			(lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : "",
			(member_array(sname[i], mapped)==-1? "  ": "□"),
			to_chinese(sname[i]) + " (" + sname[i] + ")",
			skill_level(PLAYER_SKILL_D(sname[i])->type(), skl[sname[i]]),
			skl[sname[i]], (int)lrn[sname[i]],
			);
		}
		else
		{
		printf("%s%s%-40s" NOR " - %-10s %3d/%5d\n", 
			(lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : "",
			(member_array(sname[i], mapped)==-1? "  ": "□"),
			to_chinese(sname[i]) + " (" + sname[i] + ")",
			skill_level(SKILL_D(sname[i])->type(), skl[sname[i]]),
			skl[sname[i]], (int)lrn[sname[i]],
			);
		}
	}
	write("\n");
	return 1;
}

string skill_level(string type, int level)
{
	int grade;

	grade = level / 10;
	switch(type) {
		case "knowledge":
			if( grade >= sizeof(knowledge_level_desc) )
				grade = sizeof(knowledge_level_desc)-1;
			return knowledge_level_desc[grade];
		default:
			if( grade >= sizeof(skill_level_desc) )
				grade = sizeof(skill_level_desc)-1;
			
			return skill_level_desc[grade];
	}
}

int help(object me)
{
	write(@HELP
指令格式 : skills|cha [<某人>]

这个指令可以让你(你)查询所学过的技能。

你也可以指定一个和你有师徒关系的对象，用 skills 可以查知对方的技能状况。

巫师可以查询任何人或 NPC 的技能状况。

HELP
    );
    return 1;
}
