//whitebear.c
#include <ansi.h>
inherit NPC;
int auto_perform();
int auto_heal();

void create()
{
 	set_name("白熊",({"white bear", "bear"}));
  	set("race", "野兽");
  	set("age", 3);
  	set("long","这是一头憨憨的白熊，毛色看来很好！\n");
 	set("attitude", "aggressive");

  	set("str",60);
  	set("con",30);

	set("max_jing", 2000);
	set("max_qi", 10000);
	set("max_jingli", 2000);
	set("jingli", 2000);
	set("max_neili", 2000);
	set("neili", 2000);

	set("chat_chance_combat", 30);

  	set("limbs",({ "头部", "身体", "腿部", "臀部","前胸",}) );
  	set("verbs",({"bite", "claw"}) );
  	set("combat_exp", 5000000);

	set_skill("unarmed", 300);
	set_skill("hand", 300);
	set_skill("claw", 300);
	set_skill("strike", 300);
	set_skill("dodge", 300);
	set_skill("parry", 300);
	set_skill("force", 300);

  	set_temp("apply/attack", 500);
  	set_temp("apply/damage", 50);
  	set_temp("apply/armor", 100);
  	set_temp("apply/defence", 500);
  	set_temp("fight/dodge", 100);

  	set("gem_level", ({0, 8334}));
  	set("luding_monster", 1);

	set("chat_chance", 100);
	set("chat_msg", ({
		(: auto_heal :),
	}));

	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
		(: auto_perform :),
	}));

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
}



int auto_perform()
{
	object me = this_object();
	object target = me->select_opponent();
	object owner;
	object here = environment(me);
	int damage;

	if( me->is_busy() ) return 0;

	me->set("default_actions", (: call_other, __FILE__, "query_action" :));
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
	me->set("default_actions", (: call_other, "/adm/daemons/race/beast.c", "query_action" :));

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


mapping query_action(object me)
{
	if( random(2) == 0)
	return ([
	"action": HIR"祗见$N窜上前来，"+(random(2)?"右":"左")+"掌猛然拍向$n的$l"NOR,
	"force" : 200,
	"dodge" : 10,
	"parry" : 10,
	"damage" : 200,
	"weapon" :"熊掌",
	"damage_type":"拍伤"]);

	else return ([
	"action": HIR"祗见$N上千斤的身子一扑，猛然朝$n身上压来！"NOR,
	"force" : 200,
	"dodge" : 100,
	"parry" : 0,
	"damage" : 200,
	"weapon" :"熊身",
	"damage_type":"内伤"]);
}

void die()
{
	object ob, corpse;
	message_vision("$N凄惨的嚎了几声，死了。\n", this_object());
    	if( objectp(corpse = CHAR_D->make_corpse(this_object(), killer)) )
	corpse->move(environment(this_object()));
	corpse->set("no_get_from", 1);
	destruct(this_object());
}
