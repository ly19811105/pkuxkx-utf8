// tiespear.c
// Last Modified by winder on May. 25 2001
 
#include <weapon.h>
inherit SPEAR;

void create()
{
        set_name("铁枪", ({"iron spear", "qiang", "spear"}));
        set_weight(9000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "这是一把铁枪，枪尖略显银光．\n");
                set("value", 500);
                set("material", "iron");
                set("wield_msg","$N拿出一把$n，握在手中．\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }

        init_spear(40);
        setup();
}


