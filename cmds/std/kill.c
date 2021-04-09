// kill.c
// Modified by iszt@pkuxkx, 2007-03-14, invalid_kill(), kill_msg, etc.

#include <ansi.h>

inherit F_CLEAN_UP;

string invalid_kill(object me, object target)
{
	object* team;

	if( environment(me)->query("no_fight") )
		return "这里不准战斗。\n";

	if (me->is_busy())
		return "你正忙着呢！\n";
        if(userp(target) && userp(me) && (int)me->query("PKS",1)/2 > me->query("age") - 14 )
 		    return "你杀的人还不够多吗？\n";
        if(me->query("combat_exp")<50000 && userp(target))
        return "自己功夫没练好，就想杀人？\n";  

	if( target==me )
		return "用 suicide 指令会比较快 :P。\n"; 

	if (target->query("uni_target"))
		if (!objectp(target->query("uni_target"))|| 
			  (target->query("uni_target") != me && target->query("uni_target")->query("suicongdizi/npc") != me))
			return "对方不愿和你较量。\n";

  if ( sscanf(base_name(environment(me)),"/d/%*s") &&
       !sscanf(base_name(environment(me)),"/d/wizard/%*s") &&
       userp(me) )
  {
    if ( userp(target) && me->query("xiuxian_player") )
      return "你已经退隐江湖，还是不要再惹江湖上的恩恩怨怨。\n";

    if ( userp(target) && target->query("xiuxian_player") )
      return "对方已经退隐江湖，你还忍心打搅他的清修？\n";
  }

	if( !target->is_character() || target->is_corpse() )
		{
			if (target->is_mazei())
			{
				target->unfold(me);
				return "你决定突袭"+target->query("name")+"。\n";
			}
			return "看清楚一点，那并不是生物。\n";
		}

	if( target->query("no_fight")  )
		return "杀掉他对你没什么好处！！！\n";

	if( (me->query("age") < 15) && userp(target) )
		return "你还小，人世间的钩心斗角、自相残杀还是别学的好。\n";

	if( arrayp(team = me->query_team()) && member_array(target, team)!=-1 )
		return "你们好歹也算是一条战线上的战友，难道真的要自相残杀吗？\n";

	if( userp(target) && !interactive(target) )
		return "连断线的人你也杀，可耻了点吧？\n";

	if( target->query("bihua") )
		return target->query("name") + "正在比武，你不能帮忙。\n";

	if( !undefinedp(me->query("friends/"+target->query("id"))) )
		return HIG"你这人怎么这么坏，要杀你的好友也要先把他(她)从好友中除去！\n"NOR; 

	return 0;
}

