#include <ansi.h>
inherit F_SSERVER;

int valid_target_arg(string target)
{
    if ( target == "version" ) return 2;
    return target=="null" || target=="self" ;
}

string* valid_weapon() 
{
    return ({ "all" });
}

int perform(object me)
{
	string msg;
	mapping exits;
	string *dirs;
	object dest, target;
	string dir;

    target = offensive_target(me);

    if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
        return notify_fail("又没人要打你，跑什么啊？\n");

	if( target->is_busy() )
		return notify_fail(target->name() + "目前正自顾不暇，你想跑就跑呗！\n");

	if((int)me->query_skill("lingbo-weibu", 1)<50 )
		return notify_fail("你的凌波微步尚不纯熟，无法自如的施展出来。\n");

	if( !environment(me) )
		return notify_fail("这里似乎没地方可以跑！\n");

	if( sizeof(environment(me)->query("exits")) == 0 )
		return notify_fail("这里似乎没地方可以跑！！\n");

	if( !mapp(exits = environment(me)->query("exits")) )
		return notify_fail("这里似乎没地方可以跑！！！\n");

	msg = HIC "$N嫣然一笑，脚下步法愈加繁复无比，打算找机会开溜。\n";
	//自动找出口逃跑
	me->start_busy(random(2));
	//B+
	if( F_KUNGFU->hit_rate( (int)me->query_skill("dodge", "lingbo-weibu")/10+(int)me->query("dex")+ (int)me->query_dex(), (int)target->query_dex(), 11, me, target) )
	{
		msg += HIY"$n一眨眼间，$N已经不知去向。\n" NOR;
	//逃跑成功
		me->remove_all_enemy();
		dirs = keys(exits);
		dir = dirs[random(sizeof(dirs))];
		dest = exits[dir];
		if(environment(me)->valid_leave(me, dir)) //iszt added to avoid invalid leave bug
			me->move(dest);
		else
			return notify_fail("你想跑，可是被拦了下来。");
		target->remove_all_enemy();
		target->start_busy(1);
	}
	else
	{
	//逃跑失败
		msg += HIC"可是$n发现了$N的意图，加快了攻击，$N找不到机会逃走，反而更加手忙脚乱。\n" NOR;
		me->start_busy(3);
	}
	message_vision(msg, me, target);
	return 1;
}