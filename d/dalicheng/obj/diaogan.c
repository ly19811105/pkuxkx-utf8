//Cracked by Roath
#include <weapon.h>
inherit STAFF;

void create()
{
        set_name("钓杆", ({ "diao gan", "gan","staff" }) );
 
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "这是一根生铁铸成的钓杆，上面悬了根铁丝。\n");
                set("value", 250);
                set("material", "steel");
                set("wield_msg", "$N抽出一根$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回腰间。\n");
        }
        init_staff(25);
        setup();
}

