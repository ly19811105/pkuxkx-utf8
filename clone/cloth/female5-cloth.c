// female5-cloth.c
//
// This is the basic equip for players just login.

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIB"青袖小衫"NOR, ({ "blue shan", "cloth" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
		set("long", "一件女孩喜欢的青袖小衫。\n");
                set("material", "cloth");
                set("value", 0);
                set("armor_prop/armor", 3);
		set("female_only", 1);
        }
        setup();
}