int main(object me, string arg)
{
	object obj;
	string kill_msg, msg;
	object *obs;
	int i;

	if( !arg )
		return notify_fail("你想杀谁？\n");

	if( !objectp(obj = present(arg, environment(me))) )
	{
		obs = all_inventory(environment(me));
		for (i = sizeof(obs)-1; i >= 0; i--)
		if ( obs[i]->mask_id() == arg )
		{
			obj = obs[i];
			break;
		}
		if (!objectp(obj))        	
			return notify_fail("这里没有这个人。\n");
	}

	if(stringp(msg = invalid_kill(me, obj)))
	{
		write(msg);
		return 1;
	}

	if(me->query("race")=="人类")
	{
		if(me->query("mute"))
                        msg = "\n$N突然冲向$n，双眼通红，看来是要置$n于死地！！\n\n";

		else if(stringp(kill_msg = me->query("env/kill_msg")))
                        msg = "\n$N对着$n大喝一声：「" + kill_msg + "！"NOR"」\n\n";

		else if(me->query("combat_exp") > obj->query("combat_exp")*2)
		{
			if(me->query("shen") < -10000)
				msg = "\n$N对着$n啐了一口：「$r！怪你生不逢时，$s今天看你极不顺眼，认命吧！」\n\n";
			else
				msg = "\n$N对着$n吼道：「$r！你死期已到，今天就让$s送你上西天吧！」\n\n";
		}

		else if(obj->query("combat_exp") > me->query("combat_exp")*2)
		{
			if(me->query("shen") < -10000)
				if(living(obj))
					msg = "\n$N对着$n阴笑道：「阎王叫你三更死，$s不敢留你过五更，$r，受死吧！」\n\n";
				else
					msg = "\n$N对着$n一声奸笑：「$r，别看你平时耀武扬威，今天$s就要取你性命！」\n\n";
			else
				if(living(obj))
					msg = "\n$N对着$n嘿嘿一笑：「$r，$S虽技不如你，但今天就是拼了命也要将你碎尸万段！」\n\n";
				else
					msg = "\n$N对着$n喝道：「$r！你记好$s的名字，死后到阴司去告我一状吧！」\n\n";
		}

		else {
			if(me->query("shen") < -10000)
				msg = "\n$N对着$n猛吼道：「$r！明年的今天就是你的祭日，让$s送你上路吧！」\n\n";
			else
				msg = "\n$N对着$n喝道：「$r！今日不是你死就是我活！」\n\n";
		}
	}
	else msg = "\n$N大吼一声，猛然扑向$n，看来是要将$n杀死！！\n\n";

	msg = replace_string(msg, "$r", RANK_D->query_rude(obj));
	msg = replace_string(msg, "$R", RANK_D->query_respect(obj));
	msg = replace_string(msg, "$s", RANK_D->query_self_rude(me));
	msg = replace_string(msg, "$S", RANK_D->query_self(me));

	message_vision(msg, me, obj);

	if (userp(me) && userp(obj))
	{
		log_file("static/ATTEMP_KILL",sprintf("%-12s(%-8s) attemped to kill %-12s(%-8s) on %s\n",
		me->name(1),me->query("id"),obj->name(1),obj->query("id"),ctime(time())));
//先出手的做个标记，被杀的话杀人者不增加杀气，by all@2015/1/21
		if (!environment(obj)->query("no_die") && !(obj->query("attack_player/id")==me->query("id") && time()-obj->query("attack_player/time")<300)
		&& !(me->query("attack_by_player/id")==obj->query("id") && time()-me->query("attack_by_player/time")<300))
		{
		me->set("attack_player/id",obj->query("id"));
		me->set("attack_player/time",time());
		obj->set("attack_by_player/id",me->query("id"));
		obj->set("attack_by_player/time",time());		
		}			
	}		
	
	me->kill_ob(obj);
	me->set_temp("killing", obj->query("id"));

	if( !userp(obj) )
		if(!obj->accept_kill(me))
			obj->kill_ob(me);
	else {
		obj->fight_ob(me);
		tell_object(obj, HIR "如果你要和" + me->name() 
			+ "性命相搏，请你也对这个人下一次 kill 指令。\n" NOR);
	}
	if (me->query("shaqi") >= 400)
		message_vision("$N面目狰狞，仿佛难以遏制心中的杀气。\n",me);
	if ( me->query("shaqi") >= 500 )
	{
		message_vision(HIR"$N忽然语无伦次，显然杀气过重，控制不了自己的行动了！\n"NOR, me);
		me->unconcious();
	}

	return 1;
}

int help(object me)
{
write(@HELP
指令格式 : kill <人物>
 
这个指令让你主动开始攻击一个人物，并且试图杀死对方，kill 和 fight 最大的
不同在於双方将会真刀实枪地打斗，也就是说，会真的受伤。由於 kill 只需单方
面一厢情愿就可以成立，因此你对任何人使用 kill 指令都会开始战斗，通常如果
对方是 NPC 的话，他们也会同样对你使用 kill。

当有人对你使用 kill 指令时会出现红色的字样警告你，对於一个玩家而言，如果
你没有对一名敌人使用过 kill 指令，就不会将对方真的打伤或杀死( 使用法术除
外)。

其他相关指令: fight hit

有关 fight 跟 kill 的区分请看 'help combat'.
HELP
    );
    return 1;
}
