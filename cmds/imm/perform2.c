// perform.c
// Modified by snowman@SJ 08/12/2000
// 将 perform_action() 从/inherit/skill/skill.c 搬到这里。
// 理论上是否可以节约一些内存？ :-)
// Modified by emnil@sj 02/14/2001
// 添加自创perform的接口

inherit F_SSERVER;

int perform_action(object me, mixed skill, string arg);
int diy_pfm(object me, string arg);

int main(object me, string arg)
{
	object weapon;
	string martial, skill;
	mapping prepare;
	
	seteuid(getuid());

	if ( !arg ) return notify_fail("你要用外功做什么？\n");
	if ( me->is_busy() )
		return notify_fail("( 你上一个动作还没有完成，不能施用外功。)\n");
	if ( me->is_perform()) 
		return notify_fail(me->query_perform()+"的作用时间还没过，目前不能施用外功。\n");
	
	if ( me->query_condition("no_perform") )
		return notify_fail("( 你气息不匀，暂时不能施用外功。)\n");

	if ( me->query_temp("combat_yield") )
		return notify_fail("( 你正打不还手呢，施用外功干嘛？)\n");
			
	if( sscanf(arg, "%s.%s", martial, arg)!=2 ) {
		if( weapon = me->query_temp("weapon") )
			martial = weapon->query("skill_type");
		else {
			prepare = me->query_skill_prepare();
			if (sizeof(prepare)) martial = keys(prepare)[0];
			else
			martial = "unarmed";
		}
	}
	
	notify_fail("你所使用的外功中没有这种功能。\n");
	
	if( stringp(skill = me->query_skill_mapped(martial)) ){
		if( perform_action(me, SKILL_D(skill), arg) ) {
			if( me && random(120) < (int)me->query_skill(skill) )
				me->improve_skill(skill, 1, 1);
			return 1;
		}
		if( weapon )
			return diy_pfm(me, arg);
	}
	if ( sizeof(prepare) > 1) {
		martial = keys(prepare)[1];
		if( stringp(skill = me->query_skill_mapped(martial))
		&& perform_action(me,SKILL_D(skill), arg) ) {
			if( me && random(120) < (int)me->query_skill(skill, 1) )
				me->improve_skill(skill, 1, 1);
			return 1;
		}
	}
	if( stringp(skill = me->query_skill_mapped("parry"))
	&& perform_action(me,SKILL_D(skill), arg) ) {
		if(me && random(120) < (int)me->query_skill(skill, 1) )
			me->improve_skill(skill, 1, 1);
		return 1;
	}
	if( stringp(skill = me->query_skill_mapped("dodge"))
	&& perform_action(me,SKILL_D(skill), arg) ) {
		if( me && random(120) < (int)me->query_skill(skill, 1) )
			me->improve_skill(skill, 1, 1);
		return 1;
	}

	return diy_pfm(me, arg);
}

int perform_action(object me, object skill, string arg)
{
	string action, target, file;
	mixed target_ob;
	object d_target, d_source;

	if( sscanf(arg, "%s %s", action, target)==2 ) {
		target_ob = present(target, environment(me));
		if( !target_ob ) //target_ob = target;
			return notify_fail("这里没有 " + target + "。\n");
	}
	
	else{
		action = arg;
		target_ob = offensive_target(me);
	}

	if( !stringp(file = (string)skill->perform_action_file(action))
	||      file_size(file + ".c") <= 0 )
		return 0;
	
	if ( !objectp(target_ob) ) 
		return notify_fail("这里没有可使用的对象。\n");
		//return (int)call_other( file, "perform", me, target_ob);
	if ( !present(target_ob, environment(me)) )
		return notify_fail("这里没有可使用的对象。\n");
		
	if ( target_ob != me 
	&& (d_target = target_ob->query_temp("douzhuan_target"))
	&& (d_source = target_ob->query_temp("douzhuan_source"))){
		if(!objectp(d_target)
		|| !objectp(d_source)
		|| d_source != me
		|| environment(d_target) != environment(me)
		|| environment(d_target) != environment(target_ob) )
			return (int)call_other( file, "perform", me, target_ob);
			
		else {
			d_target->fight_ob(me);
			me->fight_ob(d_target);
			target_ob = d_target;
		}
	}
	return (int)call_other( file, "perform", me, target_ob);
}

int diy_pfm(object me, string arg)
{
	string skill, file, action, target;
	mixed target_ob;
	
	return 0;
	skill = SKILL_D(me->query_skill_mapped("force"));
	if( !stringp(skill) || (skill=="/kungfu/skill/0") )
		return 0;
	if( !stringp(file = (string)skill->exert_function_file("diypfm"))
	   || file_size(file + ".c") <= 0 )
		return 0;

	if( sscanf(arg, "%s %s", action, target)==2 ) {
		target_ob = present(target, environment(me));
		if( !target_ob ) //target_ob = target;
			return notify_fail("这里没有 " + target + "。\n");
	}
	else{
		action = arg;
		target_ob = offensive_target(me);
	}

	return (int)call_other( file, "perform", me, target_ob, action);
}

int help (object me)
{
	write(@HELP
指令格式：perfrom [<武功种类>.]<招式名称> [<施用对象>]

如果你所学的外功(拳脚、剑法、刀法....)有一些特殊的攻击方式或招式，可以
用这个指令来使用，你必须先用 enable 指令指定你使用的武功，不指定武功种
类时，空手的外功是指你的拳脚功夫，使用武器时则是兵刃的武功。

若是你的外功中有种类不同，但是招式名称相同的，或者不属於拳脚跟武器技能
的武功(如轻功)，可以用 <武功>.<招式>  的方式指定，如：

perform parry.yi

or

perform chan

换句话说，只要是 enable 中的武功有特殊招式的，都可以用这个指令使用。
HELP
	);
	return 1;
}
