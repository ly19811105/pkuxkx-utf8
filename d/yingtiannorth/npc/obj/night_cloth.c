#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("夜行衣", ({"yexing yi","yi", "cloth" }) );
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
				set("long","这是一件黑色的夜行衣。\n");
                set("unit", "件");
                set("material", "cloth");
                set("armor_prop/armor", 10);
        }
        setup();
}

