// weapond.c

#include <ansi.h>
#include <combat.h>

mapping weapon_actions = ([
	"slash": ([
		"damage_type":	"割伤",
		"action":		"$N挥动$w，斩向$n的$l",
		"parry":		20,
		]),
	"slice": ([
		"damage_type":	"劈伤",
		"action":		"$N用$w往$n的$l砍去",
		"dodge":		20,
		]),
	"chop": ([
		"damage_type":	"劈伤",
		"action":		"$N的$w朝著$n的$l劈将过去",
		"parry":		-20,
		]),
	"hack": ([
		"action":		"$N挥舞$w，对准$n的$l一阵乱砍",
		"damage_type":	"劈伤",
		"damage":		30,
		"dodge":		30,
		]),
	"thrust": ([
		"damage_type":	"刺伤",
		"action":		"$N用$w往$n的$l刺去",
		"dodge":		15,
		"parry":		-15,
		]),
	"pierce": ([
		"action":		"$N的$w往$n的$l狠狠地一捅",
		"damage_type":	"刺伤",
		"dodge":		-30,
		"parry":		-30,
		]),
	"whip": ([
		"action":		"$N将$w一扬，往$n的$l抽去",
		"damage_type":	"鞭伤",
		"dodge":		-20,
		"parry":		30,
		]),
	"impale": ([
		"action":		"$N用$w往$n的$l直戳过去",
		"damage_type":	"刺伤",
		"dodge":		-10,
		"parry":		-10,
		]),
	"bash": ([
		"action":		"$N挥舞$w，往$n的$l用力一砸",
		"damage_type":	"挫伤",
		"post_action":	(: call_other, __FILE__, "bash_weapon" :),
		]),
	"crush": ([
		"action":		"$N高高举起$w，往$n的$l当头砸下",
		"damage_type":	"挫伤",
		"post_action":	(: call_other, __FILE__, "bash_weapon" :),
		]),
	"slam": ([
		"action":		"$N手握$w，眼露凶光，猛地对准$n的$l挥了过去",
		"damage_type":	"挫伤",
		"post_action":	(: call_other, __FILE__, "bash_weapon" :),
		]),
	"throw": ([
		"action":		"$N将$w对准$n的$l射了过去",
		"damage_type":	"刺伤",
		"post_action":	(: call_other, __FILE__, "throw_weapon" :),
		]),
]);

varargs mapping query_action()
{
	string verb, *verbs;

	verbs = previous_object()->query("verbs");

	if( !pointerp(verbs) ) return weapon_actions["hit"];
	else {
		verb = verbs[random(sizeof(verbs))];
		if( !undefinedp(weapon_actions[verb]) ) return weapon_actions[verb];
		else return weapon_actions["hit"];
	}
}

void throw_weapon(object me, object victim, object weapon, int damage)
{
	if( objectp(weapon) ) {
		if( (int)weapon->query_amount()==1 ) {
			weapon->unequip();
			tell_object(me, "\n你的" + weapon->query("name") + "用完了！\n\n");
		}
		weapon->add_amount(-1);
	}
}

