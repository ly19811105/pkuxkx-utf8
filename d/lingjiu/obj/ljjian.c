#include <weapon.h>
inherit SWORD;

void create()
{
        set_name("灵鹫剑", ({ "lingjiusword", "sword", "jian" }));
        set_weight(5);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "这是灵鹫宫女弟子所用的剑。\n");
                set("material", "steel");
                set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回剑鞘。\n");
        }
        init_sword(20);
        setup();
}

