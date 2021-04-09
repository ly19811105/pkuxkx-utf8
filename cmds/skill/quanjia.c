// du.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string what, who;
	object ob, victim;
	mapping myfam, vtfam;
	int sp, dp;

	object where = environment(me);
	
	seteuid(getuid());

        if ((!(myfam = me->query("family"))||myfam["family_name"] != "峨嵋派"))
        return notify_fail("只有峨嵋派才能用渡世济人！\n");

	if( environment(me)->query("no_fight") )
		return notify_fail("这里没有人打斗！\n");

	if( me->query_temp("dushi") )
		return notify_fail("你已经在劝人家罢斗了！\n");

	if( !arg || sscanf(arg, "%s stop", who)!=1 ) return
		notify_fail("指令格式：quanjia|persuade <人物> stop\n");

	victim = present(who, environment(me));

	if( !victim || victim == me) return notify_fail("你想找的对象不在这里。\n");
        if( me->query("combat_exp")>10000)
                return notify_fail("你都这么厉害了，不要去念佛经劝架吧！\n");

	if( !living(victim) || !objectp(victim))
		return notify_fail("你要劝谁罢斗？\n");

	if( !victim->is_fighting() )
		return notify_fail("人家没在打斗啊？\n");

	if ((vtfam = victim->query("family")) && vtfam["family_name"] == "峨嵋派" )
		return notify_fail("你不能向本派的使用渡世济人！\n");

	if( !wizardp(me) && wizardp(victim) )
		return notify_fail("玩家不能劝巫师罢斗。\n");

	if( me->is_fighting() )
                return notify_fail("一边打架一边劝别人罢斗？你真是虚伪到家了！\n");


	sp = (int)me->query_skill("persuading",1) + (int)me->query("kar") * 5;
	if( sp < 1 ) sp = 1;
	dp = (int)victim->query("jing");

	tell_object(me, "你摇摇了头，慢慢地向" + victim->name() + "走过去，双手合十，开始念诵佛经"
			+ "...\n\n");
	tell_object(victim, me->name() + "摇摇了头向你慢慢走过来，双手合十，说道：我佛慈悲普度渡众生, 还请" + RANK_D->query_respect(victim) + "罢斗, 免增罪孽吧 ...！\n\n");

	message("vision", "只见" + me->name() + "摇摇了头，慢慢地向" 
		+ victim->name() + "走过去，\n出双手合十，说道: 请"
		+ RANK_D->query_respect(victim) + "，停手吧 ...\n\n", environment(me), ({ me, victim }) );

	me->set_temp("dushi", 1);
	call_out( "compelete_dushi", 3, me, victim, ob, sp, dp);

	return 1;
}

protected void compelete_dushi(object me, object victim, object ob, int sp, int dp)
{
	int amount;
	object ob1;
	object where = environment(me);

	me->delete_temp("dushi");

	if( environment(victim) != environment(me) ) {
		tell_object(me, "太可惜了，你要找的人已经走了。\n");
		return;
	}

	if( living(victim) && (random(sp+dp) > dp) ) 
	{
		victim ->remove_all_enemy();
		tell_object(me, victim->name() + "低头想了一会，又看了看你，摇摇头，叹了口气，停止了打斗。\n");
		tell_object(victim, "你听了之后，心中不觉一紧，不再想继续打下去了。\n");

		me->improve_skill("persuading", 2 * random(me->query("int")));
		if(((int)me->query("learned_points") + 120) > (int)me->query("potential"))
			me->add("potential",1);
		me->add("combat_exp",2);

		me->start_busy(3);
	} 
	else 
	{
		if( random(sp) > dp/2 ) {
			message_vision(victim->name() + "狠狠地瞪了$N一眼，喝道：我都快让人给打死了，能罢斗吗! $N叹了口气转身走开了。\n", me);
			
			return;
		}
	
		tell_object(me, victim->name() + "扭过头去，对你理都不理。\n");
		tell_object(victim, "你扭过头去，对" + me->name() + "理都不理。\n");
		message("vision", victim->name() + "扭过头去，对" + me->name() + "理都不理。\n", 
			environment(me), ({ me, victim }) );

	}
}

int help(object me)
{
write(@HELP
指令格式 : persuade | quanjia <某人> stop

HELP
    );
    return 1;
}
