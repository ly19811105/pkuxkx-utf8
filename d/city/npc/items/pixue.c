// shoe.c zine 2 aug 2010

#include <armor.h>

inherit BOOTS;

void create()
{
	set_name( "鐨澊", ({ "pi xue", "shoes", "boots"}) );
	set_weight(900);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("material", "cloth");
		set("unit", "鍙?);
		set("value", 300);
		set("armor_prop/armor", 10 );
		
	}
	setup();
}
