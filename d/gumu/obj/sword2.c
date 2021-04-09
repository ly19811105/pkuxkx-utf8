//sword.c 君子剑

#include <weapon.h>
inherit SWORD;

void create()
{
	set_name("君子剑", ({ "junzi sword", "sword" }));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "柄");
		set("long", "这是一柄看起来很黑的一把剑，看起来不很显眼。\n");
		set("value", 12000);
		set("material", "steel");
		set("wield_msg", "$N拎出一把君子剑握在手中。\n");
		set("unwield_msg", "$N将手中君子剑插回腰间。\n");
	}
	init_sword(100);
	setup();
}
