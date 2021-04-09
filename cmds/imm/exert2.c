// exert.c
// Modified by snowman@SJ 08/12/2000
// 将 exert_function() 从/inherit/skill/skill.c 搬到这里。
// 理论上是否可以节约一些内存？ :-)
// Looklove Modified at 2001.5.20 for condition no_exert, can't exert all now.
// hehe

#include <skill.h>

inherit F_SSERVER;

int exert_function(object me, mixed skill, string arg);

int main(object me, string arg)
{
	string force;
	mixed rc;

	seteuid(getuid());

	if( me->is_busy() )
		return notify_fail("( 你上一个动作还没有完成，不能施用内功。)\n");

	if (!me->query_skill("force"))
		return notify_fail("你没有内功。\n");
	if( !arg )
		return notify_fail("你要用内功做什么？\n");

	if( me->query_condition("no_exert") || me->query_condition("no_force"))
	     	return notify_fail("你气息不匀，暂时不能施用内功。\n");

	notify_fail("你请先用 enable 指令选择你要使用的内功。\n");

	rc = exert_function(me, SKILL_D("force"), arg);
	if( stringp(rc) )
		return notify_fail(rc);
	if (rc >= 0)
		return rc;
	notify_fail("你所用的内功中没有这种功能。\n");
	if( stringp(force = me->query_skill_mapped("force")) ) {
//		if( me->is_exert())
//			return notify_fail(me->query_exert()+"运用当中，你不能施用内功。\n");
		if (exert_function(me, SKILL_D(force), arg) > 0) {
			if (me->is_fighting())
				me->add("combat_exp", random(2));
			return 1;
		}
	}
	return 0;
}

int exert_function(object me, mixed skill, string arg)
{
	string func, target, file;
	mixed target_ob;

	if( sscanf(arg, "%s %s", func, target)==2 ) {
		target_ob = present(target, environment(me));
		if( !target_ob ) target_ob = target;
	} else {
		func = arg;
		target_ob = offensive_target(me);
		if (!target_ob) target_ob = me;
	}

	if( !stringp(file = (string)skill->exert_function_file(func))
	|| file_size(file + ".c") <= 0 )
		return -1;

	notify_fail("");
	return (int)call_other( file, "exert", me, target_ob);
}

int help (object me)
{
	write(@HELP
指令格式：exert|yun <功能名称> [<施用对象>]

用内力进行一些特异功能，你必需要指定<功能名称>，<施用对象>则可有可无。
在你使用某一种内功的特异功能之前，你必须先用 enable 指令来指定你要使用
的内功。

请参考 help force 可得知一些大部分内功都有的功能，至于你所用的内功到底
有没有该功能，试一试或参考其他说明便知。

注：如果你改变自己的内功，你原本蓄积的内力并不能直接转换过去，必须
    从０开始。
HELP
	);
	return 1;
}
