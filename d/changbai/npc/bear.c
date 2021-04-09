//大白熊
//bear.c
#include <ansi.h>
inherit NPC;
int auto_perform();
int auto_heal();

void create()
{
 	set_name("大白熊",({"big bear", "bear"}));
  	set("race", "野兽");
  	set("age", 5);
  	set("long","这是一头憨憨的大白熊，毛色看来很好！\n");
 	set("attitude", "aggressive");

  	set("str",60);
  	set("con",30);

	set("max_jing", 4000);
        set("max_qi", 75000);
	set("max_jingli", 2000);
	set("jingli", 2000);
	set("max_neili", 4000);
	set("neili", 4000);

	set("chat_chance_combat", 30);

  	set("limbs",({ "头部", "身体", "腿部", "臀部","前胸",}) );
  	set("verbs",({"bite", "claw"}) );
        set("combat_exp", 20000000);

	set_skill("unarmed", 300);
	set_skill("hand", 300);
	set_skill("claw", 300);
	set_skill("strike", 300);
	set_skill("dodge", 600);
	set_skill("parry", 600);
	set_skill("force", 300);

  	set_temp("apply/attack", 1000);
  	set_temp("apply/damage", 100);
  	set_temp("apply/armor", 100);
  	set_temp("apply/defence",1000);
  	set_temp("fight/dodge", 100);

  	set("gem_level", ({0, 9444}));
  	set("luding_monster", 1);

	set("chat_chance", 100);
	set("chat_msg", ({
		(: auto_heal :),
	}));

	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
		(: auto_perform :),
	}));

  set("shen_type",-1);
set("score",500);
setup();
}

void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) )
        {
                        remove_call_out("kill_ob");
                        call_out("kill_ob", 1, ob);
        }
	add_action("do_struggle", "struggle");
}

void chaning(object me, object ob)
{
	int ap, dp, pp, jingli, damage;

	string *chan_msg = ({
		HIR"\n$n暗运劲力，想将压在身上的$N推开。但$N身子实在太重，丝毫不起作用。\n"NOR,
		HIR"\n$N猛力下压，只箍得$n腰骨几欲折断。\n"NOR,
		HIR"\n$N身子越压越紧，再也不放松，$n渐渐给$N压得喘不过气来。\n"NOR,
		HIR"\n$n被$N压住，除了呻吟怒骂，再无反抗的能为。\n"NOR,
	});

	string chan;

	chan = chan_msg[random(sizeof(chan_msg))];



	jingli = me->query("jingli");
	ap = jingli + random(jingli);
	pp = ob->query("jiali") + ob->query_str()*random(10) + (int)ob->query_skill("force");
	damage = (ap - pp)/3;

	if(damage > 1000 ) damage = 1000;
	if(damage < 100 ) damage = 100;

	if(wizardp(ob))
	tell_object(ob,sprintf("ap：%d ,pp：%d ,damage：%d \n" ,ap,pp,damage));

	if(!ob) {
		me->delete_temp("chaning");
		return;
	}
	if (present(ob, environment(me))) {

		if( !me->query_temp("chaning") || !ob->query_temp("snake_chan") ) {
		me->delete_temp("chaning");
		ob->delete_temp("snake_chan");
		return;
	}

		if (!living(ob) ) {  //猎物昏了就咬死
			message_vision(HIR"这时$n已给$N压得奄奄一息，$N张开大口，一口便将$n咬死。\n"NOR, me, ob);
			ob->receive_wound("qi", (ob->query("qi") + 500), me);
			ob->receive_damage("qi", (ob->query("qi") + 500), me);
			ob->delete_temp("snake_chan");
			me->delete_temp("chaning");

			return;
		}

		else if (!ob->is_character() ) {  //猎物死了就放开
			message_vision("$N松开身子，放开了$n。\n", me, ob);
			ob->delete_temp("snake_chan");
			me->delete_temp("chaning");
		return;
		}
		else {

			if(ap < random(pp) || jingli < 500 ) {
			message_vision("$N似乎敌不过$n的劲力，慢慢松开身子，站起身来，放开了$n。\n", me, ob);
			ob->delete_temp("snake_chan");
			me->delete_temp("chaning");
			}
			else {
			message_vision(chan , me, ob);
			ob->start_busy(4);
			me->start_busy(3);
			me->add("jingli", -(pp/20));
			ob->add("jingli", -damage/4);
			if (ob->query("jingli")<0) ob->set("jingli", 0);

			ob->receive_wound("qi", random(damage/10), me);
			ob->receive_damage("qi", damage/2, me);

			remove_call_out("chaning");
			call_out("chaning", 2, me, ob);
			}
			return;
		}
	}

	return;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	if(me->query_temp("try_chan")) {
	me->set_temp("chaning", victim->query("id"));
	victim->set_temp("snake_chan",1);
	victim->start_busy(3);
	me->start_busy(2);
	remove_call_out("chaning");
	call_out("chaning", 1, me, victim);

	if(victim->query("race") == "人类") return HIR"$n一个疏神，已被$N压住，再也没法抗拒。\n"NOR;
	else return HIR"这一下$n没有躲开，$N立刻压在$p身上，$n顿时动弹不得。\n"NOR;
	}

}