void bash_weapon(object me, object victim, object weapon, int damage)
{
	object ob;
	int wap, wdp;

	if( objectp(weapon)
	&&	damage==RESULT_PARRY
	&&	ob = victim->query_temp("weapon") ) {
		wap = (int)weapon->weight() / 500
			+ (int)weapon->query("rigidity")
			+ (int)me->query("str");
		wdp = (int)ob->weight() / 500
			+ (int)ob->query("rigidity")
			+ (int)victim->query("str");
		wap = random(wap);
		if( wap > 2 * wdp ) {
			ob->add("rigidity", -10);
			weapon->add("rigidity", -1);
			if(ob->query("rigidity") < 1 || weapon->query("rigidity") < 1)
			{
			if(ob->query("rigidity") < 1)
			{
			message_vision(HIW "（只听见「啪」地一声，$N手中的" + ob->name()
				+ "已经断为两截！）\n" NOR, victim );
			ob->unequip();
			ob->move(environment(victim));
			ob->set("name", "断掉的" + ob->query("name"));
			ob->set("value", 0);
			ob->set("weapon_prop", 0);
			victim->reset_action();
			}
			if(weapon->query("rigidity") < 1)
			{
			message_vision(HIW "（只听见「啪」地一声，$N手中的" + weapon->name()
				+ "已经断为两截！）\n" NOR, me );
			weapon->unequip();
			weapon->move(environment(me));
			weapon->set("name", "断掉的" + weapon->query("name"));
			weapon->set("value", 0);
			weapon->set("weapon_prop", 0);
			me->reset_action();
			}
			return;
			}
			message_vision(HIW "（$N只觉得手中" + ob->name() + "把持不定，脱手飞出！）\n" NOR,
				victim);
			ob->unequip();
			ob->move(environment(victim));
			victim->reset_action();
		} else if( wap > wdp ) {
			ob->add("rigidity", -10);
			weapon->add("rigidity", -1);
			if(ob->query("rigidity") < 1 || weapon->query("rigidity") < 1)
			{
			if(ob->query("rigidity") < 1)
			{
			message_vision(HIW "（只听见「啪」地一声，$N手中的" + ob->name()
				+ "已经断为两截！）\n" NOR, victim );
			ob->unequip();
			ob->move(environment(victim));
			ob->set("name", "断掉的" + ob->query("name"));
			ob->set("value", 0);
			ob->set("weapon_prop", 0);
			victim->reset_action();
			}
			if(weapon->query("rigidity") < 1)
			{
			message_vision(HIW "（只听见「啪」地一声，$N手中的" + weapon->name()
				+ "已经断为两截！）\n" NOR, me );
			weapon->unequip();
			weapon->move(environment(me));
			weapon->set("name", "断掉的" + weapon->query("name"));
			weapon->set("value", 0);
			weapon->set("weapon_prop", 0);
			me->reset_action();
			}
			return;
			}
			message_vision("（$N只觉得手中" + ob->name() + "一震，险些脱手！）\n",
				victim);
		} else if( wap > wdp / 2 ) {
			ob->add("rigidity", -50);
			weapon->add("rigidity", -1);
			if(ob->query("rigidity") < 1 || weapon->query("rigidity") < 1)
			{
			if(ob->query("rigidity") < 1)
			{
			message_vision(HIW "（只听见「啪」地一声，$N手中的" + ob->name()
				+ "已经断为两截！）\n" NOR, victim );
			ob->unequip();
			ob->move(environment(victim));
			ob->set("name", "断掉的" + ob->query("name"));
			ob->set("value", 0);
			ob->set("weapon_prop", 0);
			victim->reset_action();
			}
			if(weapon->query("rigidity") < 1)
			{
			message_vision(HIW "（只听见「啪」地一声，$N手中的" + weapon->name()
				+ "已经断为两截！）\n" NOR, me );
			weapon->unequip();
			weapon->move(environment(me));
			weapon->set("name", "断掉的" + weapon->query("name"));
			weapon->set("value", 0);
			weapon->set("weapon_prop", 0);
			me->reset_action();
			}
			return;
			}
			message_vision(HIC"（$N的" + weapon->name() + "和$n的" + ob->name()
				+ "重重交击在一起，发出「铛」地一声。）\n"NOR, me, victim);
		} else {
			ob->add("rigidity", -1);
			weapon->add("rigidity", -1);
			if(ob->query("rigidity") < 1 || weapon->query("rigidity") < 1)
			{
			if(weapon->query("rigidity") < 1)
			{
			message_vision(HIW "（只听见「啪」地一声，$N手中的" + ob->name()
				+ "已经断为两截！）\n" NOR, victim );
			ob->unequip();
			ob->move(environment(victim));
			ob->set("name", "断掉的" + ob->query("name"));
			ob->set("value", 0);
			ob->set("weapon_prop", 0);
			victim->reset_action();
			}
			if(weapon->query("rigidity") < 1)
			{
			message_vision(HIW "（只听见「啪」地一声，$N手中的" + weapon->name()
				+ "已经断为两截！）\n" NOR, me );
			weapon->unequip();
			weapon->move(environment(me));
			weapon->set("name", "断掉的" + weapon->query("name"));
			weapon->set("value", 0);
			weapon->set("weapon_prop", 0);
			me->reset_action();
			}
			return;
			}
			message_vision(HIY"（$N的" + weapon->name() + "和$n的" + ob->name()
				+ "相击，冒出点点的火星。）\n"NOR, me, victim);
		}
	}
}
