// tudao.c

#include <weapon.h>
inherit BLADE;

void create()
{
	set_name("屠刀",({"tudao"}));
        set_weight(8000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "这是一柄亮晃晃的屠刀，是屠夫们用来杀猪的。\n");
                set("value", 2000);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n缩了回去。\n");
        }
        init_blade(30);
        setup();
}
