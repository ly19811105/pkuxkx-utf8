//Cracked by Roath
// Jay 7/12/96 

#include <weapon.h>

inherit BLADE;
inherit F_UNIQUE;

void create()
{
        set_name("鸳刀", ({ "yuan dao", "dao", "blade" }) );
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long",
			"这是把长刀，精光耀眼，刀刃上刻著「仁者」。\n");
                set("value", 14000);
                set("material", "blacksteel");
                set("wield_msg", 
			"只听见「飕」地一声，$N的手中已经多了一把$n。\n");
                set("unequip_msg", "$N将手中的$n插入腰间的刀鞘。\n");
        }

        init_blade(80);
        setup();
	::create();
}

void init()
{
	if( this_player() == environment() )
		{add_action("do_study", "study");
		 add_action("do_study", "du");}
}

int do_study(string arg)
{
	object me = this_player();

	if ( arg != "yuan dao" && arg != "dao" && arg != "blade")
	return notify_fail("你要学什么？\n");

	if (!present("yang dao", me))
	{ write("鸳鸯刀合在一处方可研读。\n");
	  return 1; }

	if ( me->is_fighting() 
	&& (int)me->query_skill("blade", 1) >= 30 
	&& (int)me->query_skill("blade", 1) <= 100
	&& (int)me->query("combat_exp") >= 50000 )
	{
		me->receive_damage("jing", 30);
		if (me->query("PKS")<10)
		me->improve_skill("blade", me->query("int"));
		else me->improve_skill("blade", 1);
		tell_object(me, "只见鸳鸯刀相互对绕，攻防呼应，你对刀术的领悟又深了一层！\n", me);
		if (me->query("PKS")>=10)
		tell_object(me, "然而「仁者无敌」，你杀害玩家太多，妨碍了你的领唔。\n", me);
		return 1;
	}

	return 0;
}

