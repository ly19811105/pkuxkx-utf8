#include <weapon.h>
#include <ansi.h>

inherit STAFF;

void create()
{
        set_name(HIB"寒铁杖"NOR, ({"hantie zhang","zhang","staff"}));
        set_weight(6000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long",YEL"星宿派镇派之宝，寒铁杖！\n"NOR);
                set("unit", "根");
                set("no_put",1);
                set("value", 0);
                set("no_store",1);
                set("no_give_user",1);
                set("no_steal",1);
                set("weapon_prop/staff",12+random(12));

        }
        init_staff(100+random(50));
        setup();
}
