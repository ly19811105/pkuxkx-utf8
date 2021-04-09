// expell.c
// Modified by iszt@pkuxkx, 2007-05-11, removed skill penalty, added warn_expell and log

#include <skill.h>
#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object ob;
	string *skname;
	string msg;
	mapping skills;
	int i;

	if( !arg || !ob = present(arg, environment(me)) )
		return notify_fail("你要将谁逐出师门？\n");

	if( !ob->is_character() )
		return notify_fail("你逐不动他。\n");

	if( !userp(ob) )
		return notify_fail("你只能开除玩家所扮演的人物。\n");

	if( me->query("family/privs")==-1
	&&	(string)me->query("family/family_name")==(string)ob->query("family/family_name") )
		msg = RED"\n$N对着$n说道：从今天起，你再也不是我"
			+ me->query("family/family_name") + "的弟子了，你走吧！\n\n"NOR;
	else if( ob->is_apprentice_of(me) )
		msg = RED"\n$N对着$n说道：从今天起，你我师徒恩断情绝，你走吧！\n\n"NOR;
	else
		return notify_fail("这个人不是你的弟子。\n");

	if(ob->query("warn_expell") < 2)
	{
		msg += CYN"$N想了想，又道：所谓事不过三，这次暂且饶了你，下次再让我看到，就不用认我这个师父了！\n"NOR;
		message_vision(msg, me, ob);
		ob->add("warn_expell", 1);
		tell_object(ob, HIR"你已经被警告"+chinese_number(ob->query("warn_expell"))+"次了！\n"NOR);
		return 1;
	}
	ob->delete("warn_expell");
	message_vision(msg, me, ob);
	tell_object(ob, "\n你被" + me->query("name") + "开革出师门了！\n\n");

	log_file("static/expell",sprintf("%s(%s) 于%s被%s开除，经验(%d)，潜能(%d)。\n",
		ob->query("name"),ob->query("id"),ctime(time()),
		me->query("name"),ob->query("combat_exp"),ob->query("potential")));

	ob->add("betrayer",1);
	ob->set("title",HIW+ob->query("family/family_name") + "弃徒"+NOR);
	ob->expell_family(ob->query("family/family_name"));

	return 1;
}

int help(object me)
{
	write(@HELP
指令格式 : expell|kaichu <某人>
 
这个指令可以让你开除不成才的弟子，被开除的弟子所有技能都会降到原来
的一半，而且综合评价一项会变成零，这对于一个人物而言是一个「比死还
严重」的打击，请你在开除一名弟子之前务必审慎考虑。
 
HELP
	);
	return 1;
}
