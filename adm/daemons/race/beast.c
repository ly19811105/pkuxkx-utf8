// beast.c

#include <race/beast.h>

mapping combat_action =
([
	"hoof": ([
		"action":		"$N用后腿往$n的$l用力一蹬",
		"damage":		100,
		"damage_type":	"瘀伤",
	]),
	"bite": ([
		"action":		"$N扑上来张嘴往$n的$l狠狠地一咬",
		"damage":		20,
		"damage_type":	"咬伤",
	]),
	"claw": ([
		"action":		"$N用爪子往$n的$l一抓",
		"damage_type":	"抓伤",
	]),
	"poke": ([
		"action":		"$N用嘴往$n的$l一啄",
		"damage":		30,
		"damage_type":	"刺伤",
	]),
	"qian": ([
	        "action":               "$N用前螯往$n的$l用力一夹",
        	"damage":               50,
        	"damage_type":  "夹伤",
	]),

]);

string *actions;

void create()
{
	actions = keys(combat_action);
}

void setup_beast(object ob)
{
	mapping my;

	my = ob->query_entire_dbase();

	my["unit"] = "只";

         if( !(my["actions"]) ) {
		if( pointerp(my["verbs"]) )
			ob->set("default_actions", (: call_other, __FILE__, "query_action" :) );
		else
			my["default_actions"] = ([
				"action": "$N攻击$n的%s，%s\n",
			]);
	}
	
	if( undefinedp(my["gender"]) ) my["gender"] = "雄性";
	if( undefinedp(my["age"]) ) my["age"] = random(40) + 5;

	if( undefinedp(my["str"]) ) my["str"] = random(36) + 10;
	if( undefinedp(my["int"]) ) my["int"] = random(11) + 5;
	if( undefinedp(my["per"]) ) my["per"] = random(31) + 5;
	if( undefinedp(my["con"]) ) my["con"] = random(41) + 5;
	if( undefinedp(my["dex"]) ) my["dex"] = random(41) + 5;
	if( undefinedp(my["kar"]) ) my["kar"] = random(21) + 5;

	if( undefinedp(my["max_jing"]) ) {
		if( my["age"] <= 3 ) my["max_jing"] = 50;
		else if( my["age"] <= 10 ) my["max_jing"] = 50 + (my["age"] - 3) * 20;
		else if( my["age"] <= 30 ) my["max_jing"] = 190 + (my["age"] - 10) * 5;
		else my["max_jing"] = my["max_jing"] = 290 + (my["age"] - 30);
		my["jing"] = my["max_jing"] = 290 + (my["age"] - 30);
	}
	if( undefinedp(my["max_qi"]) ) {
		if( my["age"] <= 5 ) my["max_qi"] = 50;
		else if( my["age"] <= 20 ) my["max_qi"] = 50 + (my["age"] - 5) * 25;
		else my["max_qi"] = my["max_qi"] = 425 + (my["age"] - 20) * 5;
		my["qi"] = my["max_qi"] = 425 + (my["age"] - 20) * 5;
	}
	//	NOTE: beast has no initial limbs defined, you must define it yourself.
	//	ob->init_limbs(LIMBS);
	if( !ob->query_weight() ) ob->set_weight(BASE_WEIGHT + (my["str"] - 10)* 2000);
}

mapping query_action(object me)
{
	string *act;

	act = me->query("verbs");
	return combat_action[act[random(sizeof(act))]];
}