int auto_perform()
{
	object me = this_object();
	object target = me->select_opponent();
	object owner;
	object here = environment(me);
	int damage;

	if( me->query("jingli") < 500 ) return 0;

	if( me->is_busy() || target->query_temp("snake_chan") ) return 0;

	me->set_temp("try_chan", 1);
	me->set("default_actions", (: call_other, __FILE__, "query_action" :));
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
	me->set("default_actions", (: call_other, "/adm/daemons/race/beast.c", "query_action" :));
	me->delete_temp("try_chan",1);
	return 1;
}
int auto_heal()
{
        object ob = this_player();
        int amount;

        if (ob->query("eff_qi") < ob->query("max_qi"))
        {
                amount = ob->query("max_qi") / 20;
                ob->add("eff_qi", amount);
                if (ob->query("eff_qi") > ob->query("max_qi")) ob->set("eff_qi", ob->query("max_qi"));
        }
        if (ob->query("qi") < ob->query("eff_qi"))
        {
                amount = ob->query("eff_qi") / 20;
                ob->add("qi", amount);
                if (ob->query("qi") > ob->query("eff_qi")) ob->set("qi", ob->query("eff_qi"));
        }
        if (ob->query("jingli") < ob->query("max_jingli") * 2)
        {
                amount = ob->query("max_jingli") / 20;
                ob->add("jingli", amount);
                if (ob->query("jingli") > ob->query("max_jingli") * 2) ob->set("jingli", ob->query("max_jingli") * 2);
        }
        if (ob->query("eff_jing") < ob->query("max_jing"))
        {
                amount = ob->query("max_jing") / 20;
                ob->add("eff_jing", amount);
                if (ob->query("eff_jing") > ob->query("max_jing")) ob->set("eff_jing", ob->query("max_jing"));
        }
        if (ob->query("jing") < ob->query("eff_jing"))
        {
                amount = ob->query("eff_jing") / 20;
                ob->add("jing", amount);
                if (ob->query("jing") > ob->query("eff_jing")) ob->set("jing", ob->query("eff_jing"));
        }
        if (ob->query("neili") < ob->query("max_neili") * 2)
        {
                amount = ob->query("max_neili") / 20;
                ob->add("neili", amount);
                if (ob->query("neili") > ob->query("max_neili") * 2) ob->set("neili", ob->query("max_neili") * 2);
        }
	return 1;
}
int do_struggle(string arg)
{
	object me, snake;
	int ap, jingli, jiali;

	me = this_player();
	snake = this_object();

	if( snake->query_temp("chaning") != me->query("id"))
		return 0;
	if( !me->query_temp("snake_chan") || !me->is_busy() )
		return 0;

	jingli = snake->query("jingli");
	jiali = me->query("jiali");
	ap = jingli + random(jingli);

	if(me->query_temp("struggle_snake") > 4) {
		message_vision(HIW"\n$N用力挣了一挣，想摆脱压住身子的$n.....\n"NOR, me, snake);
		message_vision(HIR"\n不料$N身子动得太厉害，激怒了压住了$P的$n，一口便咬住$P的咽喉！\n"NOR, me, snake);
		me->receive_wound("qi", random(ap/2), me);
		me->receive_damage("qi", ap/2, me);
		me->unconcious();
	}
	else {
		message_vision(HIW"\n$N用力挣了一挣，想摆脱压住身子的$n.....\n"NOR, me, snake);
		me->add("neili", -(jiali+10));
		if (me->query("neili")<0)
		{
			me->set("neili",0);
			me->set("jiali",0);
			write(HIW"但此时你内力耗尽，已经无力回天了。\n"NOR);
		}
		snake->add("jingli", -jiali*2 );
		me->add_temp("struggle_snake", 1);
		remove_call_out("remove_effect");
		call_out("remove_effect", 1, me);
	}

	return 1;
}

void remove_effect(object me)
{
	me->delete_temp("struggle_snake");
}

mapping query_action(object me)
{
	if( random(2) == 0)
	return ([
	"action": HIR"祗见$N窜上前来，"+(random(2)?"右":"左")+"掌猛然拍向$n的$l"NOR,
	"force" : 400,
	"dodge" : 10,
	"parry" : 10,
	"damage" : 400,
	"weapon" :"熊掌",
	"damage_type":"拍伤"]);

	else return ([
	"action": HIR"祗见$N上千斤的身子一扑，猛然朝$n身上压来！"NOR,
	"force" : 400,
	"dodge" : 100,
	"parry" : 0,
	"damage" : 400,
	"weapon" :"熊身",
	"damage_type":"内伤"]);
}

void die()
{
	object ob, corpse;
     int i;
	message_vision("$N凄惨的嚎了几声，死了。\n", this_object());
	ob = new("/d/changbai/obj/bearheart");
    	if( objectp(corpse = CHAR_D->make_corpse(this_object(), killer)) )
	corpse->move(environment(this_object()));
	ob->move(corpse);
        corpse->set("no_get_from", 1);
        corpse->set("no_get", 1);
	destruct(this_object());
}
