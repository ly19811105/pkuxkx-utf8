// tielianzi.c
 
#include <weapon.h>
 
inherit THROWING;
 
void create()
{
	set_name("铁莲子", ({ "tie lianzi", "lianzi", "zi" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "精铁打制的莲子状暗器。\n");
		set("unit", "把");
		set("value", 0);
		set("base_unit", "粒");
		set("base_weight", 1);
		set("base_value", 0);
		set("damage", 5);	//Here the damage=int_throwing, added by King
	}
	init_throwing(5);
	setup();
}
