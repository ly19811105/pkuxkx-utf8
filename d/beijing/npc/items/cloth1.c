// cloth.c
// 布衣 zine 2 aug 2010


#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("布衣", ({ "cloth" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("material", "cloth");
                set("armor_prop/armor", 5);
        }
        setup();
}

