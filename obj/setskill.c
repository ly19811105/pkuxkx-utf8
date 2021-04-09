#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	int i,j,level;
	mapping skill_status;
	object ob;
	string skill,obj;
	string *skills;
	if( !arg )	return notify_fail("setskill <某人> <技能>/all <级别数>。\n");
        if( !arg || sscanf(arg, "%s %s %d", obj, skill, level)!=3 )
                return notify_fail("setskill <某人> <技能>/all <级别数>。\n");
	ob = find_player(obj);
	if( !ob )	ob = find_living(obj);
	if(!userp(ob))
	return notify_fail("不可以操纵NPC！\n");
	if( !ob )	ob = present(obj, environment(me));
        if( !ob ) return notify_fail("找不到这个生物.\n");
	if( (wiz_level(me) < wiz_level(ob)) && userp(ob) )
		return notify_fail("你没有设置" + ob->name() + "技能的权利。\n");
	if( level == 0 && wizardp(ob) )
		return notify_fail("不能用此命令将巫师的功夫删除。\n");
	if( (wiz_level(me) < wiz_level("(arch)")) && me!=ob )
		return notify_fail("你没有设置" + ob->name() + "技能的权利。\n");
	write(WHT"begin setting skills for "NOR + ob->short(1) + WHT"：\n"NOR);
	if( skill == "all" ) {
		if ( !(skill_status = ob->query_skills()) || !sizeof(skill_status) )
			return notify_fail("这个人没有学会任何技能，不能用 all 这个参数。\n");
		skills  = keys(skill_status);
		j = sizeof(skill_status);
        	for(i=0; i<j; i++) {
			if( level ==0 ) {
				ob->delete_skill(skills[i]);
				write("deleting->" + to_chinese(skills[i]) + 
					"(" + skills[i] + ")\n");
			}
			else {
				ob->set_skill(skills[i], level);
				printf("setting-> %-36s%d\n", to_chinese(skills[i]) + 
					"(" + skills[i] + ")", level);
			}
		}
	}
	else {
		if( level ==0 ) {
			write("deleting->" + to_chinese(skills[i]) + "(" + skills[i] + ")\n");
			ob->delete_skill(skill);
		}
		else	{
			ob->set_skill(skill, level);
			printf("setting-> %-36s%d\n", to_chinese(skill) + 
				"(" + skill + ")", level);
		}
	}
	write(WHT"Done.\n"NOR);
	return 1;
}
