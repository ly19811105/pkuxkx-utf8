//Cracked by Roath
// mudao.c

#include <ansi.h>
#include <weapon.h>

inherit BLADE;

void create()
{
	set_name("木刀", ({ "mu dao", "dao", "blade" }) );
        set_color("$YEL$");
	set_weight(2000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("value", 50);
		set("material", "iron");
		set("long", "这是一柄木制的短刀，少林寺僧习武均用此刀，以免伤人。\n");
		set("wield_msg", "$N抽出一把$n握在手中。\n");
		set("unequip_msg", "$N将手中的$n插回腰间。\n");
		set("shaolin",1);
	}
	init_blade(5);
	setup();
}
