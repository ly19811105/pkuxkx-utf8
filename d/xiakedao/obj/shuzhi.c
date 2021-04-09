//树枝
//for xiake dao

#include <weapon.h>

inherit SWORD;

void create()
{
	set_name("树枝", ({ "shu zhi","zhi" }) );
	set_weight(400);
   if( clonep() )
     set_default_object(__FILE__);
   else {
     set("unit", "根");
     set("material", "wood");
     set("long", "这是一根细长的树枝。\n");
     set("wield_msg", "$N抽出一根细长的树枝，握在手中。\n");
     set("unequip_msg", "$N放下手中的$n。\n");
   }
   init_sword(5);
   setup();
}

