//Cracked by Roath
#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
        set_name(YEL"虎皮"NOR, ({ "hu pi", "pi" }) );
        set_weight(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "块");
                set("material", "fur");
                set("value", 5000);
                set("armor_prop/armor", 20);
        }
        setup();
}

