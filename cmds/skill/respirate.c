// tuna.c

#include <skill.h>

int respirating(object me);
int halt_respirate(object me, object who, string how);

int main(object me, string arg)
{
	int respirate_cost;
	object where;

	seteuid(getuid());
	where = environment(me);

	if (where->query("pigging"))
		return notify_fail("你还是专心拱猪吧！\n");

	if (me->is_busy() || me->query_temp("pending/respirating"))
		return notify_fail("你现在正忙着呢。\n");

	if( me->is_fighting() )
		return notify_fail("战斗中吐纳，好象只有神仙才能做到。\n");

	if( !arg || !sscanf(arg, "%d", respirate_cost) || respirate_cost < 10 || respirate_cost>100000 )
		return notify_fail("指令格式 respirate|tuna <数量> ，数量指耗费精的大小，最小 10 点， 最多10万点。\n");

	if( ( (int)me->query("jing") < respirate_cost+10 )  ||  ( (int)me->query("jing") < respirate_cost + (int)(respirate_cost/10) ) )
		return notify_fail("你现在精不足，无法修行精力！\n");

	if( (int)me->query("qi") * 100 / (int)me->query("max_qi") < 70 )
		return notify_fail("你现在身体状况太差了，无法集中精神！\n");
		
  if (me->query_temp("neili_speedup") )
  	return notify_fail("你正在运行内功加速全身气血恢复，无法静下心来搬运真气。\n");

	me->set_temp("pending/respirate", 1);
	me->set_temp("respirate_cost", respirate_cost);
	message_vision("$N盘膝坐下，开始吐纳炼精。\n", me);
	me->start_busy( "respirating", "halt_respirate" );
	return 1;
}

int respirating(object me)
{
	int respirate_cost;int jingli_gain;
	if (!me) return 0;
	respirate_cost = (int)me->query_temp("respirate_cost");
	jingli_gain = 1 + (int)me->query_skill("force") / 10;
	jingli_gain=to_int(to_float(jingli_gain)*("feature/vein/BasicVein/shoutaiyin.c"->benefit_times(me)));
	if (respirate_cost < 1)
		return 0;

//	me->add("jingli", jingli_gain);
//	me->set_temp("respirate_cost", respirate_cost -= jingli_gain);
//	me->add("jing", -jingli_gain);
//	防止吐纳假死bug iszt@pkuxkx, 2007-01-17
        respirate_cost -= jingli_gain;
        if(respirate_cost < 0)
                jingli_gain = jingli_gain + respirate_cost; //r_c小于0时置为原来的值
        me->add("jing", -jingli_gain);
        if(me->query("special_skill/constitution") && me->query("age")>=18)
        jingli_gain += jingli_gain / 2; //constitution特技能让打坐效率增加50%
		jingli_gain=to_int(to_float(jingli_gain)*("feature/vein/BasicVein/shoutaiyin.c"->benefit_effect(me)+1.0));
    jingli_gain = jingli_gain * SPEWEEK_D->query_dz_bonus()/100;
        if(me->query("max_jingli") <1000)
        jingli_gain += jingli_gain  ; //精力1000以下打坐效率增加一倍
        jingli_gain =  to_int(jingli_gain * REWARD_D->get_global_factor("tuna"));
		jingli_gain = to_int(jingli_gain * REWARD_D->get_special_user_factor(me));
        me->set_temp("respirate_cost", respirate_cost);
        me->add("jingli", jingli_gain);

	if (respirate_cost > 0)
		return 1;

	me->set_temp("pending/respirate", 0);
	message_vision("$N吐纳完毕，睁开双眼，站了起来。\n", me);
	if ((int)me->query("jingli") < (int)me->query("max_jingli") * 2)
		return 0;
	else {
		if ((int)me->query("max_jingli") > (int)me->query_max_jingli() ) {
			write("你的精力修为已经达到了瓶颈。\n");
			me->set("jingli", (int)me->query("max_jingli"));
			return 0;
		}
		else {
			me->add("max_jingli", 1);
			me->set("jingli", (int)me->query("max_jingli"));
			write("你的精力上限增加了！！\n");
			return 0;
		}

	}
}

int halt_respirate(object me, object who, string how)
{
	if (!me) return 1;
	if ((int)me->query("jingli") > (int)me->query("max_jingli") * 2)
		me->set("jingli", (int)me->query("max_jingli") * 2);
	me->set_temp("pending/respirate", 0);
	return 1;
}

int help(object me)
{
	write(@HELP
指令格式 : respirate|tuna [<耗费「精」的量>]
打坐修行，利用「炼精化气，炼气化神，炼神还虚」的方法将你的精
转变成精力，数量最小是 10，可以达到的精力最大值为读书识字级别的10倍。
See also: exercise
HELP
		 );
	return 1;
}
